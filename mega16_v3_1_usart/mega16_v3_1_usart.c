#include "mega16_v3_1_usart.h"

void InitUsart(void)
{

	PORTD = 0x03;
	DDRD = 0x02;

	UCSRA = 0x00;
	
	/**** Enable RX and TX ****/
	
	UCSRB = (1<<RXEN)|(1<<TXEN);
	
	/**** Set frame format ****/
	
	UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);	
	
	
	/**** Set baud ****/
	
	UCSRC &= ~(1<<URSEL);	//Write UBRRH	
	
	UBRRH = (unsigned char)BAUD_H;
	
	UBRRL = (unsigned char)BAUD_L;
	
}

void UsartTransmit(unsigned char data)
{
	/**** Wait for send buffer empty (Polling) ****/
	
	while(!(UCSRA & (1<<UDRE)));
	
	/**** Put data into the buffer and send data ****/
	
	UDR = data;
}

void UsarTransmit9bit(unsigned int data)
{
	/**** Wait for send buffer empty (Polling) ****/
	
	while(!(UCSRA & (1<<UDRE)));
	
	/**** Copy 9th bit to TXB8 ****/
	
	UCSRB &= ~(1<<TXB8);	// clr MSB 
	
	if( data & 0x0100 )
		UCSRB |= (1<<TXB8);
		
	/**** Put data into the buffer and send data ****/

	UDR = data;
}

unsigned char UsartReceive(void)
{
	/**** Wait for data to be received ****/
	
	while (!(UCSRA & (1<<RXC)));
	
	/**** Get and return received data from buffer */
	
	return UDR;
}