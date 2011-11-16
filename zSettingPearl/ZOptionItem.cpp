//
// Project: zSetting
//
// Version: 0.3
//
// Author: Ant-ON <prozanton@gmail.com>, (C) 2010-2010
//


#include "ZOptionItem.h"

#include "ZListBox.h"

#include <ZNumPickerDlg.h>
#include <ZSingleSelectDlg.h>
#include <ZSingleCaptureDlg.h>

#ifndef WITHOUT_EDIT_TEXT_NUM
#include <ZApplication.h>
#include <ZIMethod.h>
#endif

#ifndef WITHOUT_EDIT_INTERNET_PROFILE
#include <napi.h>
#endif

#include <AM_AppObject.h>
#include <ZPopup.h>
#include <RES_ICON_Reader.h>
typedef QValueList<const AM_AppObject *> ZAppList;

#include "lng.h"
extern ZLng* lng;

#include <iostream>
using namespace std;

static AM_AppRegistry * amRegistry = NULL;

ZOptionItem::ZOptionItem( ZListBox* _container, EDIT_TYPE _type, int id ):
	ZSettingItem( _container, "%M" )
{
	this->id = id;
	type=_type;
	if ( type != EDIT_INTERNET_PROFILE )
		n=0;
	else
		n=1;
	if ( type == EDIT_APP_SELECT && !amRegistry )
	{
		amRegistry = new AM_AppRegistry();
		amRegistry->init();
	}
	
	min=0;
	max=0;
	title="";
	text="";
	list=NULL;
	changed=false;
	iFlexNum=0;
	
	appendSubItem(0, " ", true);
	appendSubItem(0, " ");
	
	connect( _container, SIGNAL(selected(ZSettingItem*)), this, SLOT(selected(ZSettingItem*)));
}

ZOptionItem::~ZOptionItem()
{
	disconnect( listBox(), SIGNAL(selected(ZSettingItem*)), this, SLOT(selected(ZSettingItem*)));
	if ( list != NULL )
		delete list;
}

