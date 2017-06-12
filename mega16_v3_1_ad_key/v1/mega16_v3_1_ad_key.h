#ifndef _MEGA16_V3_1_AD_KEY_
#define _MEGA16_V3_1_AD_KEY_

# define NO_ACTION 0

# define UP        3

# define DOWN      2

# define LEFT	   4

# define RIGHT	   1

# define ENTER     6

# define ESC       5

void InitAdKeyDevices(void);

unsigned int GetAdData(void);

unsigned char GetAdKey(void);

unsigned char ReadAdKey(void);

#endif