//
// C++ Implementation: ZSettigs
//
// Description:
//
// Author: Ant-ON <prozanton@gmail.com>, (C) 2009-2011
//
// Based on zSimpleGUI by BeZ
//

#include "zSettings.h"
#include "GUI_Define.h"
#include "BaseDlg.h"
#include "lng.h"

#include "UTIL_Sys.h"

#include <stdlib.h>
#include <unistd.h>
#include <qpixmap.h>

#include <ZApplication.h>
#include <ZSoftKey.h>

#include <dirent.h>
#include <fcntl.h>
#include <qevent.h>
#include <signal.h>
#include <sys/wait.h>
#include <ZConfig.h>
#include <iostream>

#include <PearlMod.h>

extern ZLng* lng;

using namespace std;

ZSettigs::ZSettigs ( QWidget* parent, const char* name, WFlags fl )
    : MyBaseDlg()
{
	ProgDir = getProgramDir();
	CreateWindow ( parent );
}

ZSettigs::~ZSettigs()
{

}

void ZSettigs::CreateWindow ( QWidget* parent )
{
	qApp->installEventFilter( this );
    
	lng->autoLoadLng();
	
	toLog(QString("CreateWindow: interface"));
	setMainWidgetTitle ( "zSettings" );

	tabWidget = new ZNavTabWidget(this);
	setContentWidget(tabWidget);
	
	lbSysOption = new ZListBox( tabWidget );
	lbToolOption = new ZListBox( tabWidget );
    lbSoundOption = new ZListBox( tabWidget );
    lbKeyOption = new ZListBox( tabWidget );   
	lbService = new ZListBox( tabWidget ); 
		
	QStringList * heapSize = new QStringList();
	heapSize->append(lng->getString("UNLIMIT"));	
	heapSize->append("512"+lng->getString("KB"));
	heapSize->append("768"+lng->getString("KB"));
	heapSize->append("1"+lng->getString("MB"));
	heapSize->append("2"+lng->getString("MB"));
	heapSize->append("4"+lng->getString("MB"));

	ZOptionItem * item = new ZOptionItem(lbSysOption, ZOptionItem::EDIT_ONE_OF_LIST, 0);
	item->setTitle(lng->getString("JAVAHEAP"));
	item->setList( heapSize );
	item->read( "/ezxlocal/download/appwrite/setup/ezx_system.cfg", "SYS_JAVA", "JavaHeapSize", 1 );
	lbSysOption->insertItem ( item,-1 );
	
	item = new ZOptionItem(lbSysOption, ZOptionItem::EDIT_NUM, 5);
	item->setTitle(lng->getString("MENU_FOCUS_ITEM"));
	item->setMaxMin( 15, 0 );	
	item->read( "/ezxlocal/download/appwrite/setup/lj_faultline.cfg", "LJ_Mainmenu", "DefaultMenuFocus", 0 );	
	lbSysOption->insertItem ( item,-1 );
	
	item = new ZOptionItem(lbSysOption, ZOptionItem::EDIT_NUM, 12);
	item->setTitle(lng->getString("TIME_ACTION_DISP"));
	item->setMaxMin( 360, 0 );
	item->read( "/ezxlocal/download/appwrite/setup/ezx_system.cfg", "SYS_SYSTEM_SET", "DisplayTimeout", 30 );
	lbSysOption->insertItem ( item,-1 );	
	
	item = new ZOptionItem(lbSysOption, ZOptionItem::EDIT_BOOL_YESNO, 10);
	item->setTitle(lng->getString("STD_SUB_MENU"));
	item->read( MOD_CONFIG, "PearlMod", "stdSubMenu", false );	
	lbSysOption->insertItem ( item,-1 );
	
	item = new ZOptionItem(lbSysOption, ZOptionItem::EDIT_FLEXBIT, 16);
	item->setTitle(lng->getString("PLAYER_VISUALIZATIONS"));
	item->readFlex( GetFlexIdByName("DL_DB_FEATURE_ID_SONIC_VISUALIZATIONS") );	
	lbSysOption->insertItem ( item,-1 );	
	
	item = new ZOptionItem(lbSysOption, ZOptionItem::EDIT_FLEXBIT, 17);
	item->setTitle(lng->getString("J2ME_VIBRATE_LIMIT"));
	item->readFlex( GetFlexIdByName("DL_DB_FEATURE_ID_J2ME_VIBRATE_LIMIT_AVAILABLE") );	
	lbSysOption->insertItem ( item,-1 );
	
	item = new ZOptionItem(lbToolOption, ZOptionItem::EDIT_BOOL_ONOFF, 1);
	connect( item, SIGNAL(aplly(int)), this, SLOT( applySetting(int) ) );
	item->setTitle(lng->getString("APMDFULL"));
	item->read( MOD_CONFIG, "PearlMod", "apmdFull", false );	
	lbToolOption->insertItem ( item,-1 );	
	
	item = new ZOptionItem(lbToolOption, ZOptionItem::EDIT_BOOL_ONOFF, 11);
	item->setTitle(lng->getString("LM_JAVA"));
	item->read( MOD_CONFIG, "PearlMod", "lmConrolInJava", false );	
	lbToolOption->insertItem ( item,-1 );
	
	item = new ZOptionItem(lbToolOption, ZOptionItem::EDIT_BOOL_ONOFF, 9);
	item->setTitle(lng->getString("AMFIX"));
	item->read( MOD_CONFIG, "PearlMod", "amFix", true );	
	lbToolOption->insertItem ( item,-1 );
		
	item = new ZOptionItem(lbSoundOption, ZOptionItem::EDIT_BOOL_ONOFF, 2);
	item->setTitle(lng->getString("USSD"));
	item->read( "/ezxlocal/download/appwrite/setup/ezx_call.cfg", "Setup", "ussd_message_alert_on_off", true );			
	lbSoundOption->insertItem ( item,-1 );
	
	item = new ZOptionItem(lbSoundOption, ZOptionItem::EDIT_BOOL_ONOFF, 3);
	connect( item, SIGNAL(aplly(int)), this, SLOT( applySetting(int) ) );
	item->setTitle(lng->getString("JAVAERROR"));
	item->read( MOD_CONFIG, "PearlMod", "soundJavaError", true );			
	lbSoundOption->insertItem ( item,-1 );
	
	#if 0
	item = new ZOptionItem(lbSoundOption, ZOptionItem::EDIT_BOOL_ONOFF, 4);
	connect( item, SIGNAL(aplly(int)), this, SLOT( applySetting(int) ) );
	item->setTitle(lng->getString("LOWBAT"));
	item->read( MOD_CONFIG, "PearlMod", "soundLowBat", true );			
	lbSoundOption->insertItem ( item,-1 );
	#endif
	
	item = new ZOptionItem(lbKeyOption, ZOptionItem::EDIT_APP_SELECT, 6);
	item->setTitle( lng->getString("BROWSER_KEY"));		
	item->read( "/ezxlocal/download/appwrite/setup/ezx_keyconfig.cfg", "Carrier", "Press-behavior", "" );
	lbKeyOption->insertItem ( item,-1 );
	
	item = new ZOptionItem(lbKeyOption, ZOptionItem::EDIT_APP_SELECT, 7);
	item->setTitle( lng->getString("BROWSER_KEY_LONG"));		
	item->read( "/ezxlocal/download/appwrite/setup/ezx_keyconfig.cfg", "Carrier", "Presshold-behavior", "" );
	lbKeyOption->insertItem ( item,-1 );
	
	item = new ZOptionItem(lbKeyOption, ZOptionItem::EDIT_APP_SELECT, 8);
	item->setTitle( lng->getString("SIDE_KEY"));		
	item->read( "/ezxlocal/download/appwrite/setup/ezx_idle.cfg", "Framework", "SideKeyApp", "" );
	lbKeyOption->insertItem ( item,-1 );		
	
	item = new ZOptionItem(lbService, ZOptionItem::EDIT_BOOL_ONOFF, 13);
	connect( item, SIGNAL(aplly(int)), this, SLOT( applySetting(int) ) );
	item->setTitle( "FTP" );		
	item->read( MOD_CONFIG, "PearlMod", "srvFTP", false );
	lbService->insertItem ( item,-1 );	
	
	item = new ZOptionItem(lbService, ZOptionItem::EDIT_BOOL_ONOFF, 14);
	connect( item, SIGNAL(aplly(int)), this, SLOT( applySetting(int) ) );
	item->setTitle( "Samba" );		
	item->read( MOD_CONFIG, "PearlMod", "srvSamba", false );
	lbService->insertItem ( item,-1 );		
	
	item = new ZOptionItem(lbService, ZOptionItem::EDIT_BOOL_ONOFF, 15);
	connect( item, SIGNAL(aplly(int)), this, SLOT( applySetting(int) ) );
	item->setTitle( "Screenshoter" );		
	item->read( MOD_CONFIG, "PearlMod", "srvScreenshoter", false );
	lbService->insertItem ( item,-1 );
	
	//max index: 17
	
	QPixmap imgTab1,imgTab2,imgTab3,imgTab4,imgTab5;
	imgTab1.load(ProgDir + "/img/tab_main.png" );
	imgTab2.load(ProgDir + "/img/tab_sound.png" );
	imgTab3.load(ProgDir + "/img/tab_key.png" );	
	imgTab4.load(ProgDir + "/img/tab_util.png" );
	imgTab5.load(ProgDir + "/img/tab_service.png" );	

	tabWidget->addTab(lbSysOption, QIconSet(imgTab1), "");
	tabWidget->addTab(lbToolOption, QIconSet(imgTab4), "");		
	tabWidget->addTab(lbSoundOption, QIconSet(imgTab2), "");
	tabWidget->addTab(lbKeyOption, QIconSet(imgTab3), "");
	tabWidget->addTab(lbService, QIconSet(imgTab5), "");	

	tabWidget->stopNextWhenKeyRepeat(true);

	lbSysOption->setFocus();
	//*********************** softkeys and menus ***********************
	toLog("CreateWindow: softkeys and menus");
	
	softKey  = new ZSoftKey("CST_2", this, this);
	softKey->setClickedSlot ( ZSoftKey::LEFT, this, SLOT ( save() ) );
	softKey->setText ( ZSoftKey::LEFT, lng->getString("SAVE"), ( ZSoftKey::TEXT_PRIORITY ) 0 );
	softKey->setClickedSlot ( ZSoftKey::RIGHT, qApp, SLOT ( quit() ) );
	softKey->setText ( ZSoftKey::RIGHT, lng->getString("EXIT"), ( ZSoftKey::TEXT_PRIORITY ) 0 );
	setSoftKey(softKey);
	
	toLog( QString("CreateWindow: end") );	
}

