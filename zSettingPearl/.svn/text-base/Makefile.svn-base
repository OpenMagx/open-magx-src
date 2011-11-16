TOOLPREFIX := /arm-eabi
ARMLIB     := $(TOOLPREFIX)/arm-linux-gnueabi/lib
UPLOAD_PATH = /ezxlocal/download/mystuff/.system/zSettings

ifeq ($(PLATFORM),)
PLATFORM = EZX-VE66
endif

ifeq ($(PLATFORM),EZX-U9)
QTDIR	:=	$(TOOLPREFIX)/lib/qt-zn5
EZXDIR	:=	$(TOOLPREFIX)/lib/ezx-u9
EZXDIR2	:=	$(TOOLPREFIX)/lib/ezx-zn5
DIRECTIV := -DEZX_U9
TARGET	=       zSettings_U9
endif

ifeq ($(PLATFORM),EZX-ZN5)
QTDIR	:=	$(TOOLPREFIX)/lib/qt-zn5
EZXDIR	:=	$(TOOLPREFIX)/lib/ezx-zn5
DIRECTIV := -DEZX_ZN5
TARGET	=       zSettings_ZN5
endif

ifeq ($(PLATFORM),EZX-E8)
ARMLIB     := $(TOOLPREFIX)/arm-linux-gnueabi/lib_E8
QTDIR	:=	$(TOOLPREFIX)/lib/qt-e8
EZXDIR	:=	$(TOOLPREFIX)/lib/ezx-e8
DIRECTIV := -DEZX_E8
TARGET	=       zSettings_E8
endif

ifeq ($(PLATFORM),EZX-VE66)
ARMLIB     := $(TOOLPREFIX)/arm-linux-gnueabi/lib_E8
QTDIR	:=	$(TOOLPREFIX)/lib/qt-ve66
EZXDIR	:=	$(TOOLPREFIX)/lib/ezx-ve66
DIRECTIV := -DEZX_VE66
TARGET	=       zSettings
endif

CC	=	$(TOOLPREFIX)/bin/arm-linux-gnueabi-gcc
CXX	=	$(TOOLPREFIX)/bin/arm-linux-gnueabi-g++
LD	=	$(TOOLPREFIX)/bin/arm-linux-gnueabi-g++
STRIP = $(TOOLPREFIX)/bin/arm-linux-strip
CFLAGS	=	-pipe -Wall -W -O2 -DNO_DEBUG $(INCPATH)
CXXFLAGS=	-pipe -DQWS -fno-exceptions -fno-rtti -Wall -W -O2 -DNO_DEBUG $(DIRECTIV) $(INCPATH) -DWITHOUT_EDIT_INTERNET_PROFILE -DWITHOUT_EDIT_TEXT_NUM
INCPATH	=   -I$(QTDIR)/include -I$(EZXDIR)/include -I$(EZXDIR2)/include -I$(TOOLPREFIX)/arm-linux-gnueabi/include
LDFLAGS	=	-s 
LFLAGS  =   -Wl,-rpath-link,$(EZXDIR)/lib
LINK	=	$(TOOLPREFIX)/bin/arm-linux-gnueabi-gcc
LIBS	=	$(SUBLIBS) -L./lib -L$(ARMLIB) -L$(EZXDIR)/lib -L$(QTDIR)/lib -lm -lqte-mt -lezxappbase -lflexid
MOC	=	$(QTDIR)/bin/moc
UIC	=	$(QTDIR)/bin/uic


####### Files
HEADERS =   zSettings.h\
            GUI_Define.h\
            BaseDlg.h\
            lng.h\
            ZOptionItem.h
			
SOURCES =   main.cpp\
            zSettings.cpp\
            BaseDlg.cpp\
            lng.cpp\
            ZOptionItem.cpp
            
OBJECTS =   main.o zSettings.o\
            BaseDlg.o\
			lng.o\
            ZOptionItem.o
            
SRCMOC	=	moc_zSettings.cpp\
          moc_BaseDlg.cpp\
		  moc_lng.cpp\
          moc_BaseDlg.cpp
                
OBJMOC	=	moc_zSettings.o\
          moc_BaseDlg.o\
		  moc_lng.o\
          moc_ZOptionItem.o
                
TARGETS = 	$(TARGET)
INTERFACE_DECL_PATH = .



all: $(TARGET)

$(TARGET): $(UICDECLS) $(OBJECTS) $(OBJMOC) 
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJMOC) $(LIBS)
		$(STRIP) -s $(TARGET)

moc: $(SRCMOC)

clean:
	-rm -f $(OBJECTS) $(OBJMOC) $(SRCMOC) $(UICIMPLS) $(UICDECLS) $(TARGET)
	-rm -f *~ core
	$(RM) *.o
	$(RM) moc_*.cpp

#--------- moc's -----------------------------
moc_zSettings.o: moc_zSettings.cpp zSettings.h
moc_zSettings.cpp: zSettings.h
	$(MOC) zSettings.h -o moc_zSettings.cpp
  
moc_BaseDlg.o: moc_BaseDlg.cpp BaseDlg.h
moc_BaseDlg.cpp: BaseDlg.h
	$(MOC) BaseDlg.h -o moc_BaseDlg.cpp
		
moc_lng.o: moc_lng.cpp lng.h
moc_lng.cpp: lng.h
	$(MOC) lng.h -o moc_lng.cpp		
	
moc_ZOptionItem.o: moc_ZOptionItem.cpp ZOptionItem.h
moc_ZOptionItem.cpp: ZOptionItem.h
	$(MOC) ZOptionItem.h -o moc_ZOptionItem.cpp					
			
#----------------------------------------------
install: $(TARGETS)
	ncftpput -u root -p "" 192.168.16.2 $(UPLOAD_PATH) $(TARGETS)
