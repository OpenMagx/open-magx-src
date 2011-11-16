//
// Project: zTextEdit
//
// Description: Text editor for MAGX
//
// Author: Ant-ON <prozanton@gmail.com>, (C) 2009-2010
//

//My
#include "zgui.h"
#include "BaseDlg.h"
#include "ZAboutDlg.h"
#include "ZFileDlg.h"
#include "ZSettingsDlg.h"
#include "ZFindDlg.h"

//C++/C
#include "stdio.h"
#include <stdlib.h>
#include <unistd.h>

//Qt
#include <qpixmap.h>
#include <qfile.h>
#include <qcopchannel_qws.h>
#include <qclipboard.h>
#include <qdir.h>
#include <qtextstream.h>

//EZX
#include <ZApplication.h>
#include <ZListBox.h>
#include <ZSoftKey.h>
#include <ZOptionsMenu.h>
#include <ZMessageDlg.h>
#include <ZLabel.h>
#include <ZFormContainer.h>
#include <ZSingleCaptureDlg.h>
#include <ZAppInfoArea.h>

#if defined(EZX_ZN5) || defined(EZX_U9)
#define MENU_FIX QString("  ")
#else
#define MENU_FIX ""
#endif

#include "log.h"

#include "lng.h"
extern ZLng* lng;

ZGui::ZGui ( QWidget* perent, const char*, WFlags )
	: MyBaseDlg()
{
	fixEditOff = false;
	CreateWindow ( perent );
	show();
}

ZGui::~ZGui()
{

}

void ZGui::setSettingToEdit(ZMultiLineEdit * eWidget)
{
	eWidget->installEventFilter( this );
	eWidget->setSizePolicy( QSizePolicy ( QSizePolicy::Expanding, QSizePolicy::Expanding ) );
	eWidget->setInsertionMethod ( ZMultiLineEdit::atPosNoSelected );
	eWidget->setVerScrollBar( true, false );
	eWidget->setMaxLineLength(-1);
	eWidget->setAutoUpdate(true);	
	eWidget->setUnderline(cfg_underline);
	eWidget->setWordWrap(ZMultiLineEdit::WidgetWidth);
	eWidget->setFontPercent( (float)cfg_fontSize/(float)22 );
	eWidget->setFixedWidth( SCREEN_WIDTH );
}

