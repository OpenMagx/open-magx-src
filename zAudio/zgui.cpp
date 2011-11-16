//
// Poject name: zAudio
//
// Version: 0.1
//
// Description: Programm for change audio settings
//
// Author: Ant-ON <prozanton@gmail.com>, (C) 2010
//

#include "zgui.h"

#include "stdio.h"
#include <stdlib.h>
#include <unistd.h>
#include <qpixmap.h>

#include <ZApplication.h>
#include <ZListBox.h>
#include <ZSoftKey.h>
#include <ZOptionsMenu.h>
#include <ZFormContainer.h>
#include <ZMessageDlg.h>
#ifndef EZX_Z6
#include <ZListBoxItem.h>
#endif
#include "ZOptionItem.h"

#include "gainText.h"

ZGui::ZGui ( QWidget* parent, const char* name, WFlags fl )
    : ZKbMainWidget ( ZHeader::MAINDISPLAY_HEADER, NULL, "ZMainWidget", 0 )
{
	printf("\nzAudio by Ant-ON\nVersion 0.1\n\n");
	
	gainTable = NULL;
	CreateWindow ( parent );
	show();
}

ZGui::~ZGui()
{
	if ( gainTable )
		free(gainTable);
}

void ZGui::CreateWindow ( QWidget* parent )
{
	setMainWidgetTitle ( "zAudio" );
	tabWidget = new ZNavTabWidget(this);
	setContentWidget ( tabWidget );
	gainTable = NULL;
	
	readFile();
	
	int i;
	
	#ifdef VOLUME_TABLE
	lbMedia = new ZListBox ( QString ( "%M" ), this, 0);
	lbMedia->setFixedWidth ( SCREEN_WIDTH );
	
	lbAlarm = new ZListBox ( QString ( "%M" ), this, 0);
	lbAlarm->setFixedWidth ( SCREEN_WIDTH );
	#endif
	
	lbEqHP = new ZListBox ( QString ( "%M" ), this, 0);
	lbEqHP->setFixedWidth ( SCREEN_WIDTH );
	
	lbEqSP = new ZListBox ( QString ( "%M" ), this, 0);
	lbEqSP->setFixedWidth ( SCREEN_WIDTH );
	
	lbMenu = new ZListBox ( QString ( "%M" ), this, 0);
	lbMenu->setFixedWidth ( SCREEN_WIDTH );
	
	ZFormContainer * formHP = new ZFormContainer(this);
	cbEgHPlist = new ZComboBox( false, formHP ); 
	for (i=0;i<GAIN_EQUALASER_COUNT;i++) if ( !hideEqList[i] ) cbEgHPlist->insertItem( QObject::tr(eqList[i][0], eqList[i][1]) );
	formHP->addChild(cbEgHPlist);
	formHP->addChild(lbEqHP);

	ZFormContainer * formSP = new ZFormContainer(this);
	cbEgSPlist = new ZComboBox( false, formSP ); 
	for (i=0;i<GAIN_EQUALASER_COUNT;i++) if ( !hideEqList[i] ) cbEgSPlist->insertItem( QObject::tr(eqList[i][0], eqList[i][1]) );
	formSP->addChild(cbEgSPlist);
	formSP->addChild(lbEqSP);	
	
	#ifdef VOLUME_TABLE
    lbDevice[0] = lbMedia;
    lbDevice[1] = lbAlarm;	
    #endif
    lbDevice[2] = lbEqHP;
    lbDevice[3] = lbEqSP;	  
	
	getProgramDir();
	
	QPixmap imgTab0;
	imgTab0.load(ProgDir + "/png/favorits.png" );
	tabWidget->addTab(lbMenu, imgTab0, "");	
	#ifdef VOLUME_TABLE
	QPixmap imgTab1,imgTab2;
	imgTab1.load(ProgDir + "/png/alert.png" );
	imgTab2.load(ProgDir + "/png/media.png" );
	tabWidget->addTab(lbDevice[0], imgTab1, "");
	tabWidget->addTab(lbDevice[1], imgTab2, "");
	#endif
	QPixmap imgTab3,imgTab4;
	imgTab3.load(ProgDir + "/png/equaliser_sp.png" );
	imgTab4.load(ProgDir + "/png/equaliser_hp.png" );
	tabWidget->addTab(formSP, imgTab3, "");
	tabWidget->addTab(formHP, imgTab4, "");	

	QPixmap imgItem0, imgItem1, imgItem2;
	imgItem0.load(ProgDir + "/png/save.png" );	
	imgItem1.load(ProgDir + "/png/reboot.png" );
	imgItem2.load(ProgDir + "/png/restore.png" );

	ZListBoxItem * mItem;
	mItem = new ZListBoxItem(lbMenu, "%M");
	mItem->appendSubItem(0, "\tzAudio 0.1 by Ant-ON" );	
	mItem->setSelectable(false);
	lbMenu->insertItem( mItem );
	mItem = new ZListBoxItem(lbMenu, "%I32%M");
	mItem->setPixmap( 0, imgItem0 );
	mItem->appendSubItem(1, QObject::tr("TXT_RID_CLI_SOFTKEY_SAVE","Save"));
	lbMenu->insertItem( mItem );	
	mItem = new ZListBoxItem(lbMenu, "%I32%M");
	mItem->setPixmap( 0, imgItem1 );
	mItem->appendSubItem(1, QObject::tr("TXT_RID_OPTION_REFRESH_VIEW","Reboot"));
	lbMenu->insertItem( mItem );
	mItem = new ZListBoxItem(lbMenu, "%I32%M");
	mItem->setPixmap( 0, imgItem2 );
	mItem->appendSubItem(1, QObject::tr("TXT_RID_HEADER_RESTORE_SOUND_SETTINGS","Restore"));
	lbMenu->insertItem( mItem );
		
	connect( cbEgHPlist, SIGNAL ( activated( int ) ), this, SLOT ( slotChangeEqHP( int ) ) );
	connect( cbEgSPlist, SIGNAL ( activated( int ) ), this, SLOT ( slotChangeEqSP( int ) ) );
	connect( lbMenu, SIGNAL ( returnPressed( int ) ), this, SLOT ( slotChangeMenu( int ) ) );
	
	updateView();
	
	lbMenu->setFocus();
	
	ZSoftKey* softKey = new ZSoftKey("CST_2", this, this);
	softKey->setClickedSlot ( ZSoftKey::LEFT, this, SLOT ( save() ) );
	softKey->setClickedSlot ( ZSoftKey::RIGHT, qApp, SLOT ( quit() ) );
	softKey->setText ( ZSoftKey::LEFT, tr("TXT_RID_OPTION_SAVE", "Save" ), ( ZSoftKey::TEXT_PRIORITY ) 0 );
	softKey->setText ( ZSoftKey::RIGHT, tr("TXT_RID_SOFTKEY_CANCEL", "Cancel" ), ( ZSoftKey::TEXT_PRIORITY ) 0 );
	
	setSoftKey(softKey);
}

