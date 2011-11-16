//
// Poject name: zAudio
//
// Version: 0.1
//
// Description: Programm for change audio settings
//
// Author: Ant-ON <prozanton@gmail.com>, (C) 2010
//

#include "zgui.h"
#include <ZApplication.h>

ZGui* zgui;
ZApplication* app;

int main ( int argc, char **argv )
{
	app = new ZApplication ( argc, argv );
	int ret;
	zgui = new ZGui ( NULL, NULL );
	ret = app->exec();  
	delete zgui;
	zgui = NULL;
	delete app;
	app = NULL;
	return ret;
}