void ZGui::CreateWindow ( QWidget * )
{
	///Set title window
	setMainWidgetTitle ( "zTextEdit" );
	
	///load lenguage
	ProgDir = getProgramDir();
	lng->ProgDir = ProgDir;
	lng->autoLoadLng();

	///Load settings
	ZConfig cfg(ProgDir+"/zTextEdit.cfg");
	cfg_fontSize = cfg.readNumEntry(QString("GUI"), QString("FontSize"), 15);
	cfg_underline = cfg.readBoolEntry(QString("GUI"), QString("Underline"), true);
	cfg_autoOpen = cfg.readBoolEntry(QString("GUI"), QString("AutoOpen"), false);
	cfg_menuCopy = cfg.readBoolEntry(QString("GUI"), QString("MenuCopyOnDial"), false);
	#ifdef MDI
	curDlg=0;
	countDlg=1;
	#endif
	if (cfg_autoOpen)
	{
		sFileName = cfg.readEntry(QString("LastFile"), QString("FileName"), "");
		sFilePath = cfg.readEntry(QString("LastFile"), QString("FilePath"), "");
	}
	cfg_chineseCodeDetect = cfg.readBoolEntry(QString("Enginea"), QString("ChineseCodeDetect"), false);
	#ifdef SELECT_CUR_LINE
	cfg_selCurLine = cfg.readBoolEntry(QString("GUI"), QString("SelCurLine"), false);
	#endif
	
	/*
	#if !( defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W) )
	cfg_infoBar = cfg.readBoolEntry(QString("GUI"), QString("InfoBar"), false);
	
	//Create info bar
	if ( cfg_infoBar )
	{
  		ZAppInfoArea *pAIA = new ZAppInfoArea(this);
  		#if defined(EZX_Z6) || defined(EZX_V8)
  		pAIA->setActArea( ZAppInfoArea::no_progress_meter );
  		#else
  		pAIA->setActArea( ZAppInfoArea::NO_PROGRESS_METER );
  		#endif
  		pAIA->setInputArea();
  		setAppInfoArea( pAIA );
	}
	#endif
	*/

	///Create main widget on window
	#ifndef MDI
	edit = new ZMultiLineEdit( this, false, 1, "ZMultiLineEdit"  );
	CHECK_PTR(edit);
	setSettingToEdit(edit);
	setContentWidget(edit);
	edit->setGeometry( ZGlobal::getContentR( false ) );
	#else
	wStack = new QWidgetStack(this);
	curDlg=0;
    zmeEditList[curDlg] = new ZMultiLineEdit( this, false, 1, "ZMultiLineEdit"  );
    dlgCapList[curDlg] = "New";
	CHECK_PTR(zmeEditList[curDlg]);
	setSettingToEdit(zmeEditList[curDlg]);
	wStack->addWidget(zmeEditList[curDlg], curDlg);
	setContentWidget(wStack);
	wStack->raiseWidget(curDlg);
	#endif
	textCode=0;

	///Create SoftKey and Menu
	ZSoftKey *softKey = new ZSoftKey ( NULL , this , this );
	
	QPixmap* pm  = new QPixmap();
	QRect rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);	
	MainMenu = new ZOptionsMenu ( rect, softKey, NULL, 0 );
	MainMenu->setItemSpacing(10);	
	
	///File Menu
	FileMenu = new ZOptionsMenu ( rect, softKey, NULL, 0 );
	FileMenu->setItemSpacing(10);
	pm->load(ProgDir+ "/img/new.png");
	FileMenu->insertItem ( MENU_FIX+lng->getString("NEW"), NULL, pm, true, 0, 0 );
	pm->load(ProgDir+ "/img/open.png");	
	FileMenu->insertItem ( MENU_FIX+lng->getString("OPEN"), NULL, pm, true, 1, 1 );
	pm->load(ProgDir+ "/img/save.png");	
	FileMenu->insertItem ( MENU_FIX+lng->getString("SAVE"), NULL, pm, true, 2, 2 );
	pm->load(ProgDir+ "/img/fake.png");
	FileMenu->insertItem ( MENU_FIX+lng->getString("SAVEAS"), NULL, pm, true, 3, 3 );	
	
	FileMenu->connectItem ( 0, this, SLOT ( slot_fileNew() ) );
	FileMenu->connectItem ( 1, this, SLOT ( slot_fileOpen() ) );	
	FileMenu->connectItem ( 2, this, SLOT ( slot_fileSave() ) );
	FileMenu->connectItem ( 3, this, SLOT ( slot_fileSaveAs() ) );	

	pm->load(ProgDir+ "/img/new.png");
	MainMenu->insertItem ( MENU_FIX+lng->getString("FILE"), FileMenu, pm , true , 1, 1 );  

	///Edit Menu
	EditMenu = new ZOptionsMenu ( rect, softKey, NULL, 0 );
	EditMenu->setItemSpacing(10);
	pm->load(ProgDir+ "/img/copy.png");
	EditMenu->insertItem ( MENU_FIX+lng->getString("COPY"), NULL, pm, true, 0, 0);
	pm->load(ProgDir+ "/img/cut.png");
	EditMenu->insertItem ( MENU_FIX+lng->getString("CUT"), NULL, pm, true, 1, 1);
	pm->load(ProgDir+ "/img/paste.png");
	EditMenu->insertItem ( MENU_FIX+lng->getString("PASTE"), NULL, pm, true, 2, 2);
	pm->load(ProgDir+ "/img/select_all.png");
	EditMenu->insertItem ( MENU_FIX+lng->getString("SELECT_ALL"), NULL, pm, true, 3, 3);
	pm->load(ProgDir+ "/img/fake.png");
	EditMenu->insertItem ( MENU_FIX+lng->getString("SELECT_BLOCK"), NULL, pm, true, 4, 4);	
	
	EditMenu->connectItem ( 0, this, SLOT ( slot_editCopy() ) );
	EditMenu->connectItem ( 1, this, SLOT ( slot_editCut() ) );
	EditMenu->connectItem ( 2, this, SLOT ( slot_editPaste() ) );
	EditMenu->connectItem ( 3, this, SLOT ( slot_editSelAll() ) );
	EditMenu->connectItem ( 4, this, SLOT ( slot_editSelectBlock() ) );
	
	pm->load(ProgDir+ "/img/edit.png");
	MainMenu->insertItem ( MENU_FIX+lng->getString("EDIT"), EditMenu, pm , true , 2, 2 );  
	
	CodeMenu = new ZOptionsMenu ( rect, softKey, NULL, 0 );
	CodeMenu->setItemSpacing(10);
	#if !(defined(EZX_Z6) || defined(EZX_V8))
	CodeMenu->insertItem ( "UTF-8", NULL, NULL, true, 0, 0, false, true, true );	
	CodeMenu->insertItem ( "Win1251", NULL, NULL, true, 1, 1, false, true );
	CodeMenu->insertItem ( "KOI8-R", NULL, NULL, true, 2, 2, false, true );	
	CodeMenu->insertItem ( "ISO8859-1", NULL, NULL, true, 3, 3, false, true );
	CodeMenu->insertItem ( "ISO8859-2", NULL, NULL, true, 4, 4, false, true );
	CodeMenu->insertItem ( "ISO8859-5", NULL, NULL, true, 5, 5, false, true );
	CodeMenu->insertItem ( "KOI8-U", NULL, NULL, true, 6, 6, false, true );	
	CodeMenu->insertItem ( "Big5", NULL, NULL, true, 7, 7, false, true );	
	CodeMenu->insertItem ( "GBK", NULL, NULL, true, 8, 8, false, true );	
	#else
	CodeMenu->insertItem ( "UTF-8", NULL, NULL, NULL, true, true, true, 0, 0 );	
	CodeMenu->insertItem ( "Win1251", NULL, NULL, NULL, true, true, false, 1, 1 );
	CodeMenu->insertItem ( "KOI8-R", NULL, NULL, NULL, true, true, false, 2, 2 );	
	CodeMenu->insertItem ( "ISO8859-1", NULL, NULL, NULL, true, true, false, 3, 3 );
	CodeMenu->insertItem ( "ISO8859-2", NULL, NULL, NULL, true, true, false, 4, 4 );
	CodeMenu->insertItem ( "ISO8859-5", NULL, NULL, NULL, true, true, false, 5, 5 );
	CodeMenu->insertItem ( "KOI8-U", NULL, NULL, NULL, true, true, false, 6, 6 );	
	CodeMenu->insertItem ( "Big5", NULL, NULL, NULL, true, true, false, 7, 7 );
	CodeMenu->insertItem ( "GBK", NULL, NULL, NULL, true, true, false, 8, 8 );
	#endif	

	#define CODEC_COUNT 9
	connect( CodeMenu, SIGNAL( activated( int ) ), this, SLOT( slot_codecChenged( int ) ) );
	
	pm->load(ProgDir+ "/img/fake.png");
	MainMenu->insertItem ( MENU_FIX+lng->getString("CODE"), CodeMenu, pm, true , 3, 3 );  
	
	#ifdef MDI
	DlgMenu = new ZOptionsMenu ( rect, softKey, NULL, 0 );
	DlgMenu->setItemSpacing(10);	
	connect( DlgMenu, SIGNAL( activated( int ) ), this, SLOT( slot_dlgChenged( int ) ) );
	pm->load(ProgDir+ "/img/document.png");
	MainMenu->insertItem ( MENU_FIX+lng->getString("DLG"), DlgMenu, pm, true , 3, 3 ); 
	buildDlgMenu();
	#endif
	
	pm->load(ProgDir+ "/img/find.png");
	MainMenu->insertItem ( MENU_FIX+lng->getString("SEARCH"), NULL, pm, true, 4, 4 );		
	pm->load(ProgDir+ "/img/options.png");
	MainMenu->insertItem ( MENU_FIX+lng->getString("OPTION"), NULL, pm, true, 5, 5 );	
	pm->load(ProgDir+ "/img/about.png");
	MainMenu->insertItem ( MENU_FIX+lng->getString("ABOUT"), NULL, pm, true, 6, 6 );	
	pm->load(ProgDir+ "/img/exit.png");
	MainMenu->insertItem ( MENU_FIX+lng->getString("EXIT"), NULL, pm, true, 7, 7 );
	
	MainMenu->connectItem ( 4, this, SLOT ( slot_fileFind() ) );
	MainMenu->connectItem ( 5, this, SLOT ( slot_settings() ) );	
	MainMenu->connectItem ( 6, this, SLOT ( slot_about() ) );
	MainMenu->connectItem ( 7, this, SLOT ( slot_exit() ) );	
	
	softKey->setTextForOptMenuHide(lng->getString("FILE"));
	softKey->setText ( ZSoftKey::LEFT, lng->getString("FILE"), ( ZSoftKey::TEXT_PRIORITY ) 0 );
	softKey->setText ( ZSoftKey::RIGHT, lng->getString("EXIT"), ( ZSoftKey::TEXT_PRIORITY ) 0 );
	softKey->setOptMenu ( ZSoftKey::LEFT, MainMenu );
	softKey->setClickedSlot ( ZSoftKey::RIGHT, this, SLOT ( slot_exit() ) );
	
	#if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
	edit->setFixedHeight( SCREEN_HEIGHT - headerSize().height() - softKey->height());
	#endif
	
	setSoftKey ( softKey );
	
	///Connect std signal
	#ifndef EZX_VE66
	connect( qApp, SIGNAL(signalRaise()), this, SLOT(slot_Raise()) );
	connect( qApp, SIGNAL(askReturnToIdle(int)), this, SLOT(slot_ReturnToIdle(int)) );	
	#endif
	
	///init peremen
	textCode = 0;
	pos = NULL;
	isMarck = false;
	
	///load file if need
	if ( !cfg_autoOpen )
		sFileName = "";	
		
	QFile file;
	if ( qApp->argc() > 1  )
	{
		sFileName = "";
		if ( file.exists(QString::fromUtf8(qApp->argv()[1])) )
			sFileName = QString::fromUtf8(qApp->argv()[1]);
		else
		if ( qApp->argc() > 2  )
			if ( file.exists(QString::fromUtf8(qApp->argv()[2])) )
				sFileName = QString::fromUtf8(qApp->argv()[2]);
		sFilePath = getFilePath(sFileName);
		sFileName = getFileName(sFileName);			
	}

	if ( sFileName.isEmpty() || sFilePath.isEmpty() )
		slot_fileNew();
	else
		load(sFilePath+sFileName);
}

