//
// Project: zTextEdit
//
// Description: Text editor for MAGX
//
// Author: Ant-ON <prozanton@gmail.com>, (C) 2009-2010
//

#include "BaseDlg.h"
#include "ZAboutDlg.h"

#include <ZLabel.h>
#include <ZApplication.h>
#include <ZSoftKey.h>
#include <ZScrollPanel.h>
#include <ZImage.h>
#include <ZSeparator.h>

#include "zgui.h"
extern ZGui* zgui;

#include "lng.h"
extern ZLng* lng;

ZAboutDialog::ZAboutDialog()
    :MyBaseDlg()
{
	setMainWidgetTitle("zTextEdit");
	
	ZScrollPanel * sv = new ZScrollPanel(this);
	this->setContentWidget ( sv );  
	
	ZImage *img = new ZImage( this );
	img->setPixmap ( QPixmap ( zgui->getProgramDir() + "/zTextEdit_usr.png" ) );
	sv->addChild(img, 10,10);

	QFont font ( qApp->font() ); 
	font.setBold(true);
	ZLabel * a = new ZLabel("zTextEdit",this);
	a->setFont( font );
	a->setFixedWidth( SCREEN_WIDTH-70 );
	a->setAlignment( ZLabel::AlignHCenter );
	#if defined(EZX_E8) || defined(EZX_EM30)
	sv->addChild(a, 70,5);	
	#else
	sv->addChild(a, 70,10);
	#endif
	
	a = new ZLabel(QString("ver: ")+APP_VER,this);
	a->setFixedWidth( SCREEN_WIDTH-70 );
	a->setAlignment( ZLabel::AlignHCenter );	
	#if defined(EZX_E8) || defined(EZX_EM30)  
	sv->addChild(a, 70,28);	
	#else
	sv->addChild(a, 70,35);
	#endif		

	#ifdef EZX_E2	
	a = new ZLabel(QString("Platform: EZX-E2"),this);
	#else
	#ifdef EZX_V8	
	a = new ZLabel(QString("Platform: EZX-V8"),this);
	#else
	#ifdef EZX_Z6	
	a = new ZLabel(QString("Platform: EZX-Z6"),this);
	#else
	#ifdef EZX_Z6W	
	a = new ZLabel(QString("Platform: EZX-Z6w"),this);
	#else	
	#ifdef EZX_ZN5	
	a = new ZLabel(QString("Platform: EZX-ZN5"),this);
	#else
	#ifdef EZX_U9	
	a = new ZLabel(QString("Platform: EZX-U9"),this);
	#else
	#ifdef EZX_EM30	
	a = new ZLabel(QString("Platform: EZX-EM30"),this);
	#else
	#ifdef EZX_EM35	
	a = new ZLabel(QString("Platform: EZX-EM35"),this);
	#else
	#ifdef EZX_VE66	
	a = new ZLabel(QString("Platform: EZX-VE66"),this);
	#else	
	#ifdef EZX_E8	
	a = new ZLabel(QString("Platform: EZX-E8"),this);
	#endif		
	#endif
	#endif
	#endif
	#endif
	#endif
	#endif	
	#endif
	#endif
	#endif		
		
	a->setFixedWidth( SCREEN_WIDTH-70 );
	a->setAlignment( ZLabel::AlignHCenter );	
	#if defined(EZX_E8) || defined(EZX_EM30) 
	sv->addChild(a, 70,52);	
	#else
	sv->addChild(a, 70,60);
	#endif	
	
	ZSeparator * sep = new ZSeparator();
	sep->setLength(SCREEN_WIDTH-20);
	#if defined(EZX_E8) || defined(EZX_EM30)  
	sv->addChild(sep, 10,80);	
	#else
	sv->addChild(sep, 10,100);
	#endif	
	
	a = new ZLabel("Copyrigth ©: Ant-ON, 2010",this);
	a->setAutoResize(true);
	a->setPreferredWidth(SCREEN_WIDTH-5);
	#if defined(EZX_E8) || defined(EZX_EM30) 
	sv->addChild(a, 10,85);
	#else
	sv->addChild(a, 10,110);
	#endif		
	
	a = new ZLabel("e-mail: prozanton@gmail.com",this);
	a->setAutoResize(true);
	a->setPreferredWidth(SCREEN_WIDTH-5);
	#if defined(EZX_E8) || defined(EZX_EM30) 
	sv->addChild(a, 10,107);
	#else
	sv->addChild(a, 10,140);
	#endif	
	
	a = new ZLabel("Thanks BeZ from zTextView",this);
	a->setAutoResize(true);
	a->setPreferredWidth(SCREEN_WIDTH-5);
	#if defined(EZX_E8) || defined(EZX_EM30) 
	sv->addChild(a, 10,129);
	#else
	sv->addChild(a, 10,170);
	#endif	
	
	a = new ZLabel("Based on zSimpleGUI",this);
	a->setAutoResize(true);
	a->setPreferredWidth(SCREEN_WIDTH-5);
	#if defined(EZX_E8) || defined(EZX_EM30) 
	sv->addChild(a, 10,150);
	#else
	sv->addChild(a, 10,200);
	#endif
	
	sep = new ZSeparator();
	sep->setLength(SCREEN_WIDTH-20);
	#if defined(EZX_E8) || defined(EZX_EM30) 
	sv->addChild(sep, 10,173);	
	#else
	sv->addChild(sep, 10,230);
	#endif

	ZSoftKey *softKey = new ZSoftKey ( NULL, this, this );
	softKey->setText ( ZSoftKey::LEFT, lng->getString("OK"), ( ZSoftKey::TEXT_PRIORITY ) 0 );
	softKey->setClickedSlot ( ZSoftKey::LEFT, this, SLOT ( accept() ) );
	setSoftKey( softKey );
}

ZAboutDialog::~ZAboutDialog()
{

}
