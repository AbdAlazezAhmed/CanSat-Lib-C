/*
 * GccApplication2.c
 *
 * Created: 11/22/2020 2:27:43 PM
 * Author : mizo
 */ 

#include <avr/io.h>
#include "UART/Interface/UART.h"
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include "I2C/Devices/BMP180/BMP180.h"
int main(void)
{
	initUART();
	initMPU();
	BMP180 bmp180;
	char buffer[20], float_[10];
	initBMP180(&bmp180);
    /* Replace with your application code */
    while (1) 
    {			
		readBMP180(&bmp180);
		dtostrf( bmp180.ctemp, 3, 2, float_ );
		sprintf(buffer," T = %s%cC",float_,0xF8);           /* 0xF8 Ascii value of degree '°' on serial */
		sendStringUART(buffer);
	

    }
}