QString ZGui::getProgramDir()
{
	ProgDir = QString ( qApp->argv() [0] ) ;
	int i = ProgDir.findRev ( "/" );
	ProgDir.remove ( i+1, ProgDir.length() - i );
	return ProgDir;
}

void ZGui::slot_editCopy() 
{
	#if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
	if ( isSelectText() )
		QApplication::clipboard()->setText( getSelectText() );
	else
		QApplication::clipboard()->setText( edit->text() );	
	#else
	edit->copy();
	#endif
	
	if (pos != NULL)
	{
		delete pos;
		pos = NULL;
		isMarck = false;
	}	
}

void ZGui::slot_editPaste()
{
	#if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)	
	if ( isSelectText() )
		edit->deleteText();
		
	edit->insert( QApplication::clipboard()->text() );
	
	#else
	edit->paste();
	#endif
	
	if (pos != NULL)
	{
		delete pos;
		pos = NULL;
		isMarck = false;
	}	
}

void ZGui::slot_editCut()
{
	#if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
	slot_editCopy();
	if ( isSelectText() )
		edit->deleteText();
	else
		edit->clear();	
		
	isSelected = false;
	#else
	edit->cut();
	#endif
}

void ZGui::slot_editSelectBlock()
{
	int iSelX = 0;
	int iSelY = 0;	
	if (pos == NULL)
	{	
		edit->getCursorPosition( &iSelX, &iSelY );
		pos = new QPoint(iSelX,iSelY);
		isMarck = true;
	} else
	{
		edit->getCursorPosition( &iSelX, &iSelY );
		edit->setCursorPosition( pos->x(), pos->y(), false );
		edit->setCursorPosition( iSelX, iSelY, true );
		delete pos;
		pos = NULL;
		isMarck = false;
		#if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
		isSelected = true;
		#endif
	}
}

