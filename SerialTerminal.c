#include "SerialTerminal.h"

void SerialTerminalBegin(unsigned int ubrr)
{
	/*Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1 << UDRE0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (3<<UCSZ00);
	SerialTerminalPrint('\r');
	}
	void SerialTerminalPrint(unsigned char data)
	{
		/* Wait for empty transmit buffer */
		//while (!(UCSR0A & (1<<UDRE0)));
		/* Put data into buffer, sends the data */
		UDR0 = data;
	}
	unsigned char SerialTerminalRead(void)
	{
		/* Wait for data to be received */
		//while (!(UCSR0A & (1<<RXC0)));
		/* Get and return received data from buffer */
		return UDR0;
	}
	void SerialTerminalSetBuffer(uint8_t numberOfBits){
		SerialDataindex = 0;
		totalDataSize = 0;
		bufferText = calloc(numberOfBits,sizeof(uint8_t));
	}
	void SerialTerminalAddToBuffer(char data){
		bufferText[SerialDataindex+1]=data;
		SerialDataindex++;
		totalDataSize++;
	}

