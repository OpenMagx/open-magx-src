#/bin/sh

#
# Auto pack for Motorola MOD frimware
#
# Suport package format: 
#	- PEP  (Project Evolution Packege)
#	- MGX  (-)
#	- MPKG (Motorola Packege)
#
# Autor:   Ant-ON
# Version: 2.0
#

#App info
APPNAME="zTextEdit"
AUTOR="Ant-ON"
VER=`cat ZAboutDlg.h | grep APP_VER | awk '{ print $3 }' | sed 's/"//g'`
COMMENT="Text editor"
EXEC=$APPNAME
BIG_ICON=$APPNAME"_usr.png"
SMALL_ICON=$APPNAME"_small_usr.png"

#Other info
PACK_DIR=./../pack/
PACK_FOR_PLATFORM="Z6 V8 ZN5 U9 EM35"

#copy app file in packege folder
copy_app_file () 
{
	cp ./../$APPNAME\_$PLATFORM $COPY_TO/$APPNAME
	cp ./../appicon/*.* $COPY_TO/
	mkdir $COPY_TO/img/
	cp ./../img/*.* $COPY_TO/img/
	mkdir $COPY_TO/lng/
	cp ./../lng/*.* $COPY_TO/lng/
}

#procedure of create pack
pack_pep ()
{
	#create temp  dir
	mkdir libPep
	cd libPep
	mkdir app
	
	COPY_TO=./app
	copy_app_file
	
	#Gen descriptiom.ini
	echo -e "[Actions]\nSilent=0\nInstallApp=1\nAddAppToMenu=1\n\n[InstallApp]\nName="$APPNAME"\nExec="$EXEC"\nInstallPath=../../mmc/mmca1/.Programs/"$APPNAME"/\nAppLockable=0\nAuthor="$AUTOR"\nVersion="$VER"\nDaemon=1\nBigIcon="$BIG_ICON"\nAniIcon="$BIG_ICON"\nIcon="$SMALL_ICON"\n\n[AddAppToMenu]\nParentFolder=root\n" > description.ini

	#pack packege
	tar -czf $APPNAME\_$VER_FOR_NAME\_$PLATFORM.pep --gzip app/ description.ini
	
	#copy packege to PACK_DIR
	cp $APPNAME\_$VER_FOR_NAME\_$PLATFORM.pep $PACK_DIR
	
	#remove temp dir
	cd ..
	rm -r libPep	
}

pack_mgx ()
{
	#create temp  dir
	mkdir libMgx
	cd libMgx
	mkdir $APPNAME
	
	COPY_TO=./$APPNAME
	copy_app_file
	
	#gen cfg file
	echo -e "Name = "$APPNAME"\nExec = "$APPNAME"\nIcon = "$BIG_ICON"\nAuthor = "$AUTOR"\nVersion = $VER\nComment = "$COMMENT"\n" > $APPNAME/$APPNAME.cfg

	#pack packege
	7z a $APPNAME\_$VER_FOR_NAME\_$PLATFORM.mgx $APPNAME/
	
	#copy packege to PACK_DIR
	cp $APPNAME\_$VER_FOR_NAME\_$PLATFORM.mgx $PACK_DIR
	
	#remove temp dir
	cd ..
	rm -r libMgx	
}

pack_mpkg ()
{
	#create temp  dir
	mkdir libMpkg
	cd libMpkg
	
	COPY_TO=.
	copy_app_file
	
	#Gen desktop file
	echo -e "[Desktop Entry]\nName = "$APPNAME" "$VER" by "$AUTOR"\nDirectory = "$APPNAME"\nExec = "$EXEC"\nBigIcon = "$BIG_ICON"\nAniIcon = "$BIG_ICON"\nIcon="$SMALL_ICON"\n" > $APPNAME\_$VER_FOR_NAME\_$PLATFORM.desktop

	#pack packege
	tar -czf $APPNAME\_$VER_FOR_NAME\_$PLATFORM.mpkg --gzip *
	
	#copy packege to PACK_DIR
	cp $APPNAME\_$VER_FOR_NAME\_$PLATFORM.mpkg $PACK_DIR
	
	#remove temp dir
	cd ..
	rm -r libMpkg	
}

#Temp const
COPY_TO=.
PLATFORM=NA
PEP_PLATFORM="Z6 ZN5 U9 V8"
MGX_PLATFORM="E8 ZN5 U9 EM35 EM30"
MPKG_PLATFORM="Z6 V8"
VER_FOR_NAME=`echo $VER | sed 's/\./_/g'`

#main procedure
#[
if [ "$1" = "new" ]
then
	for p in $PACK_FOR_PLATFORM
	do
		make clean
		make PLATFORM=EZX-$p
	done
fi

if [ "$1" = "pack" ]
then
	PLATFORM=$2
	if [ `echo $PLATFORM | grep EZX` ]
	then
	PLATFORM=`echo $PLATFORM | sed 's/EZX-//g'`
	fi

	PEP_PLATFORM=`echo $PEP_PLATFORM  | grep $PLATFORM`
	MGX_PLATFORM=`echo $MGX_PLATFORM  | grep $PLATFORM`
	MPKG_PLATFORM=`echo $MPKG_PLATFORM | grep $PLATFORM`
	
	if [ ! "$PEP_PLATFORM" = "" ]
	then
		PEP_PLATFORM=$PLATFORM
	fi
	if [ ! "$MGX_PLATFORM" = "" ]
	then
		MGX_PLATFORM=$PLATFORM
	fi
	if [ ! "$MPKG_PLATFORM" = "" ]
	then
		MPKG_PLATFORM=$PLATFORM
	fi
	
fi

for p in $PEP_PLATFORM
do
	NEED=`echo $PACK_FOR_PLATFORM | grep $p`
	if [ ! "$NEED" = "" ]; then
		PLATFORM=$p
		pack_pep
	fi
done

for p in $MGX_PLATFORM
do
	NEED=`echo $PACK_FOR_PLATFORM | grep $p`
	if [ ! "$NEED" = "" ]; then
		PLATFORM=$p
		pack_mgx
	fi
done

for p in $MPKG_PLATFORM
do
	NEED=`echo $PACK_FOR_PLATFORM | grep $p`
	if [ ! "$NEED" = "" ]; then
		PLATFORM=$p
		pack_mpkg
	fi
done
#]
