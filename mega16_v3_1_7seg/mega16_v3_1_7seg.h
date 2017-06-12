#ifndef	_MEGA16_V3_1_7SEG_H_
#define	_MEGA16_V3_1_7SEG_H_

#define CLR_SHCLK()  		PORTB&=~(1<<1)		  
#define SET_SHCLK()  		PORTB|=(1<<1)		  

#define CLR_STCLK()  		PORTB&=~(1<<0)		  
#define SET_STCLK()  		PORTB|=(1<<0)		  

#define CLR_DS()			PORTA&=~(1<<0)		  
#define SET_DS()			PORTA|=(1<<0)		  

const unsigned char led_7[] = { 0xc0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,
0x80,0x90,0xff,0x7f,0xc6,0x00 };

unsigned int disp_buff[4];
unsigned char posit = 0;
unsigned char DP_flag = 0;

void InitSegDevices(void)
{
	PORTD |= 0xf0;
	DDRD |= 0xf0;
	PORTB &= ~((1<<1)|(1<<0));
	DDRB |= (1<<1)|(1<<0);
	PORTA &= ~(1<<0);
	DDRA |= (1<<0);
}

void num_to_dispbuff(unsigned int num)
{
	disp_buff[0] = num / 1000;
	disp_buff[1] = num % 1000 / 100;
	disp_buff[2] = num % 100 / 10;
	disp_buff[3] = num % 10;
}

void HC595_send_byte(unsigned char SndData)
{

	unsigned char i;

	for (i = 0; i<8; i++)
	{
		/* if the current the bit need to determine is 0,we can get 0,otherwise get a non-zero value */
		if (SndData & (1 << (7 - i)))
			SET_DS();					// set 1
		else
			CLR_DS();					// set 0
		CLR_SHCLK();
		SET_SHCLK();
	}
	CLR_STCLK();
	SET_STCLK();
	
}


void Disp_1_digit(unsigned char posit, unsigned char DP_flag)
{
	PORTD |= 0xF0;								// in order not to affect the next choice

	if (DP_flag && (posit == 1))
		HC595_send_byte(led_7[disp_buff[posit]] & 0x7f);	// display DP
	else
		HC595_send_byte(led_7[disp_buff[posit]]);

	PORTD &= ~(1 << (7 - posit));					// 0 is selected,and set the other bits to 1
													//Delay_ms(1);								// to prevent flicker too fast
}



#endif