QString ZGui::getProgramDir()
{
	ProgDir = QString ( qApp->argv() [0] ) ;
	int i = ProgDir.findRev ( "/" );
	ProgDir.remove ( i+1, ProgDir.length() - i );
	return ProgDir;
}

void ZGui::readFile()
{
	if ( gainTable )
		free(gainTable);
		
	if ( !QFile::exists( GAIN_PATH ) )
		system(QString("cp %1 %2").arg(GAIN_PATH_ORG).arg(GAIN_PATH));
	
	QFile file ( GAIN_PATH );
	if (  file.open ( IO_ReadWrite ) )
	{
		tableLen = file.size();
		gainTable = (char*)malloc( tableLen );
		file.readBlock(gainTable, tableLen);
		qDebug("Readed byte %d", file.size() );
		file.close();
	} else
	{
		ZMessageDlg * dlg = new ZMessageDlg(QObject::tr("TXT_RID_STANDARD_ERROR","Error"), 
				QObject::tr("FMT_RID_INSTRUCTIONALTXT_1_WAS_NOT_FOUND","%1 not found.").arg(GAIN_PATH),
				ZMessageDlg::TypeOK, 0, this);
		dlg->exec();
		delete dlg;		
		qApp->quit();
	}
}

void ZGui::updateView()
{
	
	#ifdef VOLUME_TABLE
	ZOptionItem * item;
	
	int i,j;
	
	for ( j=0; j<GAIN_DEVICE_COUNT; j++ )
	{
		lbDevice[j]->clear();
		for ( i=0; i<GAIN_DEVICE_LEN; i++ )
		{
			if ( hideList[i] )
				continue;
			item = new ZOptionItem( lbDevice[j], ZOptionItem::EDIT_GAIN_VOLUME );
			item->setPointToVolumeData( gainTable, GAIN_DEVICES_START + GAIN_DEVICE_LEN*j + i*GAIN_DEVICE_ITEM_LEN + GAIN_DEVICE_ITEM_POS );
			qDebug("Set seek %d", GAIN_DEVICES_START + GAIN_DEVICE_LEN*j + i*GAIN_DEVICE_ITEM_LEN + GAIN_DEVICE_ITEM_POS );
			qDebug("Data %d", gainTable[GAIN_DEVICES_START + GAIN_DEVICE_LEN*j + i*GAIN_DEVICE_ITEM_LEN + GAIN_DEVICE_ITEM_POS] );
			//item->setTitle( paramList[i] );
			item->setTitle( QObject::tr(paramList[i][1], paramList[i][0])+QString(paramList[i][2])+QObject::tr(paramList[i][3], paramList[i][4])+QString(paramList[i][5]) ); 
			lbDevice[j]->insertItem( item );
		}
	}
	#endif

	cbEgHPlist->setCurrentItem(0);
	cbEgSPlist->setCurrentItem(0);
	
	slotChangeEqHP(0);
	slotChangeEqSP(0);
}

