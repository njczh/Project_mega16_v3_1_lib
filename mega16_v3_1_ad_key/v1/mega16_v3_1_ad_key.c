#include <iom16v.h>
#include <macros.h>

#include "mega16_v3_1_ad_key.h"

#define  key_state_0 0
#define  key_state_1 1
#define  key_state_2 2
#define  key_state_3 3

void InitAdKeyDevices(void)
{
	/******** port_init ********/
	PORTA &= ~(1 << 7);
	DDRA &= ~(1 << 7);

	/******** adc_init ********/
	ADMUX |= (1 << REFS0) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0);
	ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS0);
}

unsigned int GetAdData(void)
{
	unsigned int adc_data; //,adc_v;

	ADCSRA |= (1 << ADSC);
	while (!(ADCSRA & (1 << ADIF)));
	ADCSRA |= (1 << ADIF);

	adc_data = ADCL;           	   		 	// Read 8 low bits first (important)
	adc_data |= (unsigned int)ADCH << 8;  	// read 2 high bits and shift into top byte

	return adc_data;

	//adc_v = (unsigned long)adc_data * 3300 / 1024;
	//return adc_v ;
}

unsigned char GetAdKey(void)
{
	unsigned char key_value;
	unsigned int adc_data;

	adc_data = GetAdData();

	if (adc_data <= 127)      { key_value = 1; } 		// right
	else if (adc_data <= 332) { key_value = 2; }	// down
	else if (adc_data <= 460) { key_value = 4; } 	// left
	else if (adc_data <= 548) { key_value = 3; } 	// up
	else if (adc_data <= 612) { key_value = 6; } 	// confirm
	else if (adc_data <= 700) { key_value = 5; } 	// cancel
	else { key_value = 0; }

	return key_value;
}

unsigned char ReadAdKey(void)
{
	static unsigned char key_state = 0, key_value, key_time = 0;
	unsigned char key_return = 0;

	switch (key_state)
	{
	case key_state_0:
		key_value = GetAdKey();
		if (key_value)
			key_state = key_state_1;
		break;

	case key_state_1:
		if (key_value == GetAdKey())
		{
			key_state = key_state_2;
			key_time = 0;
		}
		else
			key_state = key_state_0;
		break;

	case key_state_2:
		if (!GetAdKey()) // release
		{
			switch (key_value)
			{
			case 1:key_return = 1; break;
			case 2:key_return = 2; break;
			case 3:key_return = 3; break;
			case 4:key_return = 4; break;
			case 5:key_return = 5; break;
			case 6:key_return = 6; break;
			}
			key_state = key_state_0;
		}
		else if (++key_time >= 100)
		{
			key_state = key_state_3;
				key_time = 0;
			switch (key_value)
			{
			case 1:key_return = 1; break;
			case 2:key_return = 2; break;
			case 3:key_return = 3; break;
			case 4:key_return = 4; break;
			case 5:key_return = 5; break;
			case 6:key_return = 6; break;
			}
		}
		break;

	case key_state_3:
		if (!GetAdKey()) key_state = key_state_0;
		else
		{
			if (++key_time >= 5)
			{
				key_time = 0;
				switch (key_value)
				{
				case 1:key_return = 1; break;
				case 2:key_return = 2; break;
				case 3:key_return = 3; break;
				case 4:key_return = 4; break;
				case 5:key_return = 5; break;
				case 6:key_return = 6; break;
				}
			}
		}
		break;
	}

	return key_return;
}