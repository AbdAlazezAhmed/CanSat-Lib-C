/*
 * MPU6050.c
 *
 * Created: 11/22/2020 6:24:51 PM
 *  Author: mizo
 */ 
#include "MPU6050.h"
uint8_t initMPU(){
	//delay >100ms for the power phase
	_delay_ms(100);
	//start communicating with MPU
	startI2C(MPU_ADDRESS);
	//write to sample rate register
	writeI2C(SMPLRT_DIV);
	//write sample rate from config
	writeI2C(MPU_SAMPLE_RATE);
	//send stop signal
	stopI2C();
	
	//start communicating with MPU
	startI2C(MPU_ADDRESS);
	//write to power management register
	writeI2C(PWR_MGMT_1);
	//write power management data
	writeI2C(MPU_POWER_MAN_VALUE);
	//send stop signal
	stopI2C();
	
	//start communicating with MPU
	startI2C(MPU_ADDRESS);
	//write to configuration register
	writeI2C(CONFIG);
	//write configuration data
	writeI2C(CONFIG_DATA);
	//send stop signal
	stopI2C();
	
	
	
	//start communicating with MPU
	startI2C(MPU_ADDRESS);
	//write to gyroscope configuration register
	writeI2C(GYRO_CONFIG);
	//write gyroscope configuration data
	writeI2C(GYRO_CONFIG_DATA);
	//send stop signal
	stopI2C();
	
	
	//start communicating with MPU
	startI2C(MPU_ADDRESS);
	//write to interrupt register
	writeI2C(INT_ENABLE);
	//write interrupt register data
	writeI2C(INTERRUPT_REG_DATA);
	//send stop signal
	stopI2C();
}

uint8_t startLocMPU(){
	//start communicating with MPU
	startI2C(MPU_ADDRESS);
	//write to start address of register to read from
	writeI2C(ACCEL_XOUT_H);
	//give start signal again
	startI2C(MPU_ADDRESS);
	return START_LOC_MPU_DONE;
}

uint8_t readRawMPU(MPU *mpu){
	startLocMPU();									
	(*mpu).Acc_x = (readI2C(ACK)<<8) | readI2C(ACK);
	(*mpu).Acc_y = (readI2C(ACK)<<8) | readI2C(ACK);
	(*mpu).Acc_z = (readI2C(ACK)<<8) | readI2C(ACK);
	(*mpu).Temperature = (readI2C(ACK)<<8) | readI2C(ACK);
	(*mpu).Gyro_x = (readI2C(ACK)<<8) | readI2C(ACK);
	(*mpu).Gyro_y = (readI2C(ACK)<<8) | readI2C(ACK);
	(*mpu).Gyro_z = (readI2C(ACK)<<8) | readI2C(NACK);
	stopI2C();
}