void ZSettigs::save()
{
	toLog( QString("save: start") );	
	
	int i;

	ZOptionItem * item;
	for ( i=0; i<lbSysOption->count(); i++ )
	{
		item = (ZOptionItem *)lbSysOption->item(i);
		if ( item )
			item->write();
	}
	for ( i=0; i<lbToolOption->count(); i++ )
	{
		item = (ZOptionItem *)lbToolOption->item(i);
		if ( item )
			item->write();
	}	
	for ( i=0; i<lbSoundOption->count(); i++ )
	{
		item = (ZOptionItem *)lbSoundOption->item(i);
		if ( item )
			item->write();
	}
	for ( i=0; i<lbKeyOption->count(); i++ )
	{
		item = (ZOptionItem *)lbKeyOption->item(i);
		if ( item )
			item->write();
	}	
	for ( i=0; i<lbService->count(); i++ )
	{
		item = (ZOptionItem *)lbService->item(i);
		if ( item )
			item->write();
	}		
	
	toLog( QString("save: end") );
	qApp->quit();
}

void ZSettigs::toLog(QString mes, bool r1, bool r2)
{
	if (r1)
		std::cout << "====================================================================" << std::endl;
	if (mes != NULL)
		std::cout << mes << std::endl;
	if (r2)
		std::cout << "====================================================================" << std::endl;
}

QString ZSettigs::getProgramDir()
{
	ProgDir = QString ( qApp->argv() [0] ) ;
	int i = ProgDir.findRev ( "/" );
	ProgDir.remove ( i+1, ProgDir.length() - i );
	toLog(ProgDir, true, true);
	return ProgDir;
}

void ZSettigs::applySetting( int id )
{
	switch (id)
	{
		case 1:
			system("/etc/initservices/services/apmd.sh restart &");	
			break;
		case 3:
		case 4:	
		case 10:	
			system("umount /usr/SYSqtapp/phone/Low_Battery.wav");
			system("umount /usr/SYSqtapp/phone/Device_Connect.wav");	
			system("umount /usr/SYSqtapp/xe/resource/skins/default/apps/mainmenu/list/list.svg");	
			system("/ezxlocal/download/mystuff/.system/zSettings/applySettings.sh&");	
			break;	
		case 13:
		case 14:	
		case 15:		
			system("/etc/initservices/services/inetd.sh restart &");	
			break;						
		default:
			break;
	}
}
