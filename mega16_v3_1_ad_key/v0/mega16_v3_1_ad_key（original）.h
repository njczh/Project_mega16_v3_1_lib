#ifndef _MEGA16_V3_1_AD_KEY_
#define _MEGA16_V3_1_AD_KEY_

#include <iom16v.h>
#include <macros.h>

void InitAdKeyDevices(void);

unsigned int GetAdData(void);

unsigned char GetAdKey(void);

unsigned char ReadAdKey(void);

#endif