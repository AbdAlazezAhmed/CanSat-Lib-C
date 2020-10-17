#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#define DHTB 0b10000000
#define DHTC 0b01000000
#define DHTD 0b00100000
#define DHTPINNUMMASK 0b00011111
#define DHTPHASEPOWER 0b10000000
#define DHTPHASE18MS 0b01000000
#define DHTPHASE40US 0b11000000
#define DHTPHASEMASK 0b00111111
#define PCI0VEC 0b00000001
#define PCI1VEC 0b00000010
#define PCI2VEC 0b00000100
#define DHTDDR 	(uint8_t*)(dht_ptr->pin&DHTB?&DDRB:dht_ptr->pin&DHTC?&DDRC:&DDRD)
#define DHTPORT (uint8_t*)(dht_ptr->pin&DHTB?&PORTB:dht_ptr->pin&DHTC?&PORTC:&PORTD)
#define DHTPIN 	(uint8_t*)(dht_ptr->pin&DHTB?&PINB:dht_ptr->pin&DHTC?&PINC:&PIND)
#define DHTPCMSK 	(uint8_t*)(dht_ptr->pin&DHTB?&PCMSK0:dht_ptr->pin&DHTC?&PCMSK1:&PCMSK2)
#define DHTPCIE 	(uint8_t)(dht_ptr->pin&DHTB?PCIE0:dht_ptr->pin&DHTC?PCIE1:PCIE2)
#define DHTPCIVEC   dht_ptr->pin&DHTB?PCI0VEC:dht_ptr->pin&DHTC?PCI0VEC:PCI0VEC

uint8_t DHTPHASE;
typedef struct DHT_STRUCT {
	uint8_t temp[2];
	uint8_t humidity[2];
	uint8_t checksum;
	uint8_t pin;//last 3 bits decide the port, first 5 bits represent the pin number
}DHT;
void initDHT( DHT *dht_ptr,uint8_t pin);
void readDHT( DHT *dht_ptr);
void readDHTPhase2( DHT *dht_ptr);
void readDHTPhase3( DHT *dht_ptr);
void set_Timer1B(uint16_t time);
uint8_t getDHTPCIVEC(DHT *dht_ptr);