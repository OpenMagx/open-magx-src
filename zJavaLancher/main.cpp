//
// C++ Implementation: zJavaLancher
//
// Description:
//
//
// Author: Ant-ON <prozanton@gmail.com>, (C) 2009
//
//
#include <ZApplication.h>
#include <qcopchannel_qws.h>
#include <qstring.h>
#include <qapplication.h>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include "lm_app_interface.h"

ZApplication* app;

using namespace std;

int main ( int argc, char **argv )
{
	app = new ZApplication ( argc, argv );

	delete app;
	app = NULL;
	return 1;
}
