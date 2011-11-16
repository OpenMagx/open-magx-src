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
#include "ZFonts.h"
#include <ZApplication.h>

ZFonts* zFonts;
ZApplication* app;

int main ( int argc, char **argv )
{
	app = new ZApplication ( argc, argv );
	int ret;
	zFonts = new ZFonts ( NULL, NULL );
	ret = app->exec();  
	delete zFonts;
	zFonts = NULL;
	delete app;
	app = NULL;
	return ret;
}