void ZGui::slot_editSelAll()
{
	edit->selectAll();
	#if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
	isSelected = true;
	#endif
	
	if (pos != NULL)
	{
		delete pos;
		pos = NULL;
		isMarck = false;
	}
}

void ZGui::slot_codecChenged(int n)
{
	if (n == textCode)
		return;
	
	int i;
	for ( i=0;i<CODEC_COUNT;i++)
		CodeMenu->setItemChecked(i, false);
	CodeMenu->setItemChecked(n, true);
	textCode = n;
	
	if ( sFileName.isEmpty() || sFilePath.isEmpty() )
		return;
	
	ZMessageDlg * pConfirmation = new ZMessageDlg ( lng->getString("CODE"), lng->getString("RELOAD_FILE"), ( ZMessageDlg::MessageDlgType )1, 0, this, "2", true, 0 );
    if ( pConfirmation->exec() == QDialog::Accepted )
    {
		int iSelX = 0;
		int iSelY = 0;	

		edit->getCursorPosition( &iSelX, &iSelY );
			
		load(sFilePath+sFileName, false);
		
		edit->setCursorPosition( iSelX, iSelY, false );
    }
	delete pConfirmation;
}

#if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
QString ZGui::getSelectText()
{
	
    int markBeginX, markBeginY;
    int markEndX, markEndY;
    if ( !edit->getMarkedRegion( &markBeginY, &markBeginX, &markEndY, &markEndX ) )
    {
        return "";
    }
    if ( markBeginY == markEndY )
    {
        QString *s  = edit->getString( markBeginY );
        return s->mid( markBeginX, markEndX - markBeginX );
    }
    else
    {
        QString *firstS, *lastS;
        firstS = edit->getString( markBeginY );
        lastS  = edit->getString( markEndY );
        int i;
        QString tmp;
        if ( firstS )
            tmp += firstS->mid(markBeginX);
        tmp += '\n';
        for( i = markBeginY + 1; i < markEndY ; i++ )
        {
            tmp += *edit->getString(i);
            tmp += '\n';
        }

        if ( lastS )
            tmp += lastS->left(markEndX);
        else
            tmp.truncate(tmp.length()-1);

        return tmp;
    }
}
#endif

#if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
bool ZGui::isSelectText()
{
    int markBeginX, markBeginY;
    int markEndX, markEndY;
    if ( !edit->getMarkedRegion( &markBeginY, &markBeginX, &markEndY, &markEndX ) )
    {
        return false;
    }
    return true;    
}
#endif

void ZGui::slot_about()
{
	ZAboutDialog* aboutDlg = new ZAboutDialog();
	aboutDlg->exec();
	delete aboutDlg;
	aboutDlg = NULL;
}

void ZGui::slot_settings()
{
	ZSettingsDlg* dlg = new ZSettingsDlg();
	dlg->exec();
	delete dlg;
	dlg = NULL;
}

