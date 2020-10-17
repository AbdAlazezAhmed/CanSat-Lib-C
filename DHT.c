#include "DHT.h"
void initDHT( DHT *dht_ptr,uint8_t pin){
	dht_ptr->pin=pin;
	DHTPHASE = DHTPHASEPOWER;
}
void readDHT( DHT *dht_ptr){
	
	*DHTDDR |=1<<(dht_ptr->pin&DHTPINNUMMASK);//sets the pin to OUTPUT
	*DHTPORT &= ~1<<(dht_ptr->pin&DHTPINNUMMASK);
	set_Timer1B(1124+1);//delay 18ms
	DHTPHASE = DHTPHASE18MS;
}
void set_Timer1B(uint16_t time){
	OCR1B =TCNT1+time;//the code repeats every 18 milliseconds.
	TIMSK1 |=0b00000100;//enables interrupt 1B
}
void readDHTPhase2( DHT *dht_ptr){
	DDRD |=0b00000010; 
	*DHTPORT |= 1<<(dht_ptr->pin&DHTPINNUMMASK);//makes the pin high
	set_Timer1B(2);//delay 80us
	DHTPHASE = DHTPHASE40US;

	
}
void readDHTPhase3( DHT *dht_ptr){
	*DHTPORT &= ~1<<(dht_ptr->pin&DHTPINNUMMASK);

	*DHTDDR &= ~1<<(dht_ptr->pin&DHTPINNUMMASK);//sets the pin to INPUT
	

	
	// Enable pin change interrupt using the Pin Change Interrrupt Control Register (PCICR)
	
	PCICR |= 1<<DHTPCIE;
	
	*DHTPCMSK |= 1<<(dht_ptr->pin&DHTPINNUMMASK);

	DHTPHASE = DHTPHASEPOWER;

}
uint8_t getDHTPCIVEC(DHT *dht_ptr){
	return DHTPCIVEC;
}

