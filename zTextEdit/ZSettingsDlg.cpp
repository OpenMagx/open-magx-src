//
// Project: zTextEdit
//
// Description: Text editor for MAGX
//
// Author: Ant-ON <prozanton@gmail.com>, (C) 2009-2010
//

#include "ZSettingsDlg.h"
#include <qpixmap.h>
#include <qlabel.h>
#include <ZApplication.h>
#include <ZSoftKey.h>
#include <ZNumPickerDlg.h>
#include <ZSingleSelectDlg.h>
#include <ZConfig.h>

#include "lng.h"
extern ZLng* lng;
#include "zgui.h"
extern ZGui* zgui;

ZSettingsDlg::ZSettingsDlg()
  :MyBaseDlg()
{
	setMainWidgetTitle(lng->getString("OPTION"));
	
	ZConfig cfg(lng->ProgDir+"/zTextEdit.cfg");
	cfg_fontSize = cfg.readNumEntry(QString("GUI"), QString("FontSize"), 10);
	cfg_underline = cfg.readBoolEntry(QString("GUI"), QString("Underline"), true);
	cfg_autoOpen = cfg.readBoolEntry(QString("GUI"), QString("AutoOpen"), false);
	cfg_menuCopy = cfg.readBoolEntry(QString("GUI"), QString("MenuCopyOnDial"), false);
	cfg_chineseCodeDetect = cfg.readBoolEntry(QString("Enginea"), QString("ChineseCodeDetect"), false);
	#ifdef SELECT_CUR_LINE
	cfg_selCurLine = cfg.readBoolEntry(QString("GUI"), QString("SelCurLine"), false);
	#endif
	/*
	#if !( defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W) )
	cfg_infoBar = cfg.readBoolEntry(QString("GUI"), QString("InfoBar"), false);
	#endif
	*/
	
	lbOptions = new ZListBox("%I%M", this);
 
	lbOptions->clear();
 
	ziFontSize=new ZSettingItem(lbOptions);
	ziFontSize->appendSubItem(1, lng->getString("FONTSIZE"));
	ziFontSize->appendSubItem(1, QString::number(cfg_fontSize));
	lbOptions->insertItem(ziFontSize);  
	
	ziUnderline=new ZSettingItem(lbOptions);
	ziUnderline->appendSubItem(1, lng->getString("UNDERLINE"));
	ziUnderline->appendSubItem(1, cfg_underline?lng->getString("ON"):lng->getString("OFF"));
	lbOptions->insertItem(ziUnderline);	
	
	ziAutoOpen=new ZSettingItem(lbOptions);
	ziAutoOpen->appendSubItem(1, lng->getString("AUTO_OPEN_FILE"), true);
	ziAutoOpen->appendSubItem(1, cfg_autoOpen?lng->getString("ON"):lng->getString("OFF"));
	lbOptions->insertItem(ziAutoOpen);
	
	ziMenuDial=new ZSettingItem(lbOptions);
	ziMenuDial->appendSubItem(1, lng->getString("COPY_MENU_ON_DIAL"), true);
	ziMenuDial->appendSubItem(1, cfg_menuCopy?lng->getString("ON"):lng->getString("OFF"));		
	lbOptions->insertItem(ziMenuDial);	
	
	ziChineseCodeDetect=new ZSettingItem(lbOptions);
	ziChineseCodeDetect->appendSubItem(1, lng->getString("CHINESE_CODE_DETECT"), true);
	ziChineseCodeDetect->appendSubItem(1, cfg_chineseCodeDetect?lng->getString("ON"):lng->getString("OFF"));		
	lbOptions->insertItem(ziChineseCodeDetect);		
	
	#ifdef SELECT_CUR_LINE
	ziSelCurLine=new ZSettingItem(lbOptions);
	ziSelCurLine->appendSubItem(1, lng->getString("SELECT_CUR_LINE"), true);
	ziSelCurLine->appendSubItem(1, cfg_selCurLine?lng->getString("ON"):lng->getString("OFF"));		
	lbOptions->insertItem(ziSelCurLine);		
	#endif
			
	/*
	#if !( defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W) )
	ziInfoBar=new ZSettingItem(lbOptions);
	ziInfoBar->appendSubItem(1, lng->getString("INFOBAR);
	ziInfoBar->appendSubItem(1, cfg_infoBar?lng->getString("ON:lng->getString("OFF);		
	lbOptions->insertItem(ziInfoBar);	
	#endif	
  	*/
  	
  	
	connect( lbOptions, SIGNAL(selected(int)), this, SLOT(slot_chengeOption(int)));
  
	setContentWidget ( lbOptions );
  
	ZSoftKey *softKey = new ZSoftKey ( NULL, this, this );
	softKey->setText ( ZSoftKey::LEFT, lng->getString("OK"), ( ZSoftKey::TEXT_PRIORITY ) 0 );
	softKey->setText ( ZSoftKey::RIGHT, lng->getString("CANCEL"), ( ZSoftKey::TEXT_PRIORITY ) 0 );
	softKey->setClickedSlot ( ZSoftKey::RIGHT, this, SLOT ( reject() ) );
	softKey->setClickedSlot ( ZSoftKey::LEFT, this, SLOT ( accept() ) );
	setSoftKey( softKey ); 
}

ZSettingsDlg::~ZSettingsDlg()
{

}

