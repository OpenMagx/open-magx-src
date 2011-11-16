//
// C++ Implementation: ZCardAppRepair
//
// Description:
//
//
// Author: Ant-ON <prozanton@gmail.com>, (C) 2009
//
//
#include <ZApplication.h>
#include <ZMessageDlg.h>

#include <qcopchannel_qws.h>
#include <qstring.h>
#include <qapplication.h>

#include <iostream>

#define MENU_TREE_FILE "/ezxlocal/download/appwrite/am/UserMenuTree"
#define LNG_PATH "/ezxlocal/download/mystuff/.system/lng/zCardAppRepair/all.lng"

ZApplication* app;

using namespace std;

int main ( int argc, char **argv )
{
	app = new ZApplication ( argc, argv );
	cout << "zCardAppRepair by Ant-ON" << endl;
	cout << "version: 0.2" << endl;

	#ifndef EZX_VE66
	QString curLng;
	if ( QString(argv[1]) != QString("-yes") )
	{
		ZConfig cfg( "/ezxlocal/download/appwrite/setup/ezx_system.cfg" );
		curLng = cfg.readEntry(QString("SYS_SYSTEM_SET"), QString("LanguageType"), "en");
		if ( curLng.length() > 1 )
			curLng = QString(curLng[0]) + QString(curLng[1]);
		
		ZConfig lng( LNG_PATH );
		
		ZMessageDlg * dlg = new ZMessageDlg("zCardAppRepair", 
											QString::fromUtf8(lng.readEntry("question", curLng, "Restore the application from the memory card to menu?").utf8()),
											ZMessageDlg::TypeConfirm);
		if ( !dlg->exec() )
			return 0;
	}
	#endif
	
	cout << "Read all file" << endl;
	
	QFile file ( MENU_TREE_FILE );
	file.open( IO_ReadOnly );
	char * data = (char*)malloc(file.size());
	file.readBlock(data, sizeof(data));
	QString allItem = QString( data );
	free(data);
	file.close();
	
	cout << "Read file" << endl;
	
    ZConfig cfg( MENU_TREE_FILE );
    #ifndef EZX_VE66
    QString Java = cfg.readEntry( "67dc1191-2928-4938-abce-1a73cb5ce490", "Items", "");
    #endif
    QString Nativ = cfg.readEntry( "abc9ddaa-6643-429b-9844-8dc429829417", "Items", "");
    
    int count=0;
    
	ZConfig config ( "/mmc/mmca1/.system/java/CardRegistry", false );
	QStringList grouplist;
	config.getGroupsKeyList ( grouplist );
	for ( QStringList::Iterator it = grouplist.begin(); it != grouplist.end(); ++it ) 
	{
		#ifndef EZX_VE66
		if ( config.readNumEntry ( *it, "JavaId", 0 ) > 0 || config.readEntry ( *it, "Exec", "unknown" ) == "java.sh"  )
		{
			
			if ( Java.find(*it) == -1 && allItem.find(*it) == -1 )
			{
				cout << "Add Java to list: " << QString::fromUtf8(config.readEntry ( *it, "Name", "unknown" )) << endl;
				Java = Java + *it + ";";
				count++;
			}
		} else
		#else
		if ( config.readNumEntry( *it, "AppType", 0 ) == 0 )
		#endif
		{
			if ( Nativ.find(*it) == -1 && allItem.find(*it) == -1 )
			{
				cout << "Add Nativ to list: " << QString::fromUtf8(config.readEntry ( *it, "Name", "unknown" )) << endl;
				Nativ = Nativ + *it + ";";
				count++;
			}			
		}
	}
	
	cout << "Change apply" << endl;
	#ifndef EZX_VE66
	cfg.writeEntry( "67dc1191-2928-4938-abce-1a73cb5ce490", "Items", Java);
	#endif
	cfg.writeEntry( "abc9ddaa-6643-429b-9844-8dc429829417", "Items", Nativ);	
    cfg.flush();
	
	#ifndef EZX_VE66
    {
		QStringList uidList = QStringList::split ( ";", Java );
    	QByteArray data;
    	QDataStream stream(data, IO_WriteOnly);
    	stream << getpid() << "67dc1191-2928-4938-abce-1a73cb5ce490" << uidList;
    	QCopChannel::send("AM/AppRegistry/Channel", "updateFolderOrder()", data); 
	}
    {
		QStringList uidList = QStringList::split ( ";", Nativ );
    	QByteArray data;
    	QDataStream stream(data, IO_WriteOnly);
    	stream << getpid() << "abc9ddaa-6643-429b-9844-8dc429829417" << uidList;
    	QCopChannel::send("AM/AppRegistry/Channel", "updateFolderOrder()", data); 
	}  
	
	if ( QString(argv[1]) != QString("-yes") )
	{
		ZConfig lng( LNG_PATH );
		ZMessageDlg * dlg = new ZMessageDlg("zCardAppRepair", 
											QString::fromUtf8(lng.readEntry("done", curLng, "Done. Restored: %1 application.").utf8()).arg(count),
											ZMessageDlg::TypeOK);
		dlg->exec();
	}	
	#endif
	
    cout << "Done" << endl;
	delete app;
	app = NULL;
	return 1;
}