void ZOptionItem::selected(ZSettingItem* item)
{
	if ( (ZOptionItem*)item != this )
		return;
	
	switch ( type )
	{
		case EDIT_TEXT:
		case EDIT_TEXT_NUM:
		case EDIT_FILE:
			{
			ZSingleCaptureDlg* zscd = new ZSingleCaptureDlg(title, "", ZSingleCaptureDlg::TypeLineEdit, this, "", true, 0, 0);
			ZLineEdit* zle = (ZLineEdit*)zscd->getLineEdit();
			#ifndef WITHOUT_EDIT_TEXT_NUM
			if ( type==EDIT_TEXT_NUM )
				((ZApplication*)qApp)->setInputMethod(zle, ZKB_INPUT_NUMERIC, ZKbInputField::FIELD_TYPE_NUMERIC, ""); 
			#endif
			zle->setText(text);
			if ( zscd->exec() == QDialog::Accepted )
			{
				setText(zle->text());
				changed=true;
			}
			delete zle;
			delete zscd;
			}
			break;
		case EDIT_FLEXBIT:
		case EDIT_BOOL_YESNO:
		case EDIT_BOOL_ONOFF:
			{
			QStringList itemList;
			if ( type==EDIT_BOOL_ONOFF || type==EDIT_FLEXBIT )
			{
				itemList.append(lng->getString("ON"));
				itemList.append(lng->getString("OFF"));
			} else
			{
				itemList.append(lng->getString("YES"));
				itemList.append(lng->getString("NO"));				
			}
			ZSingleSelectDlg *dlg = new ZSingleSelectDlg(title, "", this);
			dlg->addItemsList(itemList);
			dlg->getListBox()->checkItem(!n, true);
			if ( dlg->exec() == QDialog::Accepted )
			{
				setNum(!dlg->getCheckedItemIndex());
				changed=true;
			}
			delete dlg;
			}
			break;
		case EDIT_NUM:
			{
			ZNumPickerDlg * dlg = new ZNumPickerDlg(2, this);
			ZNumModule* num = dlg->getNumModule();
			num->setMaxValue(max);
			num->setMinValue(min);
			num->setValue(n);
			if ( dlg->exec() == QDialog::Accepted )
			{
				setNum( num->getValue() );
				changed=true;
			}
			delete num;
			delete dlg;
			}
			break;
		case EDIT_ONE_OF_LIST:
			{
			if ( list == NULL )
				return;
			ZSingleSelectDlg *dlg = new ZSingleSelectDlg(title, "", this);
			dlg->addItemsList(*list);
			dlg->getListBox()->checkItem(n, true);
			if ( dlg->exec() == QDialog::Accepted )
			{
				setNum(dlg->getCheckedItemIndex());
				changed=true;
			}
			delete dlg;	
			}	
			break;
		case EDIT_INTERNET_PROFILE:
			#ifndef WITHOUT_EDIT_INTERNET_PROFILE
			{
			UINT32 profiles = NAPI_GetMaxProfiles();
			QStringList list;
			list.append(lng->getString("ASK"));
			if(profiles != -1) 
			{
				char *buf = new char[NAPI_MAX_PROFILE_NAME_LENGTH * profiles];
				if(NAPI_ListAllProfile((INT8*)buf, &profiles) != -1) 
				{
					char *prof_ptr = buf;
					for(uint i = 0; i < profiles; i++, prof_ptr = buf + i * NAPI_MAX_PROFILE_NAME_LENGTH)
						list.append(QString::fromUtf8(prof_ptr));
				}
				delete buf;	
			}
			ZSingleSelectDlg *dlg = new ZSingleSelectDlg(title, "", this);
			dlg->addItemsList(list);
			
			int sel=0, i=0;
			for ( QStringList::Iterator it = list.begin(); it != list.end(); ++it )
				if ( *it == text )
				{
					sel=i;
					break;
				} else
					i++;
			if ( sel >= 0 )
				dlg->getListBox()->checkItem(sel, true);
			if ( dlg->exec() == QDialog::Accepted )
			{
				n=dlg->getCheckedItemIndex();
				setText( (n>0)?(*(list.at(n))):"" );
				changed=true;
			}
			delete dlg;
			}
			#endif
			break;
		case EDIT_APP_SELECT:
			{
			ZPopup * dlg = new ZPopup(ZPopup::DIALOG, this);
			dlg->setTitleIcon("action_required_pop.gif");
			dlg->setSoftkeyText( tr("TXT_RID_SOFTKEY_SELECT", "Select"), tr("TXT_RID_SOFTKEY_CANCEL", "Cancel") );
			ZAppList lAppList;
			amRegistry->getAllAppObjects( lAppList );
			
			QFont font ( qApp->font() );
			font.setPointSize ( 16 );
			ZListBox * lbAppList = new ZListBox("%r%I16%M", dlg);
			lbAppList->setItemFont( ZListBox::LISTITEM_REGION_A, ZListBox::StStandard, font );	
			lbAppList->setItemFont( ZListBox::LISTITEM_REGION_A, ZListBox::StHighlighted, font );	
			lbAppList->setItemFont( ZListBox::LISTITEM_REGION_A, ZListBox::StSelected, font );	
			lbAppList->setItemFont( ZListBox::LISTITEM_REGION_A, ZListBox::StHighlightSelected, font );	
		
			ZSettingItem* listitem = new ZSettingItem( lbAppList, "%r%I16%M" );
			listitem->appendSubItem ( 2, lng->getString("NO"), true );
			if ( "" == text )
				lbAppList->checkItem( 0, true );	
			lbAppList->insertItem ( listitem,-1,true );
			
			for ( int i=0; i<lAppList.count(); i++ ) 
			{
				listitem = new ZSettingItem( lbAppList, "%r%I16%M" );	

				listitem->appendSubItem ( 2, (*(lAppList.at( i )))->getName(), true );
				QPixmap pm;
				
				QString icon = (*(lAppList.at( i )))->getBigIcon();
				
				if ( (icon.right(2)==".g") || (icon.right(2)==".k") )
				{
					RES_ICON_Reader res;
					pm = res.getIcon(icon);
				} else if ( QFile::exists(icon) )
						pm.load( icon );
				else
				{
					icon = (*(lAppList.at( i )))->getSmallIcon();
					if ( (icon.right(2)==".g") || (icon.right(2)==".k") )
					{
						RES_ICON_Reader res;
						pm = res.getIcon(icon);
					} else if ( QFile::exists(icon) )
							pm.load( icon );					
				}
				
				if ( pm.height() > 16 || pm.width() > 16 )
				{
					QImage image;
					image = pm.convertToImage();
					image = image.smoothScale(16, 16);
					pm.convertFromImage(image);	
				}
				
				listitem->setPixmap ( 1, pm );
				listitem->setReservedData ( i );
				lbAppList->insertItem ( listitem,-1,true );
				
				if ( QString( (*(lAppList.at( i )))->getUid() ) == text )
					lbAppList->checkItem( i+1, true );
			}					
			
			dlg->insertChild( lbAppList );
			connect( lbAppList, SIGNAL( clicked(ZListItem*) ), dlg, SLOT( done(int) ) );
			
			
			if ( dlg->exec() == QDialog::Accepted )
			{
				if ( lbAppList->radioItemChecked()>0 )
				{
					setText( (*(lAppList.at( lbAppList->radioItemChecked()-1 )))->getUid() );
					changed=true;						
				} else
				{
					setText( "" );
					changed=true;							
				}
			}
			delete dlg;
						
			}
			break;
	}
}

