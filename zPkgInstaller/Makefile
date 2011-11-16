TOOLPREFIX:=	/arm-eabi
ARMLIB     := $(TOOLPREFIX)/arm-linux-gnueabi/lib

APPNAME  = zPkgInstaller

ifeq ($(PLATFORM),)
PLATFORM = EZX-VE66
endif

ifeq ($(PLATFORM),EZX-VE66)
ARMLIB     := $(TOOLPREFIX)/arm-linux-gnueabi/lib_E8
QTDIR	:=	$(TOOLPREFIX)/lib/qt-ve66
EZXDIR	:=	$(TOOLPREFIX)/lib/ezx-ve66
LINKLIB := -lm -lqte-mt -lezxappbase -lampackage -lezxmystuff-base -L/home/anton/rootfs_ve66/usr/mlib
DIRECTIV := -DEZX_VE66
TARGET	=       $(APPNAME)
endif

UPLOAD_PATH :=  /ezxlocal/download/mystuff/.system/zPkgInstaller
CC	=	$(TOOLPREFIX)/bin/arm-linux-gnueabi-gcc
CXX	=	$(TOOLPREFIX)/bin/arm-linux-gnueabi-g++
LD	=	$(TOOLPREFIX)/bin/arm-linux-gnueabi-g++
STRIP   =   $(TOOLPREFIX)/bin/arm-linux-strip
CFLAGS	=	-pipe -Wall -W -O2 -DNO_DEBUG $(INCPATH)
CXXFLAGS=	-pipe -DQWS -fno-exceptions -fno-rtti -Wall -W -O2 -DNO_DEBUG $(INCPATH)
INCPATH	=	-I./include -I$(QTDIR)/include -I$(EZXDIR)/include -I $(TOOLPREFIX)/arm-linux-gnueabi/include
LDFLAGS	=	-s
LINK	=	$(TOOLPREFIX)/bin/arm-linux-gnueabi-gcc
LFLAGS	=	
LIBS	=	$(SUBLIBS) -L$(ARMLIB) -L/arm-eabi/lib/ezx-ve66/lib -L/home/anton/rootfs_ve66/usr/lib $(LINKLIB)
LFLAGS	=	-Wl,-rpath-link,./lib -Wl,-rpath-link,/home/anton/rootfs_ve66/usr/lib -Wl,-rpath-link,/home/anton/rootfs_ve66/usr/mlib -Wl,-rpath-link,$(EZXDIR)/lib 
MOC	=	$(QTDIR)/bin/moc
UIC	=	$(QTDIR)/bin/uic
#########################


####### Files

HEADERS = xInstaller.h
          
SOURCES = main.cpp xInstaller.cpp
          
OBJECTS =  main.o xInstaller.o
     
SRCMOC  = moc_xInstaller.cpp
               
OBJMOC  = moc_xInstallern.o
            
DIST    =       
TARGETS =       $(TARGET)
INTERFACE_DECL_PATH = .


all: $(TARGET)

$(TARGET): $(UICDECLS) $(OBJECTS) $(OBJMOC) 
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJMOC) $(LIBS)
		$(STRIP) -s $(MAKETO)$(TARGET)
		
moc: $(SRCMOC)

tmake: Makefile

#Makefile: .pro
#	tmake .pro -o Makefile

dist:
	$(TAR) .tar .pro $(SOURCES) $(HEADERS) $(INTERFACES) $(DIST)
	$(GZIP) .tar

clean:
	-rm -f $(OBJECTS) $(OBJMOC) $(SRCMOC) $(UICIMPLS) $(UICDECLS) $(TARGET)
	-rm -f *~ core

#--------- moc's -----------------------------
moc_xInstallern.o: moc_xInstallern.cpp xInstaller.h
moc_xInstallern.cpp: xInstaller.h
	$(MOC) xInstaller.h -o moc_xInstallern.cpp
			
#----------------------------------------------
install: $(TARGETS)
	ncftpput -u root -p "" 192.168.16.2 $(UPLOAD_PATH) $(TARGETS)
