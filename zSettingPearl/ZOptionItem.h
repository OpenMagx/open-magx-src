//
// Project: zSetting
//
// Version: 0.3
//
// Author: Ant-ON <prozanton@gmail.com>, (C) 2010-2010
//

#ifndef ZOPTIONITEM_H
#define ZOPTIONITEM_H

#ifdef OLD_SDK
#include <ZListBox.h>
#else
#include <ZSettingItem.h>
#endif

#include <qstringlist.h>

#include "AM_AppRegistry.h"

class Q_EXPORT ZOptionItem: public QWidget, public ZSettingItem
{
	Q_OBJECT
public: 
	enum EDIT_TYPE
	{
		EDIT_TEXT,
		EDIT_TEXT_NUM,		
		EDIT_BOOL_YESNO,
		EDIT_BOOL_ONOFF,		
		EDIT_NUM,
		EDIT_ONE_OF_LIST,
		EDIT_INTERNET_PROFILE,
		EDIT_FILE,
		EDIT_APP_SELECT,
		EDIT_FLEXBIT,				
	};

	ZOptionItem( ZListBox* _container, EDIT_TYPE _type, int id );
	~ZOptionItem();
	
	void setTitle(QString _title);
	
	void setText(QString _text);
	QString getText();
	
	void setNum(int _n);
	void setMaxMin(int _max, int _min=0);
	int  getNum();
	
	void setList( QStringList * _list );

	void read(QString name, QString section, QString param, QString def);
	void read(QString name, QString section, QString param, int def);
	void write();
	
	void readFlex(int);
	void writeFlex();
	
protected slots:
	void selected(ZSettingItem*);

signals:
	void aplly( int );

private:
	EDIT_TYPE type;
	int n, min, max;
	QString title, text;
	QStringList * list;
	bool changed;
	int id;
	
	QString cfgName, cfgSection, cfgParam;
	int iFlexNum;
};

#endif
