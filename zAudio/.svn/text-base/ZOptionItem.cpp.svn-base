//
// Poject name: zAudio
//
// Version: 0.1
//
// Description: Programm for change audio settings
//
// Author: Ant-ON <prozanton@gmail.com>, (C) 2010
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

#ifndef WITHOUT_LANG_FILE
#include "lng.h"
#else
#define LNG_ON "On"
#define LNG_OFF "Off"
#define LNG_YES "Yes"
#define LNG_NO "No"
#endif

#ifndef WITHOUT_GAIN_VOL
#include "gainDef.h"
#endif

ZOptionItem::ZOptionItem( ZListBox* _container, EDIT_TYPE _type ):
	ZSettingItem( _container, "%M" )
{
	type=_type;
	if ( type != EDIT_INTERNET_PROFILE )
		n=0;
	else
		n=1;
	min=0;
	max=0;
	title="";
	text="";
	list=NULL;
	
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
				setText(zle->text());
			delete zle;
			delete zscd;
			}
			break;
		case EDIT_BOOL_YESNO:
		case EDIT_BOOL_ONOFF:
			{
			QStringList itemList;
			if ( type==EDIT_BOOL_ONOFF )
			{
				itemList.append(LNG_ON);
				itemList.append(LNG_OFF);
			} else
			{
				itemList.append(LNG_YES);
				itemList.append(LNG_NO);				
			}
			ZSingleSelectDlg *dlg = new ZSingleSelectDlg(title, "", this);
			dlg->addItemsList(itemList);
			dlg->getListBox()->checkItem(!n, true);
			if ( dlg->exec() == QDialog::Accepted )
				setNum(!dlg->getCheckedItemIndex());
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
				setNum( num->getValue() );
			delete num;
			delete dlg;
			}
			break;
		#ifndef WITHOUT_GAIN_VOL
		case EDIT_GAIN_VOLUME:
			{
			ZNumPickerDlg * dlg = new ZNumPickerDlg(2, this);
			ZNumModule* num = dlg->getNumModule();
			num->setMaxValue( GAIN_DEVICE_VOL_MAX );
			num->setMinValue( GAIN_DEVICE_VOL_MIN);
			num->setValue( gainTable[n] );			
			if ( dlg->exec() == QDialog::Accepted )
			{
				gainTable[n] = num->getValue();
				setSubItem(0, 1, QString::number( gainTable[n] ) );				
			}
			delete num;
			delete dlg;
			}
			break;	
		case EDIT_GAIN_EQUALOSER:
			{

			ZSingleCaptureDlg* zscd = new ZSingleCaptureDlg(title, "", ZSingleCaptureDlg::TypeLineEdit, this, "", true, 0, 0);
			ZLineEdit* zle = (ZLineEdit*)zscd->getLineEdit();
			((ZApplication*)qApp)->setInputMethod(zle, ZKB_INPUT_NUMERIC, ZKbInputField::FIELD_TYPE_NUMERIC, ""); 
			zle->setText(QString::number(u2n.num-GAIN_EQUALASER_MIN));		
			if ( zscd->exec() == QDialog::Accepted )
			{
				int num = zle->text().toInt();
				if ( num<0 )
					num=0;
				if ( num>GAIN_EQUALASER_MAX-GAIN_EQUALASER_MIN )
					num=GAIN_EQUALASER_MAX-GAIN_EQUALASER_MIN;
				
				u2n.num = num+GAIN_EQUALASER_MIN;
				memcpy(&gainTable[n], u2n.data, 2);
				setSubItem(0, 1, QString::number( u2n.num-GAIN_EQUALASER_MIN ) );				
			}
			delete zle;
			delete zscd;
			}
			break;		
		#endif	
		case EDIT_ONE_OF_LIST:
			{
			if ( list == NULL )
				return;
			ZSingleSelectDlg *dlg = new ZSingleSelectDlg(title, "", this);
			dlg->addItemsList(*list);
			dlg->getListBox()->checkItem(n, true);
			if ( dlg->exec() == QDialog::Accepted )
				setNum(dlg->getCheckedItemIndex());
			delete dlg;	
			}	
			break;
		case EDIT_INTERNET_PROFILE:
			#ifndef WITHOUT_EDIT_INTERNET_PROFILE
			{
			UINT32 profiles = NAPI_GetMaxProfiles();
			QStringList list;
			list.append(LNG_ASK);
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
			}
			delete dlg;
			}
			#endif
			break;
	}
}

void ZOptionItem::setNum(int _n)
{
	n=_n;
	switch ( type )
	{
		case EDIT_BOOL_YESNO:
			setSubItem(0, 1, n?LNG_YES:LNG_NO);
			break;
		case EDIT_BOOL_ONOFF:
			setSubItem(0, 1, n?LNG_ON:LNG_OFF);
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
		setSubItem(0, 1, LNG_ASK);		
	else
	#endif
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

#ifndef WITHOUT_GAIN_VOL
void ZOptionItem::setPointToVolumeData( char * table, int dataIndex )
{
	gainTable = table;
	n = dataIndex;
	if ( type == EDIT_GAIN_EQUALOSER )
	{
		memcpy(u2n.data, &gainTable[n], 2);
		setSubItem(0, 1, QString::number( u2n.num-GAIN_EQUALASER_MIN ) );	
	} else
		setSubItem(0, 1, QString::number( gainTable[n] ) );
}
#endif
