#include <iom16v.h>
#include <macros.h>

#include "mega16_v3_1_ds18b20.h"

/******************************************************/
// Set the 1-Wire timing to 'standard' or 'overdrive'
// Adjust tick values depending on speed

// Standard Speed
const unsigned int  A = 6;
const unsigned int	B = 64;
const unsigned int  C = 60;
const unsigned int  D = 10;
const unsigned int  E = 9;
const unsigned int  F = 55;
const unsigned int  G = 0;
const unsigned int	H = 480;
const unsigned int	I = 70;
const unsigned int	J = 410;

// Overdrive Speed
/*
const unsigned char A = 1.5 ;
const unsigned char B = 7.5 ;
const unsigned char C = 7.5 ;
const unsigned char D = 2.5 ;
const unsigned char E = 0.75;
const unsigned char F = 7	;
const unsigned char G = 2.5 ;
const unsigned int	H = 70	;
const unsigned char I = 8.5 ;
const unsigned char J = 40	;
*/
/******************************************************/

// Pause for exactly ‘tick’ number of ticks = 3us 
// Implementation is platform specific 
void tickDelay(unsigned int tick)
{
	while (tick--){NOP();NOP();NOP();NOP();}
}


void Delay_ms(unsigned int mSec)
{
	int i;
	while (mSec--)
		for (i = 0; i<(187 * 2); i++);
}


unsigned char ds18b20Reset(void)
{
	unsigned char status;
	
	OUTPUT_DQ();
	
	SET_DQ();	  		
	
	tickDelay(G);
	
	CLR_DQ();	 		 // Bus master active low
	
	tickDelay(H);
	
	SET_DQ();	 		 // release BUS	
	
	INPUT_DQ();	
	
	tickDelay(I);
	
	status = READ_DQ();	 
	
	tickDelay(J);
	
	OUTPUT_DQ();
	
	SET_DQ();
	
	return status;	// Successful initialization returns 0
}


//-----------------------------------------------------------------------------
// Send a 1-Wire write byte. Provide 10us recovery time.
//
void ds18b20WriteByte(unsigned char byte)
{
	unsigned char i;

	for(i=0;i<8;i++)
	{		
		if(byte & (1<<i)) 
		{
			// write 1
			OUTPUT_DQ();
			CLR_DQ();		// Drives DQ low
			tickDelay(A);
			
			INPUT_DQ();
			SET_DQ();		// Releases the bus
			tickDelay(B);	// Complete the time slot and 10us recovery
		}
		else
		{
			 // write 0
			 OUTPUT_DQ();
			 CLR_DQ();
			 tickDelay(C);
			 
			 INPUT_DQ();
			 SET_DQ();
			 tickDelay(D);			 
		}
	}
}

unsigned char ds18b20ReadBit(void)
{
		unsigned char result;
		
		OUTPUT_DQ();
		CLR_DQ();
		tickDelay(A);
		
		INPUT_DQ();
		SET_DQ();
		tickDelay(E);
		
		result = READ_DQ();
		
		tickDelay(F);
		
		return result;
}

unsigned char ds18b20ReadByte(void)
{
	unsigned char i,result;
	for(i=0;i<8;i++)
	{
		result >>= 1;
		
		if(ds18b20ReadBit())
			result |= 0x80;
	}
	return result;
}

unsigned char InitDs18b20(void)
{
	if (ds18b20Reset() != 0x00) return 1; // initialize failed

	ds18b20WriteByte(DS18B20_SKIP_ROM);

	ds18b20WriteByte(DS18B20_WRITE_RAM);

	ds18b20WriteByte(0);				// TH

	ds18b20WriteByte(0);				// TL

	ds18b20WriteByte(0x1f);				// R1 = 0, RO = 0 ,Thermometer Resolution = 9bits
	// Max Conversion Time  < 100ms
	
	return 0;
}

unsigned char ds18b20ConvertTemp(unsigned char *temp)
{

	if (ds18b20Reset()!=0x00) return 1; // initialize failed

	ds18b20WriteByte(DS18B20_SKIP_ROM);

	ds18b20WriteByte(DS18B20_CONVERT_TEM);

	Delay_ms(100);

	if (ds18b20Reset()!=0x00) return 1; // initialize failed

	ds18b20WriteByte(DS18B20_SKIP_ROM);

	ds18b20WriteByte(DS18B20_READ_RAM);
	
	temp[0] = ds18b20ReadByte();			// Read the first byte is Temp LSB

	temp[1] = ds18b20ReadByte();			// Temp MSB
	
	return 0; // successfully
}

char GetTemperature(unsigned char *t)
{	
	char return_t;

	t[0] >>= 4;
	t[1] <<= 4;

	return_t = t[1] + t[0];
	
	return return_t;
	/*
	char ret;
	unsigned long val;
	unsigned int temp = (t[1] * 256) + t[0];
	unsigned char sflag = 0;

	if ((t[1] & 0xf8) == 0xf8)
	{
		sflag = 1;
		temp = ~temp;
		temp++;
	}
	temp &= 0x07ff;

	val = ((unsigned long)temp) * 625;
	val /= 10000;

	ret = (char)val;

	if (sflag)
		ret |= 0x80;
	
	return ret;
	*/
}

void TempToStr(char temp,unsigned char *s_t)
{

	if (temp >= 0)
	{	
		s_t[0] = temp % 100 / 10 + '0';
		s_t[1] = temp % 10 + '0';
		s_t[2] = ' ';
	}
	else
	{
		temp = ~temp;
		temp++;

		s_t[0] = '-';
		s_t[1] = temp % 100 / 10 + '0';
		s_t[2] = temp % 10 + '0';
	}

}




/*
unsigned char tmp[3];//保存温度字节
char tval;    //保存温度值

if((ds18b20ConvertTemp(tmp) & (1<<0)) == 0)//如果转换成功
    {
       tval=GetTemperature(tmp);//计算实际温度值
	   tmp//十进制显示温度值
      if(tval>=0)
        //to do...
		
      else
        //to do...
		
    }
*/
