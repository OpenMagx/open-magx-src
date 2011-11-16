//
// Poject name: zAudio
//
// Version: 0.1
//
// Description: Programm for change audio settings
//
// Author: Ant-ON <prozanton@gmail.com>, (C) 2010
//

#ifndef GAIN_DEF_H
#define GAIN_DEF_H

#define GAIN_PATH "/ezxlocal/ap_gain.bin"
#define GAIN_PATH_ORG "/usr/bin/ap_gain.bin"

//######################################################################

#define VOLUME_TABLE

#define GAIN_DEVICES_START   (int)0x40 

#define GAIN_DEVICE_LEN      (int)0x0F
#define GAIN_DEVICE_COUNT    (int)0x04

#define GAIN_DEVICE_ITEM_LEN (int)0x01
#define GAIN_DEVICE_ITEM_POS (int)0x00

#define GAIN_DEVICE_VOL_MAX  (int)0x0F //MAX - 0x0F, maybe can set larger??
#define GAIN_DEVICE_VOL_MIN  (int)0x00
#define GAIN_DEVICE_VOL_ZERO (int)0x08

//######################################################################

#if defined(EZX_ZN5)||defined(EZX_EM30)||defined(EZX_E8)
#define GAIN_EQUALASER_START_1 (int)0x1AFE
#define GAIN_EQUALASER_START_2 (int)0x1BB4
#elif defined(EZX_VE66)
#define GAIN_EQUALASER_START_1 (int)0x1458
#define GAIN_EQUALASER_START_2 (int)0x150E
#elif defined(EZX_Z6)
#define GAIN_EQUALASER_START_1 (int)0x1A9A
#define GAIN_EQUALASER_START_2 (int)0x1B46
#endif

#define GAIN_EQUALASER_LEN   (int)0x0A
#define GAIN_EQUALASER_COUNT (int)0x12

#define GAIN_EQUALASER_ITEM_LEN (int)0x02
#define GAIN_EQUALASER_ITEM_COUNT (int)0x05

#define GAIN_EQUALASER_MAX   (int)0x7FFF
#define GAIN_EQUALASER_MIN   (int)0x0800

//######################################################################

#endif
