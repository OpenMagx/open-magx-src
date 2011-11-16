//
// C++ Implementation: BaseDlg
//
// Description: 
//
//
// Author: root <root@andLinux>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "BaseDlg.h"
#include <ZApplication.h>
#include <ZSoftKey.h>

MyBaseDlg::MyBaseDlg()
  :_ZKbMainWidget( ZHeader::MAINDISPLAY_HEADER, NULL, "ZMainWidget", WType_Modal | WType_TopLevel )
{
	myInLoop = false;
	header = 0;
	#if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
	setMainWidgetTitle("");
	#endif
}

MyBaseDlg::~MyBaseDlg()
{

}

#if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
bool MyBaseDlg::setMainWidgetTitle( const QString &Title )
{
    if ( ! header )
    {
		header = new ZHeader(ZHeader::MAINDISPLAY_HEADER,this,"zHeader",Qt::WStyle_Tool|Qt::WStyle_Customize);
		header->setGeometry( ZGlobal::getHeaderR( false ) );
		setTitleBarWidget(header);
    }
    header->setPrimTitle(Title);
    return true;  
} 

bool MyBaseDlg::setSoftKey( ZSoftKey *cstWidget )
{
	return setCSTWidget(cstWidget);	
}

QSize MyBaseDlg::headerSize()
{
	return header->size();	 
}
#endif

int MyBaseDlg::exec() 
{
  setResult(0);
  show();
  myInLoop = TRUE;
  qApp->enter_loop();
  return result();
}

void MyBaseDlg::done( int r )
{
  hide();
  if (myInLoop) 
  {
    qApp->exit_loop();
  }
  setResult(r);
  if ( qApp->mainWidget() == this )
    qApp->quit();
}

void MyBaseDlg::accept() 
{
  done(Accepted);
}

void MyBaseDlg::reject() 
{
  done(Rejected);
}