void ZGui::slot_exit()
{
	if (cfg_autoOpen)
	{
		ZConfig cfg(ProgDir+"/zTextEdit.cfg");
		cfg.writeEntry(QString("LastFile"), QString("FileName"), sFileName);
		cfg.writeEntry(QString("LastFile"), QString("FilePath"), sFilePath);
		cfg.flush();		
	}
	qApp->quit();
}

void ZGui::slot_fileNew()
{
	if ( pos != NULL )
	{
		delete pos;
		pos = NULL;
	}
	isMarck = false;
	#if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
	isSelected = false;
	#endif
	sFileName = QString::null;
	sFilePath = QString::null;
	edit->clear();
}

void ZGui::slot_fileFind()
{
	ZFindDlg * dlg = new ZFindDlg(edit, this);
	dlg->exec();
}

void ZGui::slot_fileOpen()
{
	ZFileOpenDialog *zfod  = new ZFileOpenDialog();
	zfod->exec();
	if ( zfod->result() == 1 )
	{
		if ( zfod->getFileName() != "" )
		{
			if ( !edit->text().isEmpty() )
				slot_newDlg();
			slot_fileNew();
    		sFileName = getFileName(zfod->getFileName());
    		sFilePath = getFilePath(zfod->getFileName());
    		load(sFilePath+sFileName);
		}
	}
	delete zfod;
	zfod = NULL;
}

void ZGui::slot_fileSave()
{
	if ( sFileName.isEmpty() || sFilePath.isEmpty() )
	{
		slot_fileSaveAs();
	} else
	{
		saveAs( sFilePath+sFileName, true );
	}
}

void ZGui::slot_fileSaveAs()
{
	ZFileSaveDialog *zfsd;
	zfsd  = new ZFileSaveDialog( sFilePath.isEmpty()?"/mmc/mmca1":sFilePath, sFileName.isEmpty()?"file.txt":sFileName );
	zfsd->exec();
	
	if ( zfsd->result() == 1 )
	{
    	QString fName =  zfsd->getFileName();
    	toLog(QString("*** Save file: %1").arg(fName));
    	if ( !fName.isEmpty() ) 
    	{ 
			sFileName = zfsd->getFileName();
    		sFilePath = zfsd->getFilePath()+"/";  
			saveAs(sFilePath+sFileName);
		}
	} 
	delete zfsd;
	zfsd = NULL;
}

void ZGui::slot_Raise()
{
	this->show();
}

void ZGui::slot_ReturnToIdle( int )
{
	this->hide();
}

void ZGui::slot_minimize()
{
	this->hide();
}

QTextCodec* ZGui::codecByLocalId( int id )
{
	QTextCodec* codec;
	switch (id)
	{
		case 0:
			codec = QTextCodec::codecForName("utf8");
			break;		
		case 1:
			codec = QTextCodec::codecForName("CP1251");
			break;
		case 2:
			codec = QTextCodec::codecForName("KOI8-R");
			break;	
		case 3:
			codec = QTextCodec::codecForName("ISO8859-1");
			break;	
		case 4:
			codec = QTextCodec::codecForName("ISO8859-2");
			break;		
		case 5:
			codec = QTextCodec::codecForName("ISO8859-5");
			break;				
		case 6:
			codec = QTextCodec::codecForName("KOI8-U");
			break;						
		case 7:
			codec = QTextCodec::codecForName("Big5");
			break;				
		case 8:
			codec = QTextCodec::codecForName("GBK");
			break;				
		default:
			codec = QTextCodec::codecForName("CP1251");								
	}
	return codec;
}

#define InRange(c, lower, upper)  (((c) >= (lower)) && ((c) <= (upper)))
#define IsFirstByte(c)	(InRange((c), 0x81, 0xFE))
#define IsSecondByteRange1(c)	(InRange((c), 0x40, 0x7E))
#define IsSecondByteRange2(c)	(InRange((c), 0xA1, 0xFE))
#define IsSecondByte(c)	(IsSecondByteRange1(c) || IsSecondByteRange2(c))

int ZGui::big5HeuristicContentMatch(const char* chars, int len)
{
    int score = 0;
    int i=0;
    while (i<len)
    {
		uchar ch = chars[i];
		if ( !ch )
		    return -1;
		    
		if ( ch < 32 && ch != '\t' && ch != '\n' && ch != '\r' ) 
		{
		    if ( score )
				score--;
		} else 
		if ( ch < 0x80 ) 
		    score++;
		else 
		if ( IsFirstByte(ch) ) 
		{
	
		    if ( i < len-1 ) 
		    {
				uchar c2 = chars[++i];
				if ( !IsSecondByte(c2) )
			    	return -1;
				score += 2;
		    } else
		    	score++;
		} else 
		    return -1;
		i++;
    }
    return score;
}

int ZGui::checkCodec(char* chars, int len, int codeId)
{
	if ( codeId == 7 ) //if big5 codec
		return big5HeuristicContentMatch( chars, len );
	
    QTextCodec* codec = codecByLocalId(codeId);
    
    if ( !codec ) { printf("Error: Codec %d not found!!",codeId); return -1; };
    
    int col = codec->heuristicContentMatch(chars,len);
    
    if ( codeId > 0 )
    	if ( len != strlen(chars) )
    		if ( col )
    			col--;
    		
    return col;
}

