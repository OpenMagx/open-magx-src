# This Makefile writed by Ant-ON
#.
# App can compile for platform:
#	PLATFORM=EZX-Z6 (default)
#	PLATFORM=EZX-Z6W
#	PLATFORM=EZX-U9
#	PLATFORM=EZX-ZN5
#	PLATFORM=EZX-V8
#	PLATFORM=EZX-E8
#	PLATFORM=EZX-VE66
#	PLATFORM=EZX-EM35
#.
# For example - compile this source for Motorla ZN5:
#.
# cd /PROJECT_FOLDER/
# make clean
# make PLATFORM=EZX-ZN5
#.

######Config######
APPNAME    := zFonts
UPLOAD_PATH :=  /mmc/mmca1/
##################

TOOLPREFIX := /arm-eabi
ARMLIB     := $(TOOLPREFIX)/arm-linux-gnueabi/lib

ifeq ($(PLATFORM),)
PLATFORM = EZX-VE66
endif

ifeq ($(PLATFORM),EZX-Z6)
QTDIR	:=	$(TOOLPREFIX)/lib/qt-2.3.8
EZXDIR	:=	$(TOOLPREFIX)/lib/ezx-z6
LINKLIB := -lm -lqte-mt -lezxpm -ljpeg -lezxappbase -lezxtapi-xscale-r -llog_util -llighting
DIRECTIV := -DEZX_Z6
TARGET	=       $(APPNAME)_Z6
endif

ifeq ($(PLATFORM),EZX-V8)
QTDIR	:=	$(TOOLPREFIX)/lib/qt-v8
EZXDIR	:=	$(TOOLPREFIX)/lib/ezx-v8
LINKLIB := -lm -lqte-mt -lezxpm -lezxappbase 
DIRECTIV := -DEZX_V8
TARGET	=       $(APPNAME)_V8
ZNEWCHECKBOX = 1
endif

ifeq ($(PLATFORM),EZX-E8)
ARMLIB     := $(TOOLPREFIX)/arm-linux-gnueabi/lib_E8
QTDIR	:=	$(TOOLPREFIX)/lib/qt-e8
EZXDIR	:=	$(TOOLPREFIX)/lib/ezx-e8
LINKLIB := -lm -lqte-mt -lezxappbase
DIRECTIV := -DEZX_E8
TARGET	=       $(APPNAME)_E8
endif

ifeq ($(PLATFORM),EZX-EM30)
ARMLIB     := $(TOOLPREFIX)/arm-linux-gnueabi/lib_E8
QTDIR	:=	$(TOOLPREFIX)/lib/qt-em30
EZXDIR	:=	$(TOOLPREFIX)/lib/ezx-em30
EZXDIR2	:=	$(TOOLPREFIX)/lib/ezx-e8
LINKLIB := -lm -lqte-mt -lezxappbase
DIRECTIV := -DEZX_EM30
TARGET	=       $(APPNAME)_EM30
endif

ifeq ($(PLATFORM),EZX-U9)
QTDIR	:=	$(TOOLPREFIX)/lib/qt-zn5
EZXDIR	:=	$(TOOLPREFIX)/lib/ezx-u9
EZXDIR2	:=	$(TOOLPREFIX)/lib/ezx-zn5
LINKLIB := -lm -lqte-mt -lezxappbase
DIRECTIV := -DEZX_U9
TARGET	=       $(APPNAME)_U9
endif

ifeq ($(PLATFORM),EZX-Z6W)
QTDIR	:=	$(TOOLPREFIX)/lib/qt-z6w
EZXDIR	:=	$(TOOLPREFIX)/lib/ezx-z6w
LINKLIB := -lm -lqte-mt -lezxappbase
DIRECTIV := -DEZX_Z6W
TARGET	=       $(APPNAME)_Z6W
endif

ifeq ($(PLATFORM),EZX-ZN5)
QTDIR	:=	$(TOOLPREFIX)/lib/qt-zn5
EZXDIR	:=	$(TOOLPREFIX)/lib/ezx-zn5
LINKLIB := -lm -lqte-mt -lezxappbase
DIRECTIV := -DEZX_ZN5
TARGET	=       $(APPNAME)_ZN5
endif