void ZOptionItem::setNum(int _n)
{
	n=_n;
	switch ( type )
	{
		case EDIT_BOOL_YESNO:
			setSubItem(0, 1, n?lng->getString("YES"):lng->getString("NO"));
			break;
		case EDIT_BOOL_ONOFF:
		case EDIT_FLEXBIT:
			setSubItem(0, 1, n?lng->getString("ON"):lng->getString("OFF"));
			break;
		case EDIT_NUM:
			setSubItem(0, 1, QString::number(n));
			break;
		case EDIT_ONE_OF_LIST:
			if ( list != NULL )
				setSubItem(0, 1, *(list->at(n)));
			break;		
	}
}

void ZOptionItem::setMaxMin(int _max, int _min)
{
	max=_max;
	min=_min;
}

int ZOptionItem::getNum()
{
	return n;
}

void ZOptionItem::setTitle(QString _title)
{
	title=_title;
	setSubItem(0, 0, title, true);	
}
	
void ZOptionItem::setText(QString _text)
{
	text=_text;
	#ifndef WITHOUT_EDIT_INTERNET_PROFILE
	if ( type == EDIT_INTERNET_PROFILE && text=="")
		setSubItem(0, 1, lng->getString("ASK"));		
	else
	#endif
	if ( type == EDIT_APP_SELECT && amRegistry )
	{
		const AM_RegistryObject * app = amRegistry->getRegistryObject( text );
		if ( app )
			setSubItem(0, 1, app->getName() );	
		else
			setSubItem(0, 1, text);
	} else
		setSubItem(0, 1, text);
}

QString ZOptionItem::getText()
{
	return text;
}

void ZOptionItem::setList( QStringList * _list )
{
	list = _list;
}

void ZOptionItem::read(QString name, QString section, QString param, QString def)
{
	cfgName = name;
	cfgSection = section;
	cfgParam = param;
	
	ZConfig cfg(cfgName);
	
	switch ( type )
	{
		case EDIT_TEXT_NUM:
		case EDIT_INTERNET_PROFILE:
		case EDIT_TEXT:
		case EDIT_FILE:
		case EDIT_APP_SELECT:
			setText( cfg.readEntry(cfgSection, cfgParam, def) );
			break;
		default:
			break;
	}
}

