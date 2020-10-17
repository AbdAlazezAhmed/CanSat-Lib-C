/*
 * GccApplication1.c
 *
 * Created: 7/4/2020 9:17:40 AM
 * Author : mizo
 */ 

#include <avr/interrupt.h>
#include <ctype.h>
#include "DHT.h"
#include "SerialTerminal.h"
void setup_Timer1(void);
DHT dht;
uint8_t pv;
int main(void)
{
	initDHT(&dht,0b00100011);//pin2D
	SerialTerminalBegin(MYUBRR);
	SerialTerminalSetBuffer(10);
	setup_Timer1();
	sei();
	
	
	
    /* Replace with your application code */
    while (1) 
    {
			asm("nop");
    }
}
ISR(TIMER1_OVF_vect){
	//read from DHC
	if (DHTPHASE==DHTPHASEPOWER)
		readDHT(&dht);
}
ISR(TIMER1_COMPB_vect){
	if (DHTPHASE==DHTPHASE18MS)
	{
		SerialTerminalAddToBuffer('1');
		SerialTerminalAddToBuffer('9');
		SerialTerminalAddToBuffer('4');
		SerialTerminalAddToBuffer('2');
		SerialTerminalAddToBuffer('0');
		SerialTerminalAddToBuffer('\r');
		
		readDHTPhase2(&dht);
	}else if (DHTPHASE == DHTPHASE40US){
		readDHTPhase3(&dht);
	}
	
}
ISR(USART_UDRE_vect)
{			
	if (SerialDataindex>0)
	{
		SerialTerminalPrint(bufferText[totalDataSize-SerialDataindex+1]);
		SerialDataindex--;
	}else{
		totalDataSize=0;
	}
				
		
			
			DDRB=0b11111111;
			PORTB^=0b11111111;
}
ISR(PCINT0_vect)
{
	if (getDHTPCIVEC(&dht)&PCI0VEC);
}
ISR(PCINT1_vect)
{
	if (getDHTPCIVEC(&dht)&PCI1VEC);
}
ISR(PCINT2_vect)
{
	if (getDHTPCIVEC(&dht)&PCI1VEC);

}

void setup_Timer1(void){
	TIMSK1 |=0b00000001;//enables interrupt 1 Overflow
	TCNT1 =0;
	TCCR1A =0b00000000;
	TCCR1B =0b00000100; //CS12
}


