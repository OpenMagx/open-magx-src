//
// Poject name: zAudio
//
// Version: 0.1
//
// Description: Programm for change audio settings
//
// Author: Ant-ON <prozanton@gmail.com>, (C) 2010
//

#ifndef ZOPTIONITEM_H
#define ZOPTIONITEM_H

#ifdef OLD_SDK
#include <ZListBox.h>
#else
#include <ZSettingItem.h>
#endif

#include <qstringlist.h>

#ifndef WITHOUT_GAIN_VOL
typedef union U2
{
	unsigned short int num;
	char data[2];
} U2;
#endif

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
		EDIT_GAIN_VOLUME,
		EDIT_GAIN_EQUALOSER,
	};

	ZOptionItem( ZListBox* _container, EDIT_TYPE _type );
	~ZOptionItem();
	
	void setTitle(QString _title);
	
	void setText(QString _text);
	QString getText();
	
	void setNum(int _n);
	void setMaxMin(int _max, int _min=0);
	int  getNum();
	
	void setList( QStringList * _list );
	
	#ifndef WITHOUT_GAIN_VOL
	void setPointToVolumeData( char * table, int dataIndex );
	#endif

protected slots:
	void selected(ZSettingItem*);

private:
	EDIT_TYPE type;
	int n, min, max;
	QString title, text;
	QStringList * list;
	
	#ifndef WITHOUT_GAIN_VOL
	char * gainTable;
	
	U2 u2n;
	#endif
};

#endif
