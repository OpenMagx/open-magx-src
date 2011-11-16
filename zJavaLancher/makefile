TOOLPREFIX:=	/arm-eabi
ARMLIB     := $(TOOLPREFIX)/arm-linux-gnueabi/lib

APPNAME  =       kvm

ifeq ($(PLATFORM),)
PLATFORM = EZX-ZN5
endif

ifeq ($(PLATFORM),EZX-Z6)
ARMLIB     := $(TOOLPREFIX)/arm-linux-gnueabi/lib
QTDIR	:=	$(TOOLPREFIX)/lib/qt-z6
EZXDIR	:=	$(TOOLPREFIX)/lib/ezx-z6
LINKLIB := -lm -lqte-mt -lezxappbase
DIRECTIV := -DEZX_Z6
TARGET	=       $(APPNAME)_Z6
endif

ifeq ($(PLATFORM),EZX-E8)
ARMLIB     := $(TOOLPREFIX)/arm-linux-gnueabi/lib_E8
QTDIR	:=	$(TOOLPREFIX)/lib/qt-e8
EZXDIR	:=	$(TOOLPREFIX)/lib/ezx-e8
LINKLIB := -lm -lqte-mt -lezxappbase
DIRECTIV := -DEZX_E8
TARGET	=       $(APPNAME)_E8
endif

ifeq ($(PLATFORM),EZX-VA76)
ARMLIB     := $(TOOLPREFIX)/arm-linux-gnueabi/lib_E8
QTDIR	:=	$(TOOLPREFIX)/lib/qt-e8
EZXDIR	:=	$(TOOLPREFIX)/lib/ezx-va76
LINKLIB := -lm -lqte-mt -lezxappbase
DIRECTIV := -DEZX_VA76
TARGET	=       $(APPNAME)_VA76
endif

ifeq ($(PLATFORM),EZX-ZN5)
QTDIR	:=	$(TOOLPREFIX)/lib/qt-zn5
EZXDIR	:=	$(TOOLPREFIX)/lib/ezx-zn5
LINKLIB := -lm -lqte-mt -lezxappbase
DIRECTIV := -DEZX_ZN5
TARGET	=       $(APPNAME)_ZN5
endif

UPLOAD_PATH :=  /mmc/mmca1/bin/
CC	=	$(TOOLPREFIX)/bin/arm-linux-gnueabi-gcc
CXX	=	$(TOOLPREFIX)/bin/arm-linux-gnueabi-g++
LD	=	$(TOOLPREFIX)/bin/arm-linux-gnueabi-g++
STRIP   =   $(TOOLPREFIX)/bin/arm-linux-strip
CFLAGS	=	-pipe -Wall -W -O2 -DNO_DEBUG $(INCPATH)
CXXFLAGS=	-pipe -DQWS -fno-exceptions -fno-rtti -Wall -W -O2 -DNO_DEBUG $(INCPATH)
INCPATH	=	-I$(QTDIR)/include -I$(EZXDIR)/include -I $(TOOLPREFIX)/arm-linux-gnueabi/include
LDFLAGS	=	-s
LINK	=	$(TOOLPREFIX)/bin/arm-linux-gnueabi-gcc
LFLAGS	=	
LIBS	=	$(SUBLIBS) -L$(ARMLIB) -L$(QTDIR)/lib -L$(EZXDIR)/lib $(LINKLIB)
LFLAGS	=	-Wl,-rpath-link,$(EZXDIR)/lib
MOC	=	$(QTDIR)/bin/moc
UIC	=	$(QTDIR)/bin/uic
#########################


####### Files

HEADERS =  
          
SOURCES =   main.cpp
          
OBJECTS =   main.o 
	           
INTERFACES =
UICDECLS =     
UICIMPLS =     
SRCMOC  =     
               
OBJMOC  =    
            
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

			
#----------------------------------------------
install: $(TARGETS)
	ncftpput -u root -p "" 192.168.16.2 $(UPLOAD_PATH) $(TARGETS)
