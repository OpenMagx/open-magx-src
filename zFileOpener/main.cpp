//
// C++ Implementation: zFileOpener 0.2
//
// Description:
//
//
// Author: Ant-ON <prozanton@gmail.com>, (C) 2010
//
//
#include <ZApplication.h>

#include <iostream>

#include <qstring.h>
#include <qstringlist.h>

#include <ZMessageDlg.h>
#include <ZSingleSelectDlg.h>
#include <ZProgressDlg.h>

ZApplication* app;

using namespace std;

#define LNG_PATH QString("/ezxlocal/download/mystuff/.system/lng/zFileOpener")
#define PATH_7Z "/usr/mbin/7z x %1 -o%2"

static ZConfig * cLng = 0;

QString getLangLine( QString sFrase )
{
	if ( !cLng )
	{
		QString curLng;
		ZConfig cfg( "/ezxlocal/download/appwrite/setup/ezx_system.cfg" );
		curLng = cfg.readEntry(QString("SYS_SYSTEM_SET"), QString("LanguageType"), "");
		if ( curLng.length() > 1 )
			curLng = QString(curLng[0]) + QString(curLng[1]);
		cLng = new ZConfig( LNG_PATH+"/"+curLng+".lng" );	
	}

	
	return QString::fromUtf8(cLng->readEntry(QString("mes"), sFrase, sFrase).utf8()).replace("/n","\n");
}

int main ( int argc, char **argv )
{
	app = new ZApplication ( argc, argv );
	cout << "zFileOpener 0.2 by Ant-ON" << endl;

	if ( argc > 1 )
	{
		QString sFile;
		if (argc > 2) 
			sFile = argv[2];
		else
			sFile = argv[1];
		QString sExt = sFile.right(4);
		if ( sFile.right(3)==".sh" || sExt==".lin" )
		{
			ZMessageDlg * dlg = new ZMessageDlg();
			dlg->setType(ZMessageDlg::TypeConfirm);
			dlg->setMessage( getLangLine("runSh").arg( sFile.right( sFile.length()-sFile.findRev("/")-1 ) ) );
			if ( dlg->exec() == QDialog::Accepted )
				system( sFile+"&" );
			delete dlg;
			dlg=NULL;
		} else
		if ( sFile.right(3)==".7z" || sExt==".rar" || sExt==".zip" || sExt==".tgz" || sExt==".tar" || sExt==".bz2" || sExt==".rpm" || sFile.right(3)==".gz" || sFile.right(5)==".gtar" )
		{
			QString dir = sFile.left( sFile.findRev("/")+1 );
			QString newDir = sFile.right( sFile.length()-sFile.findRev("/")-1 );
			newDir = newDir.left( newDir.findRev(".") );
			
			ZSingleSelectDlg * dlg = new ZSingleSelectDlg( "", getLangLine("extarctTo") );
			QStringList list;
			list.append( getLangLine("curDir") );
			list.append( getLangLine("fileNameDir").arg(newDir) );	
			dlg->addItemsList( list );
			if ( dlg->exec() == QDialog::Accepted )
			{
				ZProgressDlg* dlgProc = new ZProgressDlg("", getLangLine("mesExtract"), "" );
				dlgProc->show();
				qApp->processEvents();
				qApp->processEvents();
				switch ( dlg->getCheckedItemIndex() )
				{
					case 0:
						system( QString(PATH_7Z).arg( sFile ).arg( dir ).utf8() );
						break;
					case 1:
						system( QString( "mkdir -p %1" ).arg( dir+newDir ).utf8() );
						qApp->processEvents();
						system( QString(PATH_7Z).arg( sFile ).arg( dir+newDir ).utf8() );					
						break;
					default:
						break;
				}
				qApp->processEvents();
				dlgProc->hide();
				qApp->processEvents();
				delete dlgProc;
			}
			delete dlg;
			dlg=NULL;			
		}
	}

	cout << "Exit app" << endl;
	delete app;
	app = NULL;
	return 1;
}
