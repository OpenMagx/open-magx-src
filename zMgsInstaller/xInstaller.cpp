#include "xInstaller.h"

#include <time.h>
#include <iostream>
#include <sys/vfs.h>

#include <ZConfig.h>
#include <ZSoftKey.h>
#include <ZMessageDlg.h>

#include <qcopchannel_qws.h>
#include <qdir.h>
#include <qfile.h>
#include <qtextstream.h>

#include <MYSTUFF_Global.h>

using namespace std;

xInstaller::xInstaller(): QWidget(NULL, "", 0)
{
	bCancel=false;
	
	uiDlg = new AM_MPKGUI();

	if ( uiDlg->isCardMounted() )
		sTemp = TEMP_MMC;
	else
		sTemp = TEMP_PHONE;
		
	channelStart = new QCopChannel("zMgsInstaller",this,"zMgsInstaller");
	connect( channelStart, SIGNAL(received(const QCString&, const QByteArray&)), this, SLOT( siganalReceived(const QCString&, const QByteArray&) ) );
}

xInstaller::~xInstaller()
{
	delete uiDlg;
}

void xInstaller::siganalReceived( const QCString &msg, const QByteArray &data )
{
	if ( msg == "proc_show()" ) 
	{
		dlgProc = new ZProgressDlg("zMgsInstaller", "", "", this );
		dlgProc->show();
		qApp->processEvents();	
	} else 
	if ( msg == "proc_hide()" )
	{
		dlgProc->hide();
		delete dlgProc;
		dlgProc=0;
	} 
}

void xInstaller::createTmpDir( QString &tmpDirectory )
{
	QDir dir;
	if ( !dir.exists ( tmpDirectory.utf8() ) ) 
		system ( QString ( "mkdir -p %1" ).arg ( tmpDirectory ).utf8() );
	else
		clearTmpDir ( tmpDirectory, true );
}

void xInstaller::clearTmpDir( QString &tmpDirectory, bool onlyIn )
{
	toLog("Clear temp dir");
	if ( onlyIn )
		system ( QString ( "rm -r %1/*" ).arg ( tmpDirectory ).utf8() );
	else
		system ( QString ( "rm -r %1" ).arg ( tmpDirectory ).utf8() );
}

double xInstaller::getFileSystemFreeSize( AM_Global::Device device )
{
	double freeSize = 0, totalSize = 0;
	STUFF_Global::getDiskSize(((device==AM_Global::Flash2)?(ROOT_PATH_PHONE):((device==AM_Global::Card1)?ROOT_PATH_MMC:"")), freeSize, totalSize);
	return freeSize;
}

QString xInstaller::getPathByDevice( AM_Global::Device device )
{
	switch ( device )
	{
		case AM_Global::Flash2:
			return QString(PATH_PHONE);
		case AM_Global::Card1:
			return QString(PATH_MMC);
		default:
			bCancel = true;
			return "";		
	}	
}

void xInstaller::cancelInstall()
{
	clearTmpDir(sTemp, false);
}

QString xInstaller::getLangLine( QString sFrase )
{
	QString curLng;
	{
		ZConfig cfg( "/ezxlocal/download/appwrite/setup/ezx_system.cfg" );
		curLng = cfg.readEntry(QString("SYS_SYSTEM_SET"), QString("LanguageType"), "");
		if ( curLng.length() > 1 )
			curLng = QString(curLng[0]) + QString(curLng[1]);
	}
	toLog("autoLoadLng: current system lng - "+curLng);
	
	ZConfig cfg( LNG_PATH+"/"+curLng+".lng" );
	return QString::fromUtf8(cfg.readEntry(QString("skin"), sFrase, sFrase).utf8()).replace("/n","\n");
}

void xInstaller::fixParamChm(ZConfig *cfg, QString param, QString installPath)
{
	QString tmpPath = cfg->readEntry("THEME_CONFIG_TABLE", param, "");
	if ( !tmpPath.isEmpty() && tmpPath.findRev("/")!=-1 )
	{
		tmpPath = installPath+tmpPath.right( tmpPath.length()-tmpPath.findRev("/") );
		cfg->writeEntry("THEME_CONFIG_TABLE", param, tmpPath);
	}
}

