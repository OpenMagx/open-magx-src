#include "xInstaller.h"

#include <time.h>
#include <iostream>
#include <sys/vfs.h>

#include <ZConfig.h>

#include <qcopchannel_qws.h>
#include <qdir.h>
#include <qfile.h>
#include <qtextstream.h>

#include <TAPI_CLIENT_Func.h>
#include <TAPI_ACCE_Client.h>

#include <MYSTUFF_Global.h>

#include <PearlMod.h>

using namespace std;

xInstaller::xInstaller(): QWidget(NULL, "", 0)
{
	bCancel=false;
	
	uiDlg = new AM_MPKGUI();

	if ( uiDlg->isCardMounted() )
		sTemp = TEMP_MMC;
	else
		sTemp = TEMP_PHONE;

	channelStart = new QCopChannel("zPkgInstaller",this,"zPkgInstaller");
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
		dlgProc = new ZProgressDlg("zPkgInstaller", "", "", this );
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

QString xInstaller::getMgxReadConfig(QString sFile, QString key, QString def)
{
	QFile file( sFile );
    if ( file.open( IO_ReadOnly ) ) 
    {
        QTextStream stream( &file );
        stream.setEncoding( QTextStream::UnicodeUTF8 );
        QString line;
        while ( !stream.atEnd() ) 
        {
            line = stream.readLine(); // line of text excluding '\n'
			if ( line.find( key ) >= 0 && line.find( key ) < 4 )
			{
				file.close();
				return line.right(line.length()-line.find('=')-1).stripWhiteSpace();
				break;
			}
        }
        file.close();
    }
	return def;
}

double xInstaller::getFileSystemFreeSize( AM_Global::Device device )
{
	double freeSize = 0, totalSize = 0;
	STUFF_Global::getDiskSize(((device==AM_Global::Flash2)?(MOD_ROOT_PATH_PHONE):((device==AM_Global::Card1)?MOD_ROOT_PATH_MMC:"")), freeSize, totalSize);
	return freeSize;
}

QString xInstaller::getIMEI()
{
	QString result = QString::null;

	unsigned int res;
	TAPI_IMEI_NUMBER_A imei;

	TAPI_CLIENT_Init ( NULL, 0 );
	res = TAPI_ACCE_GetImei ( imei );
	if ( res == 0 ) 
	{
		QString pImei = QString::fromLatin1 ( reinterpret_cast<char*> ( imei ) );
		result = pImei;
	}
	TAPI_CLIENT_Fini();
	
	return result;
}

QString xInstaller::getPathByDevice( AM_Global::Device device )
{
	switch ( device )
	{
		case AM_Global::Flash2:
			return QString( MOD_PATH_PHONE_APP );
		case AM_Global::Card1:
			return QString( MOD_PATH_MMC_APP );
		default:
			bCancel = true;
			return "";		
	}	
}

void xInstaller::writeToRegistry( AppEntry * app )
{
	QString cfgFile;
	
	switch ( app->device )
	{
		case AM_Global::Flash2:
			cfgFile = "/ezxlocal/download/appwrite/am/InstalledDB";
			break;
		case AM_Global::Card1:
			cfgFile = "/mmc/mmca1/.system/java/CardRegistry";
			break;
		default:
			break;			
	}	
	
	ZConfig registry( cfgFile );
	registry.writeEntry(app->appId, "Name",        app->name);
	registry.writeEntry(app->appId, "ObjectType",  2);
	registry.writeEntry(app->appId, "AniIcon",     app->directory+"/"+app->aniIcon);	
	registry.writeEntry(app->appId, "AppID",       app->uid);
	registry.writeEntry(app->appId, "AppType",     app->m_type);
	registry.writeEntry(app->appId, "Args",        "");
	registry.writeEntry(app->appId, "Attribute",   1);
	registry.writeEntry(app->appId, "Directory",   app->directory);
	registry.writeEntry(app->appId, "BigIcon",     app->directory+"/"+app->bigIcon);
	registry.writeEntry(app->appId, "SimpleIcon",  app->directory+"/"+app->simpleIcon);
	registry.writeEntry(app->appId, "SVGIcon",     app->directory+"/"+app->simpleIcon);
	registry.writeEntry(app->appId, "Icon",        app->directory+"/"+app->simpleIcon);
	registry.writeEntry(app->appId, "Daemon",      1);
	registry.writeEntry(app->appId, "ExecId",      app->exec);
	registry.writeEntry(app->appId, "GroupID",     "root");
	registry.writeEntry(app->appId, "UserID",      "root");
	registry.writeEntry(app->appId, "LockEnabled", 0);	
	registry.writeEntry(app->appId, "Erasable",    app->isErasable);
	registry.writeEntry(app->appId, "Shared",      app->isShared);
	registry.writeEntry(app->appId, "Vendor",      app->vendor);
	registry.writeEntry(app->appId, "Version",     app->version);
	registry.writeEntry(app->appId, "Size",        app->appSize);
	
	QDate d = QDateTime::currentDateTime().date();
	QString sDate;
	sDate.sprintf("%.4d/%.2d/%.2d",d.year(),d.month(),d.day());
	
	registry.writeEntry ( app->appId, "InstalledDate", sDate );

	if ( app->device == AM_Global::Card1 )
	{
		QString imei = getIMEI();
		registry.writeEntry ( app->appId, "IMEI", imei );
		
		ZConfig regconf("/mmc/mmca1/.system/java/MemoryCardConfig");
		regconf.writeEntry ( app->appId, "IMEI", imei );
		regconf.writeEntry ( app->appId, "Folder", app->parentFolderUid);
		regconf.flush();
	}
	registry.flush();
	
	ZConfig userMenuTree ( "/ezxlocal/download/appwrite/am/UserMenuTree" );
	QString list = userMenuTree.readEntry(app->parentFolderUid, "Items", "");
	if ( !list.endsWith(";") )
		list=list+";";
	if ( list.find(app->appId+";")==-1 )
	{
		//write change
		userMenuTree.writeEntry(app->parentFolderUid, "Items", list+app->appId+";");
		userMenuTree.flush();
		//update menu
		QByteArray data;
		QDataStream stream(data, IO_WriteOnly);
		stream << getpid() << app->appId << app->parentFolderUid << app->position << false;
		QCopChannel::send("AM/AppRegistry/Channel", "appApplicatonObject()", data);	
	}
}

void xInstaller::extAssign( AppEntry * app, QStringList slExt )
{
	toLog( "@ extAssign" );
	
	QStringList::Iterator it;
	
	QStringList slTypes;
	slTypes.clear();
	
	QFile file( MOD_MIME_TYPE );
	
    if ( !file.open( IO_ReadWrite ) )
		return;

	toLog( "Find exist type" );
	QTextStream stream( &file );
	QString line;
	while ( !stream.atEnd() ) 
	{
		line = stream.readLine(); // line of text excluding '\n'
		for ( int i=slExt.count()-1; i>=0; i-- ) 
		{
			it = slExt.at(i);
			if ( line.find( *it, line.find(" ") ) > 0 )
			{
				slTypes.append( line.left( line.find(" ") ) );
				slExt.remove( it );
			}
		}
	}
	
	toLog( "write ne types" );
	QString types;
	for ( it = slExt.begin(); it != slExt.end(); ++it ) 
	{
		types = "file/x-" + *it; 
		slTypes.append( types );
		stream << (types + " " + *it + "\n");
	}
	
	file.close();
	
	toLog( "write user mime" );
	ZConfig userMime ( MOD_USER_MIME );
	for ( it = slTypes.begin(); it != slTypes.end(); ++it ) 
	{
		userMime.writeEntry ( *it, "AppList", app->appId+";");
		userMime.writeEntry ( *it, "AppID", app->appId);
	}
	userMime.flush();
	
	toLog( "Send update mime" );
	QCopChannel::send("/AM/MimeRegistry", "update()");
}

void xInstaller::cancelInstall()
{
	clearTmpDir(sTemp, false);
}

QString xInstaller::fixIconName( QString name, QString path )
{
	if ( name.find("usr")==-1 )
	{
		int n = name.findRev(".");
		QString newName = name;
		newName = newName.insert((n>=0)?n:0, "_usr");
		system( QString("mv %1/%2 %3/%4").arg(path).arg(name).arg(path).arg(newName).utf8() );
		name = newName;
	}
	return name;
}

QString xInstaller::fixIconToSmall( QString name, QString path )
{
	QImage * image = new QImage( QString("%3/%4").arg(path).arg(name).utf8(), "PNG" );
	if ( image->height() > 18 || image->width() > 18 )
	{
		QImage icon = image->smoothScale(18, 18);
		int n = name.findRev(".");
		name = name.insert((n>=0)?n:0, "_s");
		icon.save( QString("%3/%4").arg(path).arg(name).utf8(), "PNG" );
	}
	delete image;
	return name;
}

QString xInstaller::fixDirectoryName( QString installTo )
{
	toLog("Fix path for create folder");
	while ( installTo.left ( 3 ) == "../" )
			installTo.prepend ( "/" );
	if ( installTo.right ( 2 ) == "//" )
		installTo.remove ( installTo.length()-2, 2 );
	else if ( installTo.right ( 1 ) == "/" )
		installTo.remove ( installTo.length()-1, 1 );
	return installTo;
}


bool xInstaller::run( QString sPakgPath )
{
	QCopChannel::send( "zPkgInstaller", "proc_show()" );
	qApp->processEvents();
	qApp->processEvents();
	//unpack pack
	{
		createTmpDir(sTemp);
		system( QString(PATH_7Z).arg( sPakgPath ).arg( sTemp ).utf8() );
		
		QString tarName = sPakgPath.right( sPakgPath.length() - sPakgPath.findRev('/') );
		tarName = tarName.left( tarName.findRev('.') );
		toLog( "Check tar: " + sTemp+tarName );
		if ( QFile::exists( sTemp+tarName ) )
		{
			system( QString(PATH_7Z).arg( sTemp+tarName ).arg( sTemp ).utf8() );	
			system( QString("rm %1").arg( sTemp+tarName ).utf8() );	
		}
		tarName = tarName +".tar";
		toLog( "Check tar: " + sTemp+tarName );
		if ( QFile::exists( sTemp+tarName ) )
		{
			system( QString(PATH_7Z).arg( sTemp+tarName ).arg( sTemp ).utf8() );	
			system( QString("rm %1").arg( sTemp+tarName ).utf8() );	
		}		
	}
	QCopChannel::send( "zPkgInstaller", "proc_hide()" );	
	
	//detect pak type
	PAK_TYPE type = PAK_UNKNOWN;
	QString sFolder;
	if ( QFile::exists( sTemp + "/description.ini" ) )
		type = PAK_PEP;
	else
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
				sFolder = *it;
				toLog( QString( "Maybe pak folder:" ) + sFolder );
				if ( QFile::exists( sTemp + "/"+sFolder+"/"+sFolder+".cfg" ) )
					type = PAK_MGX;
			}
			it++;
		}
	}
	if ( type == PAK_UNKNOWN || bCancel )
	{
		toLog("Error: not detected pak type!");
		uiDlg->corruptFileDlg();
		cancelInstall();
		return 0;
	}
	
	toLog("Create discription app");
	AppEntry installedApp;
	installedApp.uid = AM_Global::createUuid();
	installedApp.appId = QString(installedApp.uid).right(37).left(36);
    installedApp.isLockEnabled = false;
    installedApp.isShared = false;
    installedApp.isErasable = true;
    installedApp.parentFolderUid = "abc9ddaa-6643-429b-9844-8dc429829417";
    installedApp.position = -1;
    installedApp.m_type = AM_AppLnk::NativeApp;
    
    #define toUTF8(a) QString::fromUtf8((a).utf8())
    switch ( type )
    {
		case PAK_PEP:
		{
			ZConfig cfg( sTemp + "/description.ini" );
			
			if ( cfg.readBoolEntry ( "Actions", "InstallApp", false ) )
			{
				installedApp.directory = fixDirectoryName( toUTF8(cfg.readEntry("InstallApp", "InstallPath", "")) );
				installedApp.bigIcon = fixIconName( toUTF8(cfg.readEntry("InstallApp", "BigIcon", "")), sTemp+"/app");
				installedApp.smallIcon = fixIconToSmall(fixIconName( toUTF8(cfg.readEntry("InstallApp", "Icon", "")), sTemp+"/app"), sTemp+"/app");
				installedApp.aniIcon = fixIconName( toUTF8(cfg.readEntry("InstallApp", "AniIcon", "" )), sTemp+"/app");
				installedApp.simpleIcon = toUTF8(installedApp.smallIcon);
				installedApp.name = toUTF8(cfg.readEntry("InstallApp", "Name", ""));
				installedApp.vendor = toUTF8(cfg.readEntry("InstallApp", "Author", ""));
				installedApp.nameResourceId = "";
				installedApp.version = toUTF8(cfg.readEntry ("InstallApp", "Version", ""));
				installedApp.exec = toUTF8(cfg.readEntry("InstallApp", "Exec", ""));
				installedApp.device = (installedApp.directory.find("/mmc/")==-1)?AM_Global::Flash2:AM_Global::Card1;
			} else
			if ( cfg.readBoolEntry ( "Actions", "UpdatePak", false ) )
			{
				installedApp.directory = fixDirectoryName( toUTF8(cfg.readEntry("UpdatePak", "InstallPath", "")) );
				installedApp.name = toUTF8(cfg.readEntry("UpdatePak", "Name", ""));
				installedApp.vendor = toUTF8(cfg.readEntry("UpdatePak", "Author", ""));
				installedApp.version = cfg.readEntry ( "UpdatePak", "Version", "" );
				installedApp.device = (installedApp.directory.find("/mmc/")==-1)?AM_Global::Flash2:AM_Global::Card1;
				type = PAK_PEP_UPDATE;
			}			
			break;
		}
		case PAK_MGX:
		{
			QString cfg = sTemp + "/"+sFolder+"/"+sFolder+".cfg";
			installedApp.directory = "";
			installedApp.name = toUTF8(getMgxReadConfig(cfg, "Name", ""));
			installedApp.vendor = toUTF8(getMgxReadConfig(cfg, "Author", ""));
			installedApp.nameResourceId = "";
			installedApp.version = toUTF8(getMgxReadConfig(cfg, "Version", ""));
			installedApp.exec = toUTF8(getMgxReadConfig(cfg, "Exec", ""));
			installedApp.bigIcon = fixIconName( toUTF8(getMgxReadConfig(cfg, "Icon", "")), sTemp + "/"+sFolder);
			installedApp.aniIcon = installedApp.bigIcon;
			installedApp.smallIcon = fixIconToSmall(installedApp.bigIcon, sTemp + "/"+sFolder);
			installedApp.simpleIcon = installedApp.smallIcon;
			break;
		}
		default:
			break;		
	}
    installedApp.appSize = STUFF_Global::getSize(sTemp);
    
    toLog("Check installed");
    bool bUpdateApp=false;
    QString sOldVersion="";
    
    if ( type == PAK_MGX || type == PAK_PEP )
    {
		ZConfig PhoneRegistry ( "/ezxlocal/download/appwrite/am/InstalledDB" );
		QStringList grouplist;
		PhoneRegistry.getGroupsKeyList( grouplist );
        for ( QStringList::Iterator it = grouplist.begin(); it != grouplist.end(); ++it ) 
        {
			if ( PhoneRegistry.readEntry( *it, "Name", "" ) == installedApp.name )
			{
				sOldVersion = PhoneRegistry.readEntry( *it, "Version", "" );
				installedApp.uid = QUuid(PhoneRegistry.readEntry( *it, "AppID", "" ));
				installedApp.appId = *it;
				installedApp.directory = PhoneRegistry.readEntry( *it, "Directory", "" );
				installedApp.device = AM_Global::Flash2;
				bUpdateApp=true;
				break;
			}
        }	
        if ( !bUpdateApp && uiDlg->isCardMounted() )
        {
			ZConfig CardRegistry ( "/mmc/mmca1/.system/java/CardRegistry" );
			CardRegistry.getGroupsKeyList( grouplist );
			for ( QStringList::Iterator it = grouplist.begin(); it != grouplist.end(); ++it ) 
			{
				if ( CardRegistry.readEntry( *it, "Name", "" ) == installedApp.name )
				{
					sOldVersion = CardRegistry.readEntry( *it, "Version", "" );
					installedApp.uid = QUuid(CardRegistry.readEntry( *it, "AppID", "" ));
					installedApp.appId = *it;
					installedApp.directory = CardRegistry.readEntry( *it, "Directory", "" );
					installedApp.device = AM_Global::Card1;
					bUpdateApp=true;
					break;
				}
			}				
		}
	} else
		sOldVersion="-";
	
    toLog("Show discription app");
    if ( bUpdateApp || type == PAK_PEP_UPDATE )
		bCancel = uiDlg->updateDlg(installedApp.name, sOldVersion, installedApp.version );
    else
		bCancel = uiDlg->appDetailsCardDlg("", installedApp.name, installedApp.vendor, installedApp.version, QString::number(installedApp.appSize) );
	
	if ( bCancel )
	{
		cancelInstall();
		return 0;
	}   
	
	if ( type == PAK_MGX && !bUpdateApp )
	{
		toLog("Get location app");
		uiDlg->installLocationDlg( installedApp.name, 0, installedApp.device );		
		toLog("Device id: "+QString::number( installedApp.device ) );
				
		toLog("Set directory for MGX");
		installedApp.directory = getPathByDevice(installedApp.device)+"/"+sFolder;
	}

	toLog("Check free space");	
	if ( getFileSystemFreeSize(installedApp.device) < installedApp.appSize && !bUpdateApp )
	{
		uiDlg->memFullDlg(installedApp.device, installedApp.appSize);
		cancelInstall();
		return 0;		
	}
	
	toLog("Show process dlg");
	uiDlg->initProgressBar( "", installedApp.name, "Install" );
	uiDlg->disableProgressCancel();
	
	if ( installedApp.directory.isEmpty() ||  bCancel )
	{
		uiDlg->invalidPkgDlg();
		cancelInstall();
		return 0;			
	}
	
	uiDlg->setProgressBar( 5 );
	qApp->processEvents();	
	
	toLog("Move folder");
    switch ( type )
    {
		case PAK_PEP:
		case PAK_PEP_UPDATE:
		{
			ZConfig cfg( sTemp + "/description.ini" );
			//if no need add app to menu => this pakege = update pakege
			if ( !cfg.readBoolEntry( "Actions", "AddAppToMenu", true ) ) 
				type = PAK_PEP_UPDATE;
			if ( cfg.readBoolEntry( "Actions", "PreInstall", false ) )
				system( (sTemp+"/scripts/"+cfg.readEntry( "PreInstall", "Name", "" )).utf8() );		
			
			QDir dir;
			if ( dir.exists ( installedApp.directory ) )
			{			
				system( QString ( "cp -rf %1/app/* %2" ).arg( sTemp ).arg( installedApp.directory ).utf8() );	
				system( QString ( "cp -rf %1/app/.[!.]* %2" ).arg( sTemp ).arg( installedApp.directory ).utf8() );
			} else
			{
				system( QString( "mkdir -p %1" ).arg( installedApp.directory ).utf8() );
				system( QString ( "mv -f %1/app/* %2" ).arg( sTemp ).arg( installedApp.directory ).utf8() );	
				system( QString ( "mv -f %1/app/.[!.]* %2" ).arg( sTemp ).arg( installedApp.directory ).utf8() );				
			}			
			//system( QString ( "mv -f %1/app/* %2" ).arg( sTemp ).arg( installedApp.directory ).utf8() );	
			//system( QString ( "mv -f %1/app/.[!.]* %2" ).arg( sTemp ).arg( installedApp.directory ).utf8() );
			//system( QString ( "cd %1; mkdir -p `find -type d | sed -e 's|\\./|%2/|'`; busybox_full find . -type f -exec mv -f '{}' '%3/{}' \\;" ).arg( sTemp+"/app" ).arg( installedApp.directory ).arg( installedApp.directory ).utf8() );
			//toLog( QString ( "cd %1; mkdir -p `find -type d | sed -e 's|\\./|%2/|'`; busybox_full find . -type f -exec mv -f '{}' '%3/{}' \\;" ).arg( sTemp+"/app" ).arg( installedApp.directory ).arg( installedApp.directory ).utf8() );
			if ( type != PAK_PEP_UPDATE )
			{
				if ( !installedApp.bigIcon.isEmpty() ) system( QString ( "mv -f %1/%2 %3/%4" ).arg( sTemp ).arg( installedApp.bigIcon ).arg( installedApp.directory ).arg( installedApp.bigIcon ).utf8() );
				if ( !installedApp.smallIcon.isEmpty() ) system( QString ( "mv -f %1/%2 %3/%4" ).arg( sTemp ).arg( installedApp.smallIcon ).arg( installedApp.directory ).arg( installedApp.smallIcon ).utf8() );
				if ( !installedApp.aniIcon.isEmpty() ) system( QString ( "mv -f %1/%2 %3/%4" ).arg( sTemp ).arg( installedApp.aniIcon ).arg( installedApp.directory ).arg( installedApp.aniIcon ).utf8() );
			}
			
			if ( cfg.readBoolEntry( "Actions", "AssignExt", false ) )
				extAssign( &installedApp, QStringList::split(";", cfg.readEntry("AssignExt", "Ext", "")) );
			break;
		}
		
		case PAK_MGX:
		{
			QDir dir;
			if ( dir.exists ( installedApp.directory ) )
			{
				system( QString ( "cp -rf %1/%2/* %3/" ).arg( sTemp ).arg( sFolder ).arg( installedApp.directory ).utf8() );
				system( QString ( "cp -rf %1/%2/.[!.]* %3/" ).arg( sTemp ).arg( sFolder ).arg( installedApp.directory ).utf8() );	
			} else
			{
				system( QString( "mkdir -p %1" ).arg( installedApp.directory ).utf8() );
				system( QString ( "mv -f %1/%2/* %3/" ).arg( sTemp ).arg( sFolder ).arg( installedApp.directory ).utf8() );
				system( QString ( "mv -f %1/%2/.[!.]* %3/" ).arg( sTemp ).arg( sFolder ).arg( installedApp.directory ).utf8() );					
			}
			
			//system( QString ( "cd %1; mkdir -p `find -type d | sed -e 's|\\./|%2/|'`; busybox_full find . -type f -exec mv -f '{}' '%3/{}' \\;" ).arg( sFolder ).arg( installedApp.directory ).arg( installedApp.directory ).utf8() );
			//toLog( QString ( "cd %1; mkdir -p `find -type d | sed -e 's|\\./|%2/|'`; busybox_full find . -type f -exec mv -f '{}' '%3/{}' \\;" ).arg( sFolder ).arg( installedApp.directory ).arg( installedApp.directory ).utf8() );
			break;
		}
		default:
			break;	
	}
	
	uiDlg->setProgressBar( 50 );
	qApp->processEvents();

	toLog(QString("Set chmod: ")+installedApp.directory+"/"+installedApp.exec );
	system ( QString( "chmod a+x %1/%2" ).arg( installedApp.directory ).arg( installedApp.exec ).utf8() );
	
	//Fix bad chinese script
	if ( installedApp.exec.endsWith(".sh") || installedApp.exec.endsWith(".lin") )
	{
		FILE * f = fopen( installedApp.directory+"/"+installedApp.exec, "rt" );
		if ( f )
		{
			fseek(f, 0, SEEK_END);
			int iFileSize = ftell(f);
			char * text = (char *)malloc(sizeof(char)*iFileSize);
			fseek(f, 0, SEEK_SET);		
			fread(text, sizeof(char), iFileSize, f);
			fclose(f);		
			int startId=0;
			while ( startId<iFileSize && *(text+startId) != '#' ) 
			{
				if ( *(text+startId) == 0x0A )
				{
					startId=-1;
					break;
				}
				startId++;
			}
			if ( startId > 0 )
			{
				f = fopen( installedApp.directory+"/"+installedApp.exec, "wt" );
				fwrite(text+3, sizeof(char), iFileSize-3, f); // 3 ??? maybe need change 3 to startId ???
				fclose(f);
			}
			free(text);
		}
	}
	
	uiDlg->setProgressBar( 55 );
	qApp->processEvents();
	
	if ( type != PAK_PEP_UPDATE )
	{
		toLog("Write info about program to registry");
		writeToRegistry( &installedApp );
	}
	
	toLog("Run post install script");
    switch ( type )
    {
		case PAK_PEP:
		case PAK_PEP_UPDATE:
		{
			ZConfig cfg( sTemp + "/description.ini" );
			if ( cfg.readBoolEntry( "Actions", "PostInstall", false ) )
				system( sTemp+"/scripts/"+cfg.readEntry( "PostInstall", "Name", "" )+"&" );			
			break;
		}
		default:
			break;	
	}
	
	uiDlg->setProgressBar( 90 );
	qApp->processEvents();	
	
	clearTmpDir(sTemp, false);
	
	uiDlg->setProgressBar( 100 );
	qApp->processEvents();	
	
	toLog("Close process dlg");
	uiDlg->close();
	
	toLog("Show dlg installed sucessful");
	uiDlg->appInstalledNoLaunchDlg( installedApp.name );
	
	return 1;
}
