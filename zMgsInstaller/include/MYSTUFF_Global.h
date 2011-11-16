// Writet by Ant-ON, <prozanton@gmail.com>
//
// Date: 15.11.10
//
// Lib: libezxmystuff-base.so
//

#ifndef MYSTUFF_GLOBAL_H
#define MYSTUFF_GLOBAL_H

#include <qstring.h>

class STUFF_Global
{
public:
    static bool getDiskSize( const QString& diskName, double& diskFreeSize, double& diskTotalSize );
    static uint getSize( const QString& dirName );    
	static bool isReadOnly( const QString& fileName);

	// ...
    
};

#endif //MYSTUFF_GLOBAL_H
