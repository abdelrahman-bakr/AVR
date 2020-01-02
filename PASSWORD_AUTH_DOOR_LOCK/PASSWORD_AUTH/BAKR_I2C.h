#ifndef BAKR_I2C
#define BAKR_I2C 

#define F_CPU 1000000
#define SCL_CLK 1000000
#include "avr/io.h"

#define BITRATE(TWSR)	((F_CPU/SCL_CLK)-16)/(2*pow(4,(TWSR&((1<<TWPS0)|(1<<TWPS1)))))

void I2C_Init();
uint8_t I2C_Start(char write_address);
uint8_t I2C_Repeated_Start(char read_address);
uint8_t I2C_Write(char data);
char I2C_Read_Ack();
char I2C_Read_Nack();
void I2C_Stop()	;


/********************************************************************************
	slave funvtions 
********************************************************************************/

void I2C_Slave_Init(uint8_t slave_address);
int8_t I2C_Slave_Listen();
int8_t I2C_Slave_Transmit(char data);
char I2C_Slave_Receive();


#endif