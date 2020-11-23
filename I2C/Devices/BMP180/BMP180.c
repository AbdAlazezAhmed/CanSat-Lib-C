/*
 * BMP180.c
 *
 * Created: 11/23/2020 11:07:51 AM
 *  Author: mizo
 */ 
#include "BMP180.h"
uint8_t initBMP180(BMP180 *bmp180){
	//allocate cooficients
	(*bmp180).coof = malloc(11*sizeof(uint16_t));
	for (int i = 0; i < 11; i++){
		//start communication with BMP180
		startI2C(BMP180_ADDR_w);
		//send target register (for coof)
		writeI2C((170 + (2 * i)));
		//send stop signal
		stopI2C();
		
		//start communication with BMP180
		startI2C(BMP180_ADDR_r);
		//read into coof
		(*bmp180).coof[i] = (readI2C(ACK) << 8) + readI2C(NACK);
		//send stop signal
		stopI2C();
		//delay said in data sheet to be 50ms
		_delay_ms(50);
		//checksum
		if (((*bmp180).coof[i] > 32767) && (i != 3) && (i != 4) && (i != 5))
		{
			(*bmp180).coof[i] -= 65536;
		}
	}
	//delay 300ms
	_delay_ms(300);
	//init successful
	return INIT_COMPLETE;
}
uint8_t readBMP180(BMP180 *bmp180){
	//temporary data var
	uint8_t data[3];
	//start communicating with BMP180
	startI2C(BMP180_ADDR_w);
	//select measurement control register
	writeI2C(BMP180_REG_CONTROL);     
	//enable temperature measurement
	writeI2C(BMP180_COMMAND_TEMPERATURE); 
	//send stop signal                
	stopI2C();
	//delay 100ms
	_delay_ms(100);

	//start communication with MBP180
	startI2C(BMP180_ADDR_w);
	//select data register
	writeI2C(BMP180_REG_RESULT); 
	//send stop signal
	stopI2C();

	//start communication with BMP180
	startI2C(BMP180_ADDR_r);
	//start reading temprature
	float temp = ((readI2C(ACK) <<8) + readI2C(NACK));
	//send stop signal
	stopI2C();

	//start communication with BMP180
	startI2C(BMP180_ADDR_w);
	//select measurement control register
	writeI2C(BMP180_REG_CONTROL); 
	//enable pressure measurement, OSS = 1
	writeI2C(BMP180_COMMAND_PRESSURE1);
	//send stop signal
	stopI2C();
	//delay 100ms
	_delay_ms(100);
	//start communication with BMP180
	startI2C(BMP180_ADDR_w);
	//select data register
	writeI2C(BMP180_REG_RESULT); 
	//send stop signal
	stopI2C();
	//request 3 bytes of data
	//start communication with BMP180
	startI2C(BMP180_ADDR_r);
	//read pressure
	uint32_t pres = ((readI2C(ACK) <<16) + (readI2C(ACK) <<8) + readI2C(NACK)) / 128; //128 = 8-OSS
	//send stop signal
	stopI2C();

	// Convert the data
	

	// Calibration for Temperature
	double X1 = (temp - (*bmp180).coof[5]) * (*bmp180).coof[4] / 32768.0;
	double X2 = ((double)(*bmp180).coof[9] * 2048.0) / (X1 + (*bmp180).coof[10]);
	double B5 = X1 + X2;
	float cTmp = ((B5 + 8.0) / 16.0) / 10.0;
	float fTmp = cTmp * 1.8 + 32;

	// Calibration for Pressure
	double B6 = B5 - 4000;
	X1 = ((*bmp180).coof[7] * ((long)B6 * (long)B6 / 4096.0)) / 2048.0;
	X2 = (*bmp180).coof[1] * B6 / 2048.0;
	double X3 = X1 + X2;
	double B3 = ((((*bmp180).coof[0] * 4 + X3) * 2) + 2) / 4.0;
	X1 = (*bmp180).coof[2] * B6 / 8192.0;
	X2 = ((*bmp180).coof[6] * ((long)B6 * (long)B6 / 2048.0)) / 65536.0;
	X3 = ((X1 + X2) + 2) / 4.0;
	double B4 = (*bmp180).coof[3] * (X3 + 32768) / 32768.0;
	long long B7 = (((unsigned long long )pres - (unsigned long long )B3) * ((unsigned long long )25000.0));
	float pressure = 0.0;
	if (B7 < 2147483648)
	{
		pressure = (B7 * 2) / B4;
	}
	else
	{
		pressure = (B7 / B4) * 2;
	}
	X1 = (pressure / 256.0) * (pressure / 256.0);
	X1 = (X1 * 3038.0) / 65536.0;
	X2 = ((-7357) * pressure) / 65536.0;
	pressure = (pressure + (X1 + X2 + 3791) / 16.0) / 100;

	// Calculate Altitude
	float height = 44330 * (1 - pow((pressure / 1013.25), 0.1903));
	(*bmp180).ctemp=cTmp;
	(*bmp180).ftemp=fTmp;
	(*bmp180).pressure=pressure;
	(*bmp180).altitude=height;
	return READ_SUCCESSFUL;
}


