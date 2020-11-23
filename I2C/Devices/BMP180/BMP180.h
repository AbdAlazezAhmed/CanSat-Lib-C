/*
 * BMP180.h
 *
 * Created: 11/23/2020 11:08:01 AM
 *  Author: mizo
 */ 


#ifndef BMP180_H_
#define BMP180_H_

#define INIT_COMPLETE 24
#define READ_SUCCESSFUL 25

#include <stdlib.h>
#include <util/delay.h>
#include "BMP180_REG.h"
#include "../../Interface/MinI2C.h"

typedef struct BMP180_struct{
	uint16_t *coof;
	float ctemp;
	float ftemp;
	float pressure;
	float altitude;
}BMP180;

uint8_t initBMP180(BMP180 *bmp180);
uint8_t readBMP180(BMP180 *bmp180);

#endif /* BMP180_H_ */