//
// Project: ZSettigs
//
// Description:
//
// Author: Ant-ON <prozanton@gmail.com>, (C) 2009-2011
//
//

#include "zSettings.h"
#include "lng.h"
#include <ZApplication.h>
#include <qcopchannel_qws.h>

ZSettigs *zSettigs;
ZApplication* app;
ZLng* lng;

int main ( int argc, char **argv )
{
	app = new ZApplication ( argc, argv );
	int ret;
	
	qDebug("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\");
	qDebug("\\  zSetting 1.1 for Perl Mod             \\");
	qDebug("\\  Develop by Ant-ON                     \\");	
	qDebug("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\");	
  
    lng = new ZLng();
    
	zSettigs = new ZSettigs ( NULL, NULL );
	zSettigs->toLog("end init gui");
	app->setMainWidget(zSettigs);
	zSettigs->toLog("setMainWidget");
	zSettigs->show();
	ret = app->exec();  
	delete zSettigs;
	zSettigs = NULL;
  
	delete app;
	app = NULL;
	return ret;
}
