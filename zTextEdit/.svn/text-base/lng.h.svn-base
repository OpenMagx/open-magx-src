//
// Project: zTextEdit
//
// Description: Text editor for MAGX
//
// Author: Ant-ON <prozanton@gmail.com>, (C) 2009-2010
//

#ifndef LNG_H
#define LNG_H

#include <ZListBox.h>
#include <ZComboBox.h>

#include <qobject.h>
#include <unistd.h>
#include <stdlib.h>

#include <ZComboBox.h>
#include <ZConfig.h>

#define LNG_PATH ProgDir+"/lng/"

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
