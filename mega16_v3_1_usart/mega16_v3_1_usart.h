//ICC-AVR application builder : 2017/5/30 16:10:04
// Target : M16
// Crystal: 7.3728Mhz

#include <iom16v.h>
#include <macros.h>

#define BAUD 9600
#define CRYSTAL 7372800

#define BAUD_SETTING (unsigned int)((unsigned long)CRYSTAL/(16*(unsigned long)BAUD) -1)
#define BAUD_H (unsigned char)(BAUD_SETTING >> 8)
#define BAUD_L (unsigned char)(BAUD_SETTING)

/* USART */
#define UBRRHI	(*(volatile unsigned char *)0x40)
#define UBRRH	(*(volatile unsigned char *)0x40)
#define  URSEL    7
#define UBRR	(*(volatile unsigned char *)0x29)
#define UBRRL	(*(volatile unsigned char *)0x29)
#define UCSRC	(*(volatile unsigned char *)0x40)
#define  URSEL    7
#define  UMSEL    6
#define  UPM1     5
#define  UPM0     4
#define  USBS     3
#define  UCSZ1    2
#define  UCSZ0    1
#define  UCPOL    0
#define UCSRB	(*(volatile unsigned char *)0x2A)
#define  RXCIE    7
#define  TXCIE    6
#define  UDRIE    5
#define  RXEN     4
#define  TXEN     3
#define  UCSZ2    2
#define  RXB8     1
#define  TXB8     0
#define UCSRA	(*(volatile unsigned char *)0x2B)
#define  RXC      7
#define  TXC      6
#define  UDRE     5
#define  FE       4
#define  DOR      3
#define  OVR      3    /*This definition differs from the databook*/
#define  PE       2
#define  U2X      1
#define  MPCM     0
#define UDR	(*(volatile unsigned char *)0x2C)

void InitUsart(void);

void UsartTransmit(unsigned char data);

void UsarTransmit9bit(unsigned int data);

unsigned char UsartReceive(void);