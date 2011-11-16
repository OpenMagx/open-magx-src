//
// Project: zTextEdit
//
// Description: Text editor for MAGX
//
// Author: Ant-ON <prozanton@gmail.com>, (C) 2009-2010
//

#ifndef ZFINDDLG_H
#define ZFINDDLG_H

//My
#include "GUI_Define.h"

//EZX
#include <ZPopup.h>
#include <ZMultiLineEdit.h>
#include <ZLineEdit.h>
#include <ZSoftKey.h>
#include <ZWidget.h>

class ZFindDlg: public QDialog
{
	Q_OBJECT
	public:
		ZFindDlg(ZMultiLineEdit * edit_p, QWidget *parent = 0, const char *name = 0);
		~ZFindDlg();
		
		void selectText(int p);
	
	private slots:
		void newFind(const QString &);
		void nextFind();
		void lastFind();

	protected:
    	virtual bool eventFilter( QObject *target, QEvent *e );
	
	private:
		ZMultiLineEdit * edit_p;
		ZLineEdit * lineEdit;
		ZSoftKey * softKey;
		
		int oldP;
		QString oldText;
};

#endif
