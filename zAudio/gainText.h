//
// Poject name: zAudio
//
// Version: 0.1
//
// Description: Programm for change audio settings
//
// Author: Ant-ON <prozanton@gmail.com>, (C) 2010
//

#ifndef GAIN_TEXT_H
#define GAIN_TEXT_H

#include "gainDef.h"

const char * paramList[GAIN_DEVICE_LEN][6] =
{
	{"Handset", "TXT_RID_SETTING_B_PHONE","","","","",},
	{"Mono handset","TXT_RID_OPTION_HEADSET"," (","","3.5mm",")",},
	{"Stereo handset","TXT_RID_SETTING_A_STEREO_HEADSET"," (","","3.5mm",")",},
	{"Speakerphone", "TXT_RID_SETTING_A_LOUDSPEAKER","","","","",},
	{"Headset","TXT_RID_OPTION_HEADSET"," (","", "mUSB",")",},
	{"???","","","","","",},
	{"???","","","","","",},
	{"???","","","","","",},
	{"???","","","","","",},
	{"Stereo headset","TXT_RID_SETTING_A_STEREO_HEADSET"," (","","TTY",")",},
	{"Stereo headset","TXT_RID_SETTING_A_STEREO_HEADSET"," (","","mUSB",")",},
	{"Handset","TXT_RID_SETTING_B_PHONE"," (","TXT_RID_SETTING_A_SLIDE_CLOSED", "slide cloused",")",},
	{"Vibrator","TXT_RID_CLI_STANDARD_VIBRATE","","","","",},
	{"Headset","TXT_RID_OPTION_HEADSET"," (","","no mic, 3.5mm",")",},
	{"Speakerphone","TXT_RID_SETTING_A_LOUDSPEAKER"," (","TXT_RID_SETTING_A_SLIDE_CLOSED","slide cloused",")",},		
};

#if defined(EZX_VE66) || defined(EZX_Z6)
bool hideList[GAIN_DEVICE_LEN] = { 0,1,1,0,0,1,1,1,1,1,0,0,1,1,0 };	
#elif defined(EZX_EM30) || defined(EZX_E8)
bool hideList[GAIN_DEVICE_LEN] = { 0,0,0,0,0,1,1,1,1,1,0,1,0,0,1 };	
#elif defined(EZX_ZN5)
bool hideList[GAIN_DEVICE_LEN] = { 0,0,0,0,0,1,1,1,1,1,0,1,1,0,1 };	
#else
bool hideList[GAIN_DEVICE_LEN] = { 0,1,1,0,0,1,1,1,1,1,0,1,1,1,1 };	
#endif

//bool hideList[GAIN_DEVICE_LEN] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

const char * eqList[GAIN_EQUALASER_COUNT][2] =  
{
   {"TXT_RID_LIST_A_BASS_BOOST", "Bass Boost"}, 
   {"TXT_RID_SETTING_B_SPOKEN_WORD_BOOK", "Spoken Word"},
   {"TXT_RID_SETTING_B_CLASSICAL", "Classical"},
   {"TXT_RID_SETTING_B_COUNTRY_MUSIC", "Country"},
   {"TXT_RID_SETTING_B_DANCE", "Dance"},
   {"TXT_RID_SETTING_B_TECHNO", "Techno"},
   {"TXT_RID_SETTING_B_HIP_HOP_RAP", "HipHop"},
   {"TXT_RID_SETTING_B_LATIN", "Latin"},
   {"TXT_RID_SETTING_B_OLDIES", "Oldies"}, 
   {"TXT_RID_SETTING_B_POP", "Pop"},
   {"TXT_RID_SETTING_B_R_AND_B_SOUL", "RBSoul"},
   {"TXT_RID_SETTING_B_REGGAE", "Reggae"}, 
   {"TXT_RID_SETTING_B_ROCK", "Rock"},
   {"TXT_RID_SETTING_B_SMALL_SPEAKER", "Small Speaker"},
   {"TXT_RID_SETTING_B_TREBLE_BOOST", "Treble Boost"}, 
   {"TXT_RID_SETTING_B_VOCAL_BOOST", "Vocal Booster"},
   {"TXT_RID_SETTING_B_VOCAL_REDUCER", "Vocal Reducer"},
   {"TXT_RID_SETTING_B_JAZZ_BLUES", "Jazz Blues"} 
};

char eqHzList[GAIN_EQUALASER_ITEM_COUNT][9] = 
{
	"800Hz",
	"1600Hz",
	"3150Hz",
	"6300Hz",
	"12500Hz",
};

bool hideEqList[GAIN_EQUALASER_COUNT] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };	
#endif