ifeq ($(PLATFORM),EZX-EM35)
ARMLIB     := $(TOOLPREFIX)/arm-linux-gnueabi/lib_E8
QTDIR	:=	$(TOOLPREFIX)/lib/qt-em35
EZXDIR	:=	$(TOOLPREFIX)/lib/ezx-em35
LINKLIB := -lm -lqte-mt -lezxappbase
DIRECTIV := -DEZX_EM35
TARGET	=       $(APPNAME)_EM35
endif

ifeq ($(PLATFORM),EZX-VE66)
ARMLIB     := $(TOOLPREFIX)/arm-linux-gnueabi/lib_E8
QTDIR	:=	$(TOOLPREFIX)/lib/qt-em35
EZXDIR	:=	$(TOOLPREFIX)/lib/ezx-ve66
LINKLIB := -lm -lqte-mt -lezxappbase
DIRECTIV := -DEZX_VE66
TARGET	=       $(APPNAME)_VE66
endif

CC	    =	$(TOOLPREFIX)/bin/arm-linux-gnueabi-gcc
CXX	    =	$(TOOLPREFIX)/bin/arm-linux-gnueabi-g++
LD	    =	$(TOOLPREFIX)/bin/arm-linux-gnueabi-g++
STRIP   =   $(TOOLPREFIX)/bin/arm-linux-strip
CFLAGS	=	-pipe -Wall -W -O2 -DNO_DEBUG $(INCPATH)
CXXFLAGS=	-pipe -DQWS -fno-exceptions -fno-rtti -Wall -W -O2 -DNO_DEBUG $(DIRECTIV) $(INCPATH)
INCPATH	=	-I$(QTDIR)/include -I$(EZXDIR)/include -I$(EZXDIR2)/include -I $(TOOLPREFIX)/arm-linux-gnueabi/include
LDFLAGS	=	-s
LINK	=	$(TOOLPREFIX)/bin/arm-linux-gnueabi-gcc
LFLAGS	=	-Wl,-rpath-link,$(EZXDIR)/lib
LIBS	=	$(SUBLIBS) -L$(EZXDIR)/lib -L$(EZXDIR2)/lib -L$(ARMLIB) -L$(QTDIR)/lib $(LINKLIB)
MOC	    =	$(QTDIR)/bin/moc
UIC	    =	$(QTDIR)/bin/uic


####### Files
HEADERS =   ZFonts.h\
            GUI_Define.h\
            BaseDlg.h\
            ZAboutDlg.h
            
SOURCES =   main.cpp\
            ZFonts.cpp\
            BaseDlg.cpp\
            ZAboutDlg.cpp
	    
OBJECTS =   main.o ZFonts.o\
            BaseDlg.o\
            ZAboutDlg.o
            
SRCMOC	=	moc_ZFonts.cpp\
          moc_BaseDlg.cpp\
          moc_ZAboutDlg.cpp
                
OBJMOC	=	moc_ZFonts.o\
          moc_BaseDlg.o\
          moc_ZAboutDlg.o
                
TARGETS = 	$(TARGET)
INTERFACE_DECL_PATH = .



all: $(TARGET)

$(TARGET): $(UICDECLS) $(OBJECTS) $(OBJMOC) 
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJMOC) $(LIBS)
		$(STRIP) -s $(MAKETO)$(TARGET)
		
moc: $(SRCMOC)

clean:
	-rm -f $(OBJECTS) $(OBJMOC) $(SRCMOC) $(UICIMPLS) $(UICDECLS)
	-rm -f *~ core
	$(RM) *.o
	$(RM) moc_*.cpp

#--------- moc's -----------------------------
moc_ZFonts.o: moc_ZFonts.cpp ZFonts.h
moc_ZFonts.cpp: ZFonts.h
	$(MOC) ZFonts.h -o moc_ZFonts.cpp
  
moc_BaseDlg.o: moc_BaseDlg.cpp BaseDlg.h
moc_BaseDlg.cpp: BaseDlg.h
	$(MOC) BaseDlg.h -o moc_BaseDlg.cpp

moc_ZAboutDlg.o: moc_ZAboutDlg.cpp ZAboutDlg.h
moc_ZAboutDlg.cpp: ZAboutDlg.h
	$(MOC) ZAboutDlg.h -o moc_ZAboutDlg.cpp
				
#----------------------------------------------
install: $(TARGETS)
	ncftpput -u root -p "" 192.168.16.2 $(UPLOAD_PATH) $(TARGETS)