void ZGui::save()
{
	QFile file ( GAIN_PATH );
	if (  file.open ( IO_WriteOnly ) )
	{
		file.reset();
		file.writeBlock(gainTable, tableLen);
		file.close();
	}	
	
	qApp->quit();
}

void ZGui::slotChangeEqHP( int eq )
{
	ZOptionItem * item;
	
	lbEqHP->clear();
	
	fprintf(stderr, "HP %s:", eqList[eq][1]);;
	for ( int i=0; i<GAIN_EQUALASER_ITEM_COUNT; i++ )
	{
		fprintf(stderr, "%2x", gainTable[GAIN_EQUALASER_START_2 + eq*GAIN_EQUALASER_LEN + GAIN_EQUALASER_ITEM_LEN*i]);
		fprintf(stderr, "%2x ", gainTable[GAIN_EQUALASER_START_2 + eq*GAIN_EQUALASER_LEN + GAIN_EQUALASER_ITEM_LEN*i+1]);
		item = new ZOptionItem( lbEqHP, ZOptionItem::EDIT_GAIN_EQUALOSER );
		item->setPointToVolumeData( gainTable, GAIN_EQUALASER_START_2 + eq*GAIN_EQUALASER_LEN + GAIN_EQUALASER_ITEM_LEN*i );
		item->setTitle( eqHzList[i] );
		lbEqHP->insertItem( item );
	}
	fprintf(stderr, "\n");
}