int ZGui::detectCodec( char * chars, int maxLen )
{
	toLog("\t#Maxlen: "+QString::number(maxLen) + " strlen "+QString::number(strlen(chars)) );
	
	int ret[CODEC_COUNT];

	int id=0;

	for (int i=0;i<(cfg_chineseCodeDetect?CODEC_COUNT-1:CODEC_COUNT-2); i++) // CODEC_COUNT-1 - GBK not be detected
	{
		ret[i] = checkCodec( chars, strlen(chars), i );
		toLog("\t#CodecId: "+QString::number(i)+" res:"+QString::number(ret[i]));
		if ( ret[i]>ret[id] )
			id = i;
	}

	return id;
}

void ZGui::load ( const QString fileName, bool AutoCodec )
{
	toLog("load ("+fileName+")");
	QFile file ( fileName );
	if (  file.open ( IO_ReadWrite ) )//IO_ReadOnly ) )
	{
		//Block update
	    edit->blockSignals(true);
		edit->setAutoUpdate(false);	
			
		//Set def editor
		edit->clear();
		edit->setText("");
	
		//Detect codec
		if ( AutoCodec )
		{
			//Reset all checked
			for (int i=0; i<CODEC_COUNT;i++)
				CodeMenu->setItemChecked(i,false);
			//Read data for detect
			char data[10000];
			int size = file.readBlock(data, sizeof(data));
			file.reset();
			textCode = detectCodec(data, size);
			//Check codec
			CodeMenu->setItemChecked(textCode, true);
		}
		
		toLog("\tload text");
		//Load file
		char data[ file.size() ];
		file.readBlock(data, sizeof(data));
		QTextCodec* codec = codecByLocalId(textCode);
		toLog("\tset text");
		edit->setText( codec->toUnicode( data ) );
		toLog("\tclose file");
		file.close();
		
		//Unblock update
	    edit->blockSignals(false);
		edit->setAutoUpdate(true);
		
		#ifdef MDI
		setMainWidgetTitle(sFileName);
		buildDlgMenu();
		#endif
		
		toLog("end load");
	}
}

void ZGui::saveAs ( const QString fileName, bool save )
{ 
	if ( (access(fileName.utf8(),0) == 0) && !save )
	{
		QString sBody = lng->getString("REWRITE").arg ( getFileName(fileName) );
		
		ZMessageDlg * pConfirmation = new ZMessageDlg ( lng->getString("SAVING"), sBody, ( ZMessageDlg::MessageDlgType )1, 0, this, "2", true, 0 );
		if ( pConfirmation->exec() )
		{
			ZMessageDlg * pMessage = new ZMessageDlg ( lng->getString("SAVING"), lng->getString("CHANGED"), ( ZMessageDlg::MessageDlgType )1, 0, this, "saveas", true, 0 );
			pMessage->show();
			delete pMessage;
		}
		
		delete pConfirmation;
	}
	
	if ( !(access(getFilePath(fileName).utf8(),02) == 0) ) // Check save to ReadOnly FS
	{   
		ZMessageDlg * pWarning = new ZMessageDlg ( lng->getString("ERROR"), "Do not save to ReadOnly FS!", ( ZMessageDlg::MessageDlgType )2, 0, this, "saveas", true, 0 );
		pWarning->exec();
		delete pWarning;
		return;
	}
	
	if ( access(fileName.utf8(),0) == 0 ) //remove file for rewrite
		remove(fileName.utf8());
	
	QFile file ( fileName );
	
	if ( !file.open ( IO_WriteOnly | IO_Truncate ) )
	{   
		ZMessageDlg * pWarning = new ZMessageDlg ( lng->getString("ERROR"), lng->getString("FILE_SAVING_FAILED"), ( ZMessageDlg::MessageDlgType )2, 0, this, "saveas", true, 0 );
		pWarning->exec();
		delete pWarning;
		return;
	}
	
	QTextCodec* codec = codecByLocalId(textCode);	
	file.reset();
	QCString str = codec->fromUnicode( edit->text() );
	file.writeBlock( str, str.length() );
	char endFile[]={0};
	file.writeBlock( endFile, sizeof(endFile) );
	
	file.flush();
	file.close();
	
	ZMessageDlg * pMessage = new ZMessageDlg ( lng->getString("SAVING"), lng->getString("FILE_SAVING_SUCCESS"), ( ZMessageDlg::MessageDlgType ) 2, 0, this, "saveas", true, 0 );
	pMessage->exec();
	delete pMessage;
}

QString ZGui::getFilePath(const QString &AFileName)
{		
  QString str = AFileName;
  int i = str.findRev ( "/" );
  str.remove ( i+1, str.length() - i );
  return str;  
}

