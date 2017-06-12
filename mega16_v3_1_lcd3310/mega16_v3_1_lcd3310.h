// CLK (SCK)      <=> PB7
// DIN (MOSI)     <=> PB5
// D/C (LCD-D/C)  <=> PA6
// CS  (LCD-SCE)  <=> PA4
// RST (LCE-RES)  <=> PA5

#ifndef _MEGA16_V3_1_LCD3310_H_
#define _MEGA16_V3_1_LCD3310_H_

#define SET_SPI_CLK()        PORTB |= (1<<7)
#define CLR_SPI_CLK()        PORTB &= ~(1<<7)

#define SET_SPI_MOSI()       PORTB |= (1<<5)
#define CLR_SPI_MOSI()       PORTB &= ~(1<<5)

#define SET_LCD_DC()         PORTA |= (1<<6)
#define CLR_LCD_DC()         PORTA &= ~(1<<6)

#define SET_LCD_CS()         PORTA |= (1<<4)
#define CLR_LCD_CS()         PORTA &= ~(1<<4)

#define SET_LCD_RST()        PORTA |= (1<<5)
#define CLR_LCD_RST()        PORTA &= ~(1<<5)

//extern unsigned char tc_status;

void InitSpi(void);

void InitLcdDevices(void);

void DelayUs(unsigned int uSec);

/**********************************************************************
Function:		LcdWriteByte()	   
Description:	Write one Byte to LCD by SPI
Parameter:		unsigned char data	 : data you want to send
				unsigned char command: is command? no1/yes0
Return:			void
**********************************************************************/
void LcdWriteByte(unsigned char data, unsigned char command);

void LcdCls(void);

void LcdFull(void);

void LcdInit(void);

/**********************************************************************
Function:		LcdSetXY()	   
Description:	Set display coordinates
Parameter:		unsigned char X : 0 - 83
				unsigned char Y : 0 - 5
Return:			void
**********************************************************************/
void LcdSetXY(unsigned char X,unsigned char Y);

void LcdWriteChar(unsigned char c);

void LcdWriteInverseChar(unsigned char c);

void LcdWriteEnglishString(unsigned char X, unsigned char Y,unsigned char inverse, unsigned char *s);

void LcdWriteChineseString(unsigned char X, unsigned char y,
	 					   unsigned char *pstr, unsigned char ch_width);

#endif