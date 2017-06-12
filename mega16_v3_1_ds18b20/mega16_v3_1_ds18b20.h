#ifndef _MEGA16_V3_1_DS18B20_H_
#define _MEGA16_V3_1_DS18B20_H_

#define INPUT_DQ()		 DDRA &= ~(1 << 2)		
#define OUTPUT_DQ()		 DDRA |= (1 << 2)		
#define CLR_DQ()		 PORTA &= ~(1 << 2)		
#define SET_DQ()		 PORTA |= (1 << 2)		
#define READ_DQ()		 PINA & (1 << 2)		

#define DS18B20_READ_ROM			0x33
#define DS18B20_MATCH_ROM			0X55
#define DS18B20_SKIP_ROM			0XCC
#define DS18B20_SEARCH_ROM			0XF0
#define DS18B20_ALARM_SEARCH_ROM	0XEC

#define DS18B20_WRITE_RAM			0X4E
#define DS18B20_READ_RAM			0XBE
#define DS18B20_COPY_RAM			0X48 
#define DS18B20_CONVERT_TEM			0X44
#define DS18B20_EECALL_EEPROM		0XB8

#define DS18B20_READ_POWER_SUPPLY	0XB4

void tickDelay(unsigned int tick);

void Delay_ms(unsigned int mSec);

unsigned char InitDs18b20(void);

unsigned char ds18b20Reset(void);

void ds18b20WriteByte(unsigned char byte);

unsigned char ds18b20ReadBit(void);

unsigned char ds18b20ReadByte(void);

unsigned char ds18b20ConvertTemp(unsigned char *temp);

char GetTemperature(unsigned char *t);

void TempToStr(char temp,unsigned char *s_t);

#endif