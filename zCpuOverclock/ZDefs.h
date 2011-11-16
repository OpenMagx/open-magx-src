#ifndef ZDEFS_H
#define ZDEFS_H

#define AM_STATE_SERVER_CHANNEL     "/AM/State/Server"

#define MEDIAPLAYER_BUSY 38
#define MEDIAPLAYER_NOT_BUSY 39

#define SYSTEM_CHANNEL "EZX/System"
#define PHONE_IDLE_STATUS_TEXT_CHANNEL "/phone/idle/statustext/chn"

#define SLIDER_OPENED "sliderOpened"
#define SLIDER_CLOSED "sliderClosed"

#ifndef EZX_E8
#define LCD_ON "LCDOn"
#define LCD_PRE_OFF ""
#else
#define LCD_ON "DPL_BKLGT_RESTORED"
#define LCD_PRE_OFF "DPL_BKLGT_DIMMED"
#endif

#define LCD_OFF "LCDOff"

#define KEY_LOCK "KEYPADLOCKED"

#define CPU_CONFIG "/ezxlocal/download/appwrite/setup/pe_zCpuOverclock.cfg"

#endif
