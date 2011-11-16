TOOLPREFIX := /arm-eabi
ARMLIB     := $(TOOLPREFIX)/arm-linux-gnueabi/lib
APPNAME    := zCpuOverclock

ifeq ($(PLATFORM),)
PLATFORM = EZX-ZN5
endif

ifeq ($(PLATFORM),EZX-Z6)
QTDIR	:=	$(TOOLPREFIX)/lib/qt-2.3.8
EZXDIR	:=	$(TOOLPREFIX)/lib/ezx-z6
LINKLIB := -lm -lqte-mt -lezxpm -ljpeg -lezxappbase -lezxtapi-xscale-r -llog_util -llighting
DIRECTIV := -DEZX_Z6
TARGET	=       $(APPNAME)
endif

ifeq ($(PLATFORM),EZX-E8)
ARMLIB     := $(TOOLPREFIX)/arm-linux-gnueabi/lib_E8
QTDIR	:=	$(TOOLPREFIX)/lib/qt-e8
EZXDIR	:=	$(TOOLPREFIX)/lib/ezx-e8
LINKLIB := -lm -lqte-mt -lezxappbase
DIRECTIV := -DEZX_E8 -DNO_KEYLOCK
TARGET	=       $(APPNAME)_E8
endif

ifeq ($(PLATFORM),EZX-ZN5)
QTDIR	:=	$(TOOLPREFIX)/lib/qt-zn5
EZXDIR	:=	$(TOOLPREFIX)/lib/ezx-zn5
LINKLIB := -lm -lqte-mt -lezxappbase
DIRECTIV := -DEZX_ZN5 -DNO_KEYLOCK
TARGET	=       $(APPNAME)_ZN5
endif


CC	    =	$(TOOLPREFIX)/bin/arm-linux-gnueabi-gcc
CXX	    =	$(TOOLPREFIX)/bin/arm-linux-gnueabi-g++
LD	    =	$(TOOLPREFIX)/bin/arm-linux-gnueabi-g++
STRIP   =   $(TOOLPREFIX)/bin/arm-linux-strip
CFLAGS	=	-pipe -Wall -W -O2 -DNO_DEBUG $(INCPATH)
CXXFLAGS=	-pipe -DQWS -fno-exceptions -fno-rtti -Wall -W -O2 -DNO_DEBUG $(DIRECTIV) $(INCPATH)
INCPATH	=	-I$(QTDIR)/include -I$(EZXDIR2)/include -I$(EZXDIR)/include -I $(TOOLPREFIX)/arm-linux-gnueabi/include
LDFLAGS	=	-s
LINK	=	$(TOOLPREFIX)/bin/arm-linux-gnueabi-gcc
LFLAGS	=	-Wl,-rpath-link,$(EZXDIR)/lib
LIBS	=	$(SUBLIBS) -L$(EZXDIR2)/lib -L$(EZXDIR)/lib -L$(ARMLIB) -L$(QTDIR)/lib $(LINKLIB)
MOC	    =	$(QTDIR)/bin/moc
UIC	    =	$(QTDIR)/bin/uic


####### Files
HEADERS =   QOverclockApplication.h
            
SOURCES =   main.cpp QOverclockApplication.cpp
	    
OBJECTS =   main.o QOverclockApplication.o
            
INTERFACES =
UICDECLS =	
UICIMPLS =	
SRCMOC	=	moc_QOverclockApplication.cpp
                
OBJMOC	=	moc_QOverclockApplication.o
                
DIST	=	
TARGETS = 	$(TARGET)
INTERFACE_DECL_PATH = .



all: $(TARGET)

$(TARGET): $(UICDECLS) $(OBJECTS) $(OBJMOC) 
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJMOC) $(LIBS)
	/arm-eabi/bin/arm-linux-strip -s $(TARGET)
moc: $(SRCMOC)

clean:
	-rm -f $(OBJECTS) $(OBJMOC) $(SRCMOC) $(UICIMPLS) $(UICDECLS) $(TARGET)
	-rm -f *~ core
	$(RM) *.o
	$(RM) moc_*.cpp

#--------- moc's -----------------------------
moc_%.cpp: %.h
	$(MOC) $< -o $@


install: $(TARGETS)
	ncftpput -u root -p "" 192.168.16.2 $(UPLOAD_PATH) $(TARGETS)
