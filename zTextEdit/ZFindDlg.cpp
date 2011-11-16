//
// Project: zTextEdit
//
// Description: Text editor for MAGX
//
// Author: Ant-ON <prozanton@gmail.com>, (C) 2009-2010
//

#include "ZFindDlg.h"

#include "lng.h"
extern ZLng* lng;

ZFindDlg::ZFindDlg(ZMultiLineEdit * e, QWidget *parent, const char *name)
	:QDialog(parent, name, true, 0)
{
	edit_p = e;

	lineEdit = new ZLineEdit(this);
	lineEdit->setFixedWidth(SCREEN_WIDTH);
	insertChild(lineEdit);
	
	softKey = new ZSoftKey(NULL, this, this);
	
	softKey->setGeometry( ZGlobal::getCstR() );
	
	softKey->setGeometry( 0, lineEdit->height(), SCREEN_WIDTH, softKey->height());
	setGeometry(0,SCREEN_HEIGHT-(lineEdit->height()+softKey->height()), SCREEN_WIDTH, (lineEdit->height()+softKey->height())); 

	softKey->setText ( ZSoftKey::LEFT, lng->getString("FIND"), ( ZSoftKey::TEXT_PRIORITY ) 0 );
	softKey->setText ( ZSoftKey::RIGHT, lng->getString("CANCEL"), ( ZSoftKey::TEXT_PRIORITY ) 0 );
	softKey->setClickedSlot ( ZSoftKey::LEFT, this, SLOT ( nextFind() ) );
	softKey->setClickedSlot ( ZSoftKey::RIGHT, this, SLOT ( accept() ) );
	
	connect(lineEdit, SIGNAL( textChanged( const QString & ) ), this, SLOT( newFind( const QString & ) ) );
	
	//
	oldText = "";
	oldP = 0;
}

ZFindDlg::~ZFindDlg()
{
	delete softKey;
	delete lineEdit;
}

void ZFindDlg::selectText(int p)
{
	int iSelX = 0;
	int iSelY = 0;	
	
	if (p<0) 
	{
		//Clear select if not exist
		edit_p->getCursorPosition( &iSelX, &iSelY );
		edit_p->setSelection(0,0,0,0);
		edit_p->setCursorPosition( iSelX, iSelY, false );			
	} else
	{
		edit_p->getCorsorPosition( iSelX, iSelY, p );
		edit_p->setCursorPosition( iSelX+7, iSelY, false );//For visible result
		edit_p->setCursorPosition( iSelX, iSelY, false );
		edit_p->getCorsorPosition( iSelX, iSelY, p + lineEdit->text().length() - 1 );
		edit_p->setCursorPosition( iSelX, iSelY, true );
	}
}

void ZFindDlg::newFind(const QString &text)
{
	oldText = text;
	oldP = edit_p->text().find(oldText, 0, false);
	selectText(oldP);
}

void ZFindDlg::nextFind()
{
	if (oldP<0)
		return;
	
	int p = edit_p->text().find(oldText, oldP+1, false);
	
	if (p>=0)
	{
		oldP = p;
		selectText(oldP);	
	}
}

void ZFindDlg::lastFind()
{
	if (oldP<0)
		return;	
		
	int p = edit_p->text().findRev(oldText, oldP-1, false);
	
	if (p>=0)
	{
		oldP = p;
		selectText(oldP);	
	}
}

bool ZFindDlg::eventFilter( QObject *target, QEvent *e )
{
	if (target == lineEdit)
	{
		if (QEvent::KeyPress == e->type())
			switch ( ((QKeyEvent*)e)->key() )
			{		
				case KEY_SIDE_UP:       nextFind();	return true; break;
				case KEY_SIDE_DOWN:     lastFind();	return true; break;
			}

		return false;
    } else
    	return false;
}	