void ZOptionItem::read(QString name, QString section, QString param, int def)
{
	cfgName = name;
	cfgSection = section;
	cfgParam = param;
	
	ZConfig cfg(cfgName);
	switch ( type )
	{
		case EDIT_BOOL_YESNO:
		case EDIT_BOOL_ONOFF:		
			setNum( cfg.readBoolEntry(cfgSection, cfgParam, def) );
			break;			
		case EDIT_NUM:			
		case EDIT_ONE_OF_LIST:
			setNum( cfg.readNumEntry(cfgSection, cfgParam, def) );
			break;	
		default:
			break;
	}
}

void ZOptionItem::readFlex(int iNum)
{
	iFlexNum = iNum;
	
    unsigned long int index = iFlexNum/32;
    unsigned long int mask = 1 << (31-iFlexNum%32);

	char bufFile[30][20];
	int i=0;
	for ( i=0;i<30;i++ ) bufFile[i][0]=0;
	i=0;
	
	//Read full file
	FILE* pFile = fopen("/ezxlocal/download/appwrite/setup/ezx_flexbit_rw.cfg", "r");
	if ( pFile )
	{
		while(i<30)
			if ( fgets(bufFile[i++], 20, pFile) <= 0 )
				break;
		fclose(pFile);
	}
	
	int k=i;
	int iFlexNum;
	unsigned long int iFlex;    
	for (i=0;i<k;i++)
	{
		if ( (sscanf(bufFile[i], "%d = %ld\n", &iFlexNum, &iFlex) > 1) && (iFlexNum==index) )
		{
			setNum( iFlex&mask );
			return;
		}
	}
	
	setNum( 0 );	
}

void ZOptionItem::writeFlex()
{
    unsigned long int index = iFlexNum/32;
    unsigned long int mask = 1 << (31-iFlexNum%32);

	char bufFile[30][30];
	int i=0;
	for ( i=0;i<30;i++ ) bufFile[i][0]=0;
	i=0;
	
	//Read full file
	FILE* pFile = fopen("/ezxlocal/download/appwrite/setup/ezx_flexbit_rw.cfg", "rb+");
	if ( pFile )
	{
		while(i<30)
			if ( fgets(bufFile[i++], 30, pFile) <= 0 )
				break;
		int k=i;

		int iFlexNum;
		unsigned long int iFlex;    
		for (i=0;i<k;i++)
		{
			if ( (sscanf(bufFile[i], "%d = %ld\n", &iFlexNum, &iFlex) > 1) && (iFlexNum==index) )
			{
				if ( n )
					iFlex = iFlex | mask;
				else
					iFlex = iFlex & (~mask);
				sprintf(bufFile[i], "%d = %ld\n", iFlexNum, iFlex );
				break;
			}
		}
		
		//Write full file
		rewind(pFile);

		for (i=0;i<k;i++)
			fputs(bufFile[i], pFile);
		fflush(pFile);
		fclose(pFile);
	}
}

void ZOptionItem::write()
{
	if (!changed)
		return;
	
	ZConfig cfg(cfgName);
	switch ( type )
	{
		case EDIT_TEXT_NUM:
		case EDIT_INTERNET_PROFILE:
		case EDIT_TEXT:
		case EDIT_FILE:
		case EDIT_APP_SELECT:
			cfg.writeEntry(cfgSection, cfgParam, getText());
			break;
		case EDIT_BOOL_YESNO:
		case EDIT_BOOL_ONOFF:		
			cfg.writeEntry(cfgSection, cfgParam, (bool)getNum());
			break;			
		case EDIT_NUM:			
		case EDIT_ONE_OF_LIST:
			cfg.writeEntry(cfgSection, cfgParam, getNum());
			break;
		case EDIT_FLEXBIT:
			writeFlex();
			break;
		default:
			break;
	}	
	
	cfg.flush();
	
	emit aplly(id);
}
