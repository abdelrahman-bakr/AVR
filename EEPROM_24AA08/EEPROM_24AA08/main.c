/*
 * EEPROM_24AA08.c
 *
 * Created: 23/08/2019 03:33:00 م
 * Author : MR.X
 */ 

#include <avr/io.h>
#include "BAKR_I2C.h"
#include <util/delay.h> 
#include "BAKR_UART.h"



int main(void)
{
		UART_CONFIG config = {UART_BR_9600,UART_POLLING,NO_PARITY} ; 
		
		
//	I2C_Init(0x20); 
I2C_Slave_Init(0xC0);
	UART_Initialize(&config);
	char *ptr = malloc(10); 
  char x,y ; 
  
    while (1) 
    {
	UART_TX('y');
	_delay_ms(100);
		switch(I2C_Slave_Listen())	/* Check for SLA+W or SLA+R */
			{
		case 0:{
			x =	I2C_Slave_Receive();
			
			_delay_ms(100);
			UART_TX(x);
			_delay_ms(100);
		}

	
			}
		
    }
}

void EEPROM__READ(char address,char* store_location ){
	
	I2C_Start(0x20);
	I2C_Write(0xA8);
	I2C_Write(address);
	
	I2C_Start(0x20);
	I2C_Write(0xA9);
	I2C_Read_Nack(store_location);
	I2C_Stop(); 
	
}