bool xInstaller::run( QString sPakgPath )
{
	QCopChannel::send( "zMgsInstaller", "proc_show()" );
	qApp->processEvents();
	qApp->processEvents();
	//unpack pack
	{
		createTmpDir(sTemp);
		system( QString(PATH_7Z).arg( sPakgPath ).arg( sTemp ) );
		
		QString tarName = sPakgPath.right( sPakgPath.length() - sPakgPath.findRev('/') );
		tarName = tarName.left( tarName.findRev('.')+1 ) +"tar";
		toLog( "Check tar: " + sTemp+tarName );
		if ( QFile::exists( sTemp+tarName ) )
		{
			system( QString(PATH_7Z).arg( sTemp+tarName ).arg( sTemp ) );	
			system( QString("rm %1").arg( sTemp+tarName ) );	
		}
	}
	QCopChannel::send( "zMgsInstaller", "proc_hide()" );
	
	//detect pak type
	QString sTempFolder="";
	{
		QDir dir ( sTemp, "*" );
		dir.setFilter ( QDir::Dirs | QDir::Hidden );
		QStringList entries = dir.entryList();
		entries.sort();	

		QStringList::ConstIterator it = entries.begin();
		while ( it != entries.end() )
		{
			if ( *it != "." && *it != ".." )
			{
				sTempFolder = *it;
				toLog( QString( "Maybe pak folder:" ) + sTempFolder );
				if ( QFile::exists( sTemp + "/"+sTempFolder+"/"+sTempFolder+".chm" ) )
					break;
			}
			it++;
		}
	}
	if ( sTempFolder.isEmpty() || bCancel )
	{
		toLog("Error: not detected pak type!");
		uiDlg->corruptFileDlg();
		cancelInstall();
		return 0;
	}
	
	toLog("Create discription app");
	
	
	SkinEntry installedSkin;
    
    ZConfig cfg( sTemp + "/" + sTempFolder + "/" + sTempFolder + ".chm" );
	installedSkin.name = cfg.readEntry ( "THEME_CONFIG_TABLE", "ThemeName", "" );
    installedSkin.vendor = cfg.readEntry ( "THEME_PROP_TABLE", "CopyRight", "" );
    installedSkin.date = cfg.readEntry ( "THEME_PROP_TABLE", "CreatedTime", "" );
    installedSkin.directory = cfg.readEntry ( "THEME_CONFIG_TABLE", "Skin", "" ).lower();  
    if ( installedSkin.directory.find(PATH_MMC)!=-1 )
		installedSkin.device = AM_Global::Card1;
	else
		installedSkin.device = AM_Global::Flash2;	
    installedSkin.appSize = STUFF_Global::getSize(sTemp);
    
    toLog("Check installed");
    bool bUpdateApp=false;
    {
		QDir dir;
		if ( dir.exists ( installedSkin.directory ) )
			bUpdateApp=true;
		else
		if ( dir.exists ( installedSkin.directory.replace(PATH_PHONE, PATH_MMC) ) )
		{
			installedSkin.directory = installedSkin.directory.replace(PATH_PHONE, PATH_MMC);
			bUpdateApp=true;
		}else
		if ( dir.exists ( installedSkin.directory.replace(PATH_MMC, PATH_PHONE) ) )
		{
			installedSkin.directory = installedSkin.directory.replace(PATH_MMC, PATH_PHONE);
			bUpdateApp=true;
		} 

	}
	
    toLog("Show discription app");
    {
    ZMessageDlg * dlg = new ZMessageDlg(this);
    dlg->setType(ZMessageDlg::TypeChoose);
    if ( bUpdateApp )
		dlg->setMessage( getLangLine("update").arg( installedSkin.name ).arg( installedSkin.vendor ).arg( installedSkin.date ).arg( installedSkin.appSize ) );
    else
		dlg->setMessage( getLangLine("install").arg( installedSkin.name ).arg( installedSkin.vendor ).arg( installedSkin.date ).arg( installedSkin.appSize ) );
	bCancel = dlg->exec()!=QDialog::Accepted;
	delete dlg;
	dlg=NULL;
	}
	
	if ( bCancel )
	{
		cancelInstall();
		return 0;
	}   
	
	if ( !bUpdateApp )
	{
		toLog("Get location app");
		uiDlg->installLocationDlg( installedSkin.name, 0, installedSkin.device );		
		toLog("Device id: "+QString::number( installedSkin.device ) );
				
		toLog("Set directory for MGS");
		switch ( installedSkin.device )
		{
			case AM_Global::Flash2:
				installedSkin.directory = installedSkin.directory.replace(PATH_MMC, PATH_PHONE);
				break;
			case AM_Global::Card1:
				installedSkin.directory = installedSkin.directory.replace(PATH_PHONE, PATH_MMC);
				break;
			default:
				bCancel = true;
				return "";		
		}
	}

	toLog("Check free space");	
	if ( getFileSystemFreeSize(installedSkin.device) < installedSkin.appSize && !bUpdateApp )
	{
		uiDlg->memFullDlg(installedSkin.device, installedSkin.appSize);
		cancelInstall();
		return 0;		
	}
	
	toLog("Show process dlg");
	uiDlg->initProgressBar( "", installedSkin.name, "Install" );
	uiDlg->disableProgressCancel();
	
	if ( installedSkin.directory.isEmpty() ||  bCancel )
	{
		uiDlg->invalidPkgDlg();
		cancelInstall();
		return 0;			
	}
	
	fixParamChm(&cfg, "WallPaper", installedSkin.directory);
	fixParamChm(&cfg, "PowerOffScreen", installedSkin.directory);
	fixParamChm(&cfg, "PowerOnScreen", installedSkin.directory);
	
	fixParamChm(&cfg, "MsgAlert", installedSkin.directory);
	fixParamChm(&cfg, "LightAlert", installedSkin.directory);
	fixParamChm(&cfg, "CallAlertLine1", installedSkin.directory);	
	fixParamChm(&cfg, "CallAlertLine2", installedSkin.directory);
	fixParamChm(&cfg, "CalendarAlarm", installedSkin.directory);
	fixParamChm(&cfg, "IMAlert", installedSkin.directory);
	fixParamChm(&cfg, "ScreenSaver", installedSkin.directory);
	fixParamChm(&cfg, "CLIScreenSaver", installedSkin.directory);
	
	cfg.flush();
	
	uiDlg->setProgressBar( 8 );
	qApp->processEvents();		
	
	toLog("Create dir");
	if ( !bUpdateApp )
	{
		QDir dir;
		if ( !dir.exists ( installedSkin.directory ) ) 
			system( QString( "mkdir -p %1" ).arg( installedSkin.directory ).utf8() );
	}
	
	uiDlg->setProgressBar( 5 );
	qApp->processEvents();	
	
	toLog("Move folder");
	toLog( QString ( "cp -f %1/%2.chm %3/%4.phm" ).arg( sTemp+"/"+sTempFolder ).arg( sTempFolder ).arg( CHM_PATH ).arg( sTempFolder ).utf8() );
	system( QString ( "cp -f %1/%2.chm %3/%4.phm" ).arg( sTemp+"/"+sTempFolder ).arg( sTempFolder ).arg( CHM_PATH ).arg( sTempFolder ).utf8() );	
	toLog( QString ( "mv -f %1/%2/* %3/" ).arg( sTemp ).arg( sTempFolder ).arg( installedSkin.directory ).utf8() );
	system( QString ( "mv -f %1/%2/* %3/" ).arg( sTemp ).arg( sTempFolder ).arg( installedSkin.directory ).utf8() );
	
	uiDlg->setProgressBar( 90 );
	qApp->processEvents();	
	
	clearTmpDir(sTemp, false);
	
	uiDlg->setProgressBar( 100 );
	qApp->processEvents();	
	
	toLog("Close process dlg");
	uiDlg->close();
	
	toLog("Show dlg installed sucessful");
	uiDlg->appInstalledNoLaunchDlg( installedSkin.name );
	
	return 1;
}
