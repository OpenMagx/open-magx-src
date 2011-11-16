//
// C++ Implementation: ZLng
//
// Description:
//
// Author: Ant-ON <prozanton@gmail.com>, (C) 2009-2011
//
//

#ifndef LNG_H
#define LNG_H

#include <qobject.h>
#include <unistd.h>
#include <stdlib.h>

#define LNG_PATH QString("/ezxlocal/download/mystuff/.system/lng/zSettings/")

#include <ZListBox.h>
#include <ZComboBox.h>

class ZLng
{
	public:
		ZLng();
		~ZLng();

		QString getString(QString str);
		
		QString ProgDir;

		void loadLngFile(QString fname );
		void getLngList(ZComboBox *list, QString cur);
		QString getLngFileName(QString lname);
		void autoLoadLng();
		void loadLngFullNameFile(QString fname);
		void setCurrentLng(QString lng);

		QString getCurrentLng();

	private:
		QString CurLng;
		ZConfig * cLng;
};

#endif