void ZGui::slotChangeEqSP( int eq )
{
	ZOptionItem * item;
	
	lbEqSP->clear();
	
	fprintf(stderr, "SP %s:", eqList[eq][1]);
	for ( int i=0; i<GAIN_EQUALASER_ITEM_COUNT; i++ )
	{
		fprintf(stderr, "%2x", gainTable[GAIN_EQUALASER_START_1 + eq*GAIN_EQUALASER_LEN + GAIN_EQUALASER_ITEM_LEN*i]);
		fprintf(stderr, "%2x ", gainTable[GAIN_EQUALASER_START_1 + eq*GAIN_EQUALASER_LEN + GAIN_EQUALASER_ITEM_LEN*i+1]);
		item = new ZOptionItem( lbEqSP, ZOptionItem::EDIT_GAIN_EQUALOSER );
		item->setPointToVolumeData( gainTable, GAIN_EQUALASER_START_1 + eq*GAIN_EQUALASER_LEN + GAIN_EQUALASER_ITEM_LEN*i );
		item->setTitle( eqHzList[i] );
		lbEqSP->insertItem( item );
	}
	fprintf(stderr, "\n");
}

void ZGui::slotChangeMenu( int n )
{
	switch (n)
	{
		case 1:
			{
			QFile file ( GAIN_PATH );
			if (  file.open ( IO_WriteOnly ) )
			{
				file.reset();
				file.writeBlock(gainTable, tableLen);
				file.close();
			}
			ZMessageDlg * dlg = new ZMessageDlg("", 
			#ifndef EZX_Z6
					QObject::tr("TXT_RID_STANDARD_YOU_HAVE_SUCCESSFULLY_SAVED","Successfully saved:").replace(':',' '),
			#else
					QObject::tr("TXT_RID_STANDARD_YOU_HAVE_SUCCESSFULLY_SAVED","Successfully saved:").replace(QRegExp(":"),QString(" ")),
			#endif			
					ZMessageDlg::TypeOK, 0, this);
			dlg->exec();
			
			delete dlg;
			
			break;	
			}		
		case 2:
			{
			ZMessageDlg * dlg = new ZMessageDlg(" ", 
			#ifdef EZX_Z6
					QObject::tr("TXT_RID_CLI_HEADER_PLEASE_WAIT","Update..."),
			#else
					QObject::tr("TXT_RID_INSTRUCTIONALTXT_PLEASE_WAIT","Update..."),
			#endif			
					ZMessageDlg::TypeCustom, 0, this);
			#ifdef EZX_Z6		
			dlg->setTitleIcon( MSG_WAIT_ICON );
			#else
			dlg->setTitleIcon( "info_pop.g" );
			#endif
			dlg->show();
			qApp->processEvents();
			system(QString("busybox killall -9 soundmanager; sleep 2; busybox killall -9 am; busybox killall -9 messaging"));
			delete dlg;			
			break;	
			}
		case 3:
			{
			ZMessageDlg * dlg = new ZMessageDlg(QObject::tr("TXT_RID_HEADER_RESTORE_SOUND_SETTINGS","Restore"),
					QObject::tr("TXT_RID_INSTRUCTIONALTXT_ARE_YOU_SURE_YOU_WANT_TO_RESET_ALL_SOUND_SETTINGS_TO_DEFAULT_VALUES","Restore sound?"),
						ZMessageDlg::TypeChoose);

			if ( dlg->exec()==QDialog::Accepted )
			{
				system(QString("rm %1").arg(GAIN_PATH));
				readFile();
				updateView();
				ZMessageDlg * dlg2 = new ZMessageDlg(QObject::tr("TXT_RID_HEADER_RESTORE_SOUND_SETTINGS","Restore"), 
						QObject::tr("TXT_RID_INSTRUCTIONALTXT_YOU_HAVE_RESET_ALL_SOUND_SETTINGS_TO_DEFAULT_VALUES","Restored all sound settings to default."),
						ZMessageDlg::TypeOK, 0, this);
				dlg2->exec();
				delete dlg2;				
			}
			delete dlg;
			break;
			}		
		default:
			break;
	}
}