QString ZGui::getFileName(const QString &AFileName)
{
  QString str = AFileName;
  int i = str.findRev ( "/" );
  str.remove ( 0, i);
  if (str.left(1) = "/") str.remove ( 0, 1);
  return str;    
}

bool ZGui::eventFilter( QObject *target, QEvent *e ) //Event filter edit [ZMultiLineEdit]
{
	#define CURENT_EDITOR ((ZMultiLineEdit*)target)
	
	if (QEvent::KeyPress == e->type())
	{
		#if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
		if ( !isMarck && isSelected ) //Fix bag SelectAll
		{
			switch ( ((QKeyEvent*)e)->key() )
			{		
				case KEY_LEFT:
				case KEY_UP:      		
				case KEY_DOWN:      
				case KEY_RIGHT:	
					int iSelX = 0;
					int iSelY = 0;
					CURENT_EDITOR->getCursorPosition( &iSelX, &iSelY );
					CURENT_EDITOR->setSelection(0,0,0,0);
					isSelected = false;
					CURENT_EDITOR->setCursorPosition( iSelX, iSelY, false );	
					
			}	
		} else
		#endif
		
		if ( isMarck ) //Select whith move cursor
		{
			switch ( ((QKeyEvent*)e)->key() )
			{		
				case KEY_SIDE_UP:       CURENT_EDITOR->pageUp(isMarck);                 return true; break;
				case KEY_SIDE_DOWN:     CURENT_EDITOR->pageDown(isMarck);               return true; break;		
				case KEY_LEFT:      	CURENT_EDITOR->cursorLeft(isMarck,false,true);  return true; break;
				case KEY_UP:      		CURENT_EDITOR->cursorUp(isMarck,false);          return true; break;
				case KEY_DOWN:      	CURENT_EDITOR->cursorDown(isMarck,false);        return true; break;
				case KEY_RIGHT:
				{ 
					if ( ((QKeyEvent*)e)->isAutoRepeat() )  
						CURENT_EDITOR->cursorWordForward(isMarck);
					else 
						CURENT_EDITOR->cursorRight(isMarck,false,true);
					return true;	
					break; 
				}
			}
		} 
		
		switch ( ((QKeyEvent*)e)->key() )
		{
			#ifdef MDI
			case KEY_SIDE_SELECT:	slot_nextDlg();						return true; break;
			#endif
			case KEY_SIDE_UP:       CURENT_EDITOR->pageUp();            return true; break;
			case KEY_SIDE_DOWN:     CURENT_EDITOR->pageDown();          return true; break;			
			case KEY_GREEN:
				if (cfg_menuCopy)	
				{
					#if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
				    QPoint pos( 0, 0 );
				    int col=0, row=0;
				    CURENT_EDITOR->getCursorPosition( &row, &col );
				    QString line = CURENT_EDITOR->textLine( row );
				    QFontMetrics fm( CURENT_EDITOR->font() );
				    pos.setX( 3 + fm.width(line, col) );
				    pos.setY( row*CURENT_EDITOR->getLineHeight() + 3 );
				    pos = CURENT_EDITOR->mapToGlobal(pos);
					#else
					QPoint pos = CURENT_EDITOR->mapToGlobal(CURENT_EDITOR->cursorPoint());
					#endif
					EditMenu->setPosition(ZOptionsMenu::TopLeft, pos );
					EditMenu->popup();
				} else
				slot_editSelectBlock();
				return true; 
				break;
			case KEY_C:
			{
				if (pos != NULL)
				{
					delete pos;
					pos = NULL;
				}
				break;	
			}
			#ifdef SELECT_CUR_LINE
			case KEY_DOWN:
			case KEY_UP:
			{
				if ( cfg_selCurLine )
					CURENT_EDITOR->update();
				break;
			}
			#endif	
		}

	}
	#ifdef SELECT_CUR_LINE
	if ( cfg_selCurLine && e->type() == QEvent::Paint ) //Paint select line
	{
		CURENT_EDITOR->paintEvent( (QPaintEvent*)e );
		QPainter paint( CURENT_EDITOR );
		QPen pen( green, 1 );
		paint.setPen( pen );
		int y;
		#if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
	    int col=0, row=0;
	    CURENT_EDITOR->getCursorPosition( &row, &col );
	    y=(row+1)*CURENT_EDITOR->getLineHeight() + 3;
		#else
		y=CURENT_EDITOR->getLineHeight()+CURENT_EDITOR->cursorPoint().y();
		#endif
		paint.drawLine( 3, y, CURENT_EDITOR->width() - 6, y );
		
		return true;
	}
	#endif
	//Fix bag edit off, on down up, down, center
	if ( e->type() == QEvent::LeaveModalEdit )
		fixEditOff = true;
	if ( fixEditOff && ( QEvent::KeyRelease == e->type() ) )
	{
		CURENT_EDITOR->keyPressEvent( new QKeyEvent (QEvent::KeyPress, KEY_CENTER, 0, 0) );
		fixEditOff = false;
	}		
	if ( e->type() == QEvent::FocusIn )	
		fixEditOff = false;

	return false;
}

