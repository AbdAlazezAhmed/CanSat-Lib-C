#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#define FOSC 16000000 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1
char *bufferText,SerialDataindex,totalDataSize;
void SerialTerminalBegin(unsigned int ubrr);
void SerialTerminalPrint(unsigned char data);
void SerialTerminalSetBuffer(uint8_t numberOfBits);
void SerialTerminalAddToBuffer(char data);
unsigned char SerialTerminalRead(void);
