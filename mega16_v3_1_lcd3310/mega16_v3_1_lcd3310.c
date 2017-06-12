#include <iom16v.h>
#include <macros.h>

#include "mega16_v3_1_lcd3310.h"
#include "english6x8Pixel.h"

// SPI initialize
// clock rate: 1843199hz
void InitSpi(void)
{
 SPCR = 0x50; //setup SPI
 SPSR = 0x00; //setup SPI
}

void InitLcdDevices(void)
{

 PORTA &= ~((1<<6)|(1<<5)|(1<<4));
 DDRA |= (1<<6)|(1<<5)|(1<<4);
 PORTB &= ~((1<<7)|(1<<5)|(1<<4));
 DDRB  |= (1<<7)|(1<<5)|(1<<4);

 InitSpi();
 
 LcdInit();
 
}

void DelayUs(unsigned int uSec)
{
	while (uSec--){
		NOP();NOP();NOP();NOP();
	}
}

void LcdWriteByte(unsigned char data, unsigned char command)
{
	CLR_LCD_CS();					// enable LCD

	if (command == 0)
		CLR_LCD_DC();				// data is a command
	else
		SET_LCD_DC();       		// data is just a data

	SPDR = data;          			// send  data
	while ((SPSR & 0x80) == 0);		// waiting for transmission to complete

	SET_LCD_CS();           		// close LCD
}


void LcdCls(void)
{
	unsigned int i;

	LcdWriteByte(0x0c, 0);
	LcdWriteByte(0x80, 0);

	for (i = 0; i < 504; i++)
		LcdWriteByte(0x00, 1);
}

void LcdFull(void)
{
	unsigned int i;

	LcdWriteByte(0x0c, 0);
	LcdWriteByte(0x80, 0);

	for (i = 0; i < 504; i++)
		LcdWriteByte(0xff, 1);
}

void LcdInit(void)
{
	CLR_LCD_RST();
	DelayUs(10);
	SET_LCD_RST();

	CLR_LCD_CS();			// close LCD
	DelayUs(10);

	LcdWriteByte(0x21, 0);	// use extended instruction set
	LcdWriteByte(0xc8, 0);	// set Bias System
	LcdWriteByte(0x07, 0);	// set Temperature Coefficient
	LcdWriteByte(0x13, 0);	// 1:48
	LcdWriteByte(0x20, 0);	// use basic instruction set
	LcdWriteByte(0x0c, 0);	// display mode : normal
	LcdCls();
	
	SET_LCD_CS();			// enable LCD
	
}

void LcdSetXY(unsigned char X, unsigned char Y)
{
	LcdWriteByte(0x40 | Y, 0);		  	// column
	LcdWriteByte(0x80 | X, 0);          // row
}

void LcdWriteChar(unsigned char c)
{
	unsigned char line;

	c -= 32;

	for (line = 0; line<6; line++)
		LcdWriteByte(font6x8[c][line], 1);
}

void LcdWriteInverseChar(unsigned char c)
{
	unsigned char line;

	c -= 32;

	for (line = 0; line<6; line++)
		LcdWriteByte(~font6x8[c][line], 1);
}

void LcdWriteEnglishString(unsigned char X, unsigned char Y, unsigned char inverse ,unsigned char *s)
{
	LcdSetXY(X, Y);
	
	if(inverse)
	{
		while (*s)
		{
			LcdWriteInverseChar(*s);
			s++;
		}
	}
	else
	{
		while (*s)
		{
			LcdWriteChar(*s);
			s++;
		}
	}
}

void LcdWriteChineseString(unsigned char X, unsigned char y,
	 					   unsigned char *pstr, unsigned char ch_width)
{


}
