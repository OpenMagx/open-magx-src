//
// C++ Implementation: TestMain
//
// Description:
//
//
// Author: BeZ <bezols@gmail.com>, (C) 2008
// Author: Ant-ON <bezols@gmail.com>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "zgui.h"
#include <ZApplication.h>
#include "lng.h"

ZGui* zgui;
ZApplication* app;
ZLng * lng;

int main ( int argc, char **argv )
{
	app = new ZApplication ( argc, argv );
	int ret;
	lng = new ZLng();
	zgui = new ZGui ( NULL, NULL );
	app->setMainWidget(zgui);
	ret = app->exec();
	delete zgui;
	zgui = NULL;
	delete app;
	app = NULL;
	return ret;
}