#ifdef MDI
void ZGui::slot_nextDlg()
{
	if ( countDlg == 1 ) return;
	
	if ( countDlg <= ++curDlg )
		curDlg = 0;
	
	if ( !zmeEditList[curDlg] ) return;

	wStack->raiseWidget(curDlg);
	zmeEditList[curDlg]->setFocus();
	
	setMainWidgetTitle(sFileName.isEmpty()?sDlgCap:sFileName);
	buildDlgMenu();
}

void ZGui::slot_newDlg()
{
	if ( countDlg >= MAX_DIALOG_COUNT )
		return;

	++curDlg;
	++countDlg;
    zmeEditList[curDlg] = new ZMultiLineEdit( this, false, 1, "ZMultiLineEdit"  );
    
	CHECK_PTR(zmeEditList[curDlg]);
	setSettingToEdit(zmeEditList[curDlg]);

	wStack->addWidget(zmeEditList[curDlg], curDlg);
	wStack->raiseWidget(curDlg);

	zmeEditList[curDlg]->setFocus();
	dlgCapList[curDlg]="New "+QString::number(curDlg);
	fileNameList[curDlg]="";
	textCodeList[curDlg]=0;
	
	setMainWidgetTitle(sFileName.isEmpty()?sDlgCap:sFileName);
	buildDlgMenu();
}

void ZGui::slot_dlgChenged(int n)
{
	if ( countDlg == 1 ) return;	
	
	if ( n<FIX_DLG_MENU_INDEX )
		return;
	
	curDlg = n-FIX_DLG_MENU_INDEX;

	if ( !zmeEditList[curDlg] ) return;

	wStack->raiseWidget(curDlg);

	zmeEditList[curDlg]->setFocus();
	
	setMainWidgetTitle(sFileName.isEmpty()?sDlgCap:sFileName);
	buildDlgMenu();
}

void ZGui::buildDlgMenu()
{
	DlgMenu->clear();
	QPixmap * pm = new QPixmap();
	pm->load(ProgDir+ "/img/document_add.png");
	DlgMenu->insertItem ( MENU_FIX+lng->getString("NEW_DLG"), NULL, pm, true, 0, 0 );
	pm->load(ProgDir+ "/img/document_del.png");
	DlgMenu->insertItem ( MENU_FIX+lng->getString("CLOSE_DLG"), NULL, pm, true, 1, 1 );
	pm->load(ProgDir+ "/img/fake.png");
	DlgMenu->insertItem ( MENU_FIX+lng->getString("NEXT_DLG"), NULL, pm, true, 2, 2 );
	
	#if !(defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W))
	DlgMenu->insertSeparator(3, 3); 
	#endif
	
	DlgMenu->connectItem ( 0, this, SLOT ( slot_newDlg() ) );
	DlgMenu->connectItem ( 1, this, SLOT ( slot_closeDlg() ) );	
	DlgMenu->connectItem ( 2, this, SLOT ( slot_nextDlg() ) );
	
	int i;
	for ( i=0;i<countDlg;i++ )
		#if !(defined(EZX_Z6) || defined(EZX_V8))
		DlgMenu->insertItem ( QString::number(i+1) + ": " + (fileNameList[i].isEmpty()?dlgCapList[i]:fileNameList[i]), NULL, NULL, true, FIX_DLG_MENU_INDEX+i, FIX_DLG_MENU_INDEX+i, false, true, i==curDlg );
		#else
		DlgMenu->insertItem ( QString::number(i+1) + ": " + (fileNameList[i].isEmpty()?dlgCapList[i]:fileNameList[i]), NULL, NULL, NULL, true, true, i==curDlg, FIX_DLG_MENU_INDEX+i, FIX_DLG_MENU_INDEX+i );
		#endif
	
	//Set codeck chek on menu
	for ( i=0;i<CODEC_COUNT;i++)
		CodeMenu->setItemChecked(i, false);
	CodeMenu->setItemChecked(textCode, true);
}

void ZGui::slot_closeDlg()
{
	if ( countDlg == 1 ) return;
	
	wStack->removeWidget(zmeEditList[curDlg]);
	zmeEditList[curDlg]->close(true);
	
	--countDlg;
	
	int i;
	for ( i=curDlg;i<countDlg;i++ )
	{
		zmeEditList[i]=zmeEditList[i+1];
		fileNameList[i]=fileNameList[i+1];
		filePathList[i]=filePathList[i+1];
		dlgCapList[i]=dlgCapList[i+1];
		wStack->removeWidget(zmeEditList[i+1]);
		wStack->addWidget(zmeEditList[i+1],i);
	}
	
	if ( curDlg>0 )
		--curDlg;
	
	wStack->raiseWidget(curDlg);
	
	slot_dlgChenged(FIX_DLG_MENU_INDEX+curDlg);
}
#endif