void ZSettingsDlg::slot_chengeOption(int sel)
{
	switch (sel)
	{
		case 0:
		{
			ZNumPickerDlg * dlg = new ZNumPickerDlg(2,this);
			ZNumModule* num = dlg->getNumModule();
			num->setMaxValue(30);
			num->setMinValue(6);
			num->setValue(cfg_fontSize);
			if ( dlg->exec() == QDialog::Accepted )
			{
				cfg_fontSize = num->getValue();
				ziFontSize->setSubItem(1, 1, QString::number(cfg_fontSize));	
			}
			delete num;
			delete dlg;	

			break;
		}
		case 1:
		{
			QStringList itemList;
			itemList.append(lng->getString("ON"));
			itemList.append(lng->getString("OFF"));
			ZSingleSelectDlg *dlg = new ZSingleSelectDlg(lng->getString("UNDERLINE"), "", this);
			dlg->addItemsList(itemList);
			dlg->getListBox()->checkItem(!cfg_underline, true);
			if ( dlg->exec() == QDialog::Accepted )
			{
				cfg_underline = !dlg->getCheckedItemIndex();
				ziUnderline->setSubItem(1, 1, cfg_underline?lng->getString("ON"):lng->getString("OFF"));
			}
			delete dlg;
			break;
		}	
		case 2:
		{
			QStringList itemList;
			itemList.append(lng->getString("ON"));
			itemList.append(lng->getString("OFF"));
			ZSingleSelectDlg *dlg = new ZSingleSelectDlg(lng->getString("AUTO_OPEN_FILE"), "", this);
			dlg->addItemsList(itemList);
			dlg->getListBox()->checkItem(!cfg_autoOpen, true);
			if ( dlg->exec() == QDialog::Accepted )
			{
				cfg_autoOpen = !dlg->getCheckedItemIndex();
				ziAutoOpen->setSubItem(1, 1, cfg_autoOpen?lng->getString("ON"):lng->getString("OFF"));
			}
			delete dlg;
			break;
		}
		case 3:
		{
			QStringList itemList;
			itemList.append(lng->getString("ON"));
			itemList.append(lng->getString("OFF"));
			ZSingleSelectDlg *dlg = new ZSingleSelectDlg(lng->getString("COPY_MENU_ON_DIAL"), "", this);
			dlg->addItemsList(itemList);
			dlg->getListBox()->checkItem(!cfg_menuCopy, true);
			if ( dlg->exec() == QDialog::Accepted )
			{
				cfg_menuCopy = !dlg->getCheckedItemIndex();
				ziMenuDial->setSubItem(1, 1, cfg_menuCopy?lng->getString("ON"):lng->getString("OFF"));
			}
			delete dlg;
			break;
		}			
		case 4:
		{
			QStringList itemList;
			itemList.append(lng->getString("ON"));
			itemList.append(lng->getString("OFF"));
			ZSingleSelectDlg *dlg = new ZSingleSelectDlg(lng->getString("CHINESE_CODE_DETECT"), "", this);
			dlg->addItemsList(itemList);
			dlg->getListBox()->checkItem(!cfg_chineseCodeDetect, true);
			if ( dlg->exec() == QDialog::Accepted )
			{
				cfg_chineseCodeDetect = !dlg->getCheckedItemIndex();
				ziChineseCodeDetect->setSubItem(1, 1, cfg_chineseCodeDetect?lng->getString("ON"):lng->getString("OFF"));	
			}
			delete dlg;
			break;
		}	
		#ifdef SELECT_CUR_LINE
		case 5:
		{
			QStringList itemList;
			itemList.append(lng->getString("ON"));
			itemList.append(lng->getString("OFF"));
			ZSingleSelectDlg *dlg = new ZSingleSelectDlg(lng->getString("SELECT_CUR_LINE"), "", this);
			dlg->addItemsList(itemList);
			dlg->getListBox()->checkItem(!cfg_selCurLine, true);
			if ( dlg->exec() == QDialog::Accepted )
			{
				cfg_selCurLine = !dlg->getCheckedItemIndex();
				ziSelCurLine->setSubItem(1, 1, cfg_selCurLine?lng->getString("ON"):lng->getString("OFF"));	
			}
			delete dlg;
			break;
		}	
		#endif			
		/*
		#if !( defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W) )			
		case 6:
		{
			QStringList itemList;
			itemList.append(lng->getString("ON"));
			itemList.append(lng->getString("OFF"));
			ZSingleSelectDlg *dlg = new ZSingleSelectDlg(lng->getString("INFOBAR"), "", this);
			dlg->addItemsList(itemList);
			dlg->getListBox()->checkItem(!cfg_infoBar, true);
			if ( dlg->exec() == QDialog::Accepted )
			{
				cfg_infoBar = !dlg->getCheckedItemIndex();
				ziInfoBar->setSubItem(1, 1, cfg_infoBar?lng->getString("ON"):lng->getString("OFF"));	
			}
			delete dlg;
			break;
		}
		#endif	
		*/
	}
}

void ZSettingsDlg::accept()
{
	ZConfig cfg(lng->ProgDir+"/zTextEdit.cfg");
	cfg.writeEntry(QString("GUI"), QString("FontSize"), cfg_fontSize);
	cfg.writeEntry(QString("GUI"), QString("Underline"), cfg_underline);
	cfg.writeEntry(QString("GUI"), QString("AutoOpen"), cfg_autoOpen);
	cfg.writeEntry(QString("GUI"), QString("MenuCopyOnDial"), cfg_menuCopy);
	cfg.writeEntry(QString("Enginea"), QString("ChineseCodeDetect"), cfg_chineseCodeDetect);
	#ifdef SELECT_CUR_LINE
	cfg.writeEntry(QString("GUI"), QString("SelCurLine"), cfg_selCurLine);	
	#endif
	/*
	#if !( defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W) )
	cfg.writeEntry(QString("GUI"), QString("InfoBar"), cfg_infoBar);
	#endif
	*/
	cfg.flush();
	MyBaseDlg::accept();
}
