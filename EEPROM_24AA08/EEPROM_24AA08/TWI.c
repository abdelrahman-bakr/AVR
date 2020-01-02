/******************************************************************************
 *
 * Module:      I2C
 * File Name:   I2C.c
 * Target MC:   AVR
 * Description: Source file for the UART AVR driver
 *
 * version :    1.0
 * created :    7:16:20 AM
 * Author  :    Abdelrhman khafaga
 *
 *******************************************************************************/

#include "TWI.h"
/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
static volatile void (*G_TWI)  (void)='\0' ;
static enum state{ERROR,SUCCESS};
/*******************************************************************************
 *                                ISR'S                                        *
 *******************************************************************************/
ISR(TWI_vect)
{
	if (G_TWI!='\0')
	{
		(*G_TWI)();
	}
}
/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/
void TWI_initialize(const TWI_config*  TWI_config_ptr)
{
	/* Bit Rate: 200.000 kbps using zero pre-scaler TWPS=00 and F_CPU=8Mhz */
	TWBR = 0x0B;   //TWBR should be 10 or higher if the TWI operates in Master mode.
	TWSR = 0x00;

	/*putting address & General Call Recognition: on */
	TWAR = ((TWI_config_ptr->Address)<<1)|(1<<TWGCE) ;

	TWCR = (1<<TWEN)|(1<<TWEA)|((TWI_config_ptr->Mode)<<TWIE);
	/* enable TWI & enable/disable TWI interrupt */
}


void TWI_Send_Start(void)
{
	/*
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * save the previous configuration by (TWCR & 0x4F)
	 */
	TWCR &= 0x4F ;
	TWCR |= (1 << TWINT) | (1 << TWSTA) ;
	/* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT)){};
}

void TWI_Send_Stop(void)
{
	/*
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * save the previous configuration by (TWCR & 0x4F)
	 */

	TWCR &= 0x4F ;
	TWCR |= (1 << TWINT) | (1 << TWSTO) ;
}

void TWI_Enable(void)
{
	TWCR &=~(1<<TWEN); //disable TWI

}

void TWI_Disable(void)
{
	TWCR |=(1<<TWEN); //Enable TWI

}

void TWI_Write(uint8 data)
{
	/* Put data On TWI data Register */
	TWDR = data;
	/*
	 * Clear the TWINT flag before sending the data TWINT=1
	 * save the previous configuration by (TWCR & 0x4F)
	 */
	TWCR &= 0x4F ;
	TWCR |= (1 << TWINT);
	/* Wait for TWINT flag set in TWCR Register(data is send successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT)){};
}


uint8 TWI_Read_ACK(void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 */
	TWCR &= 0x4F ;

	TWCR |= (1 << TWINT) | (1 << TWEA);
	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT)){};
	/* Read Data */
	return TWDR;
}

uint8 TWI_Read_NACK(void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 */
	TWCR &= 0x4F ;
	TWCR &=~(1 << TWEA) ;
	TWCR |= (1 << TWINT);

	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));
	/* Read Data */
	return TWDR;
}


uint8 TWI_Status(void)
{
	uint8 status;
	/* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
	status = TWSR & 0xF8;
	return status;
}


uint8 TWI_Send_String(uint8 address,const uint8* str_ptr)
{
	uint8 SLA_W,i=0 ;

	/* Send the Start Bit */
	TWI_Send_Start();

	if (TWI_Status() != TWI_START)
	{
		TWI_Send_Stop();
		return ERROR;
	}
	/* Send the Device Address */
	SLA_W=(address<<1) ; // 7-bit address + 0 (Write)
	TWI_Write(SLA_W);

	if (TWI_Status() != TWI_MT_SLA_W_ACK)
	{
		TWI_Send_Stop();
		return ERROR;
	}

	/* Send the Data */
	while(str_ptr[i]!='\0')
	{
		TWI_Write(str_ptr[i]);
		if (TWI_Status() != TWI_MT_DATA_ACK)
		{
			TWI_Send_Stop();
			return ERROR;
		}
		i++ ;
	}
	/* Send the Stop Bit */
	TWI_Send_Stop();
	return SUCCESS;
}

/*
 * this function called by ISR
 */

void TWI_Receive_String(uint8* buffer)
{
static uint8 i ;
	if((TWI_Status() == TWI_SR_SLA_W_ACK) || (TWI_Status() == TWI_SR_GCALL_ACK))
	{
		i=0 ; //start of data
	}

	else if ((TWI_Status() == TWI_SR_DATA_ACK) || (TWI_Status() == TWI_SR_GC_DATA_ACK))
	{
		buffer[i++]=TWDR; //get data in case of receive address or general call
	}
	buffer[i]='\0' ;
	TWCR |= (1 << TWINT);
}

void TWI_Callback(void(*function_ptr) (void))
{
	G_TWI=function_ptr ;
}
