/******************************************************************************
 *
 * Module:      UART
 * File Name:   UART.c
 * Target MC:   AVR 
 * Description: Source file for the UART AVR driver
 *
 * version :    1.0
 * created :    7:16:20 AM 
 * Author  :    Abdelrhman khafaga
 *
 *******************************************************************************/

#include "UART.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
static volatile void (*G_UART_RX)  (void)='\0' ;
static volatile void (*G_UART_TX)  (void)='\0' ;
/*******************************************************************************
 *                                ISR'S                                        *
 *******************************************************************************/
ISR(USART_RXC_vect)
{
	if (G_UART_RX!='\0')
		{
			(*G_UART_RX)();
		}
}

ISR(USART_TXC_vect)
{
	if (G_UART_TX!='\0')
		{
			(*G_UART_TX)();
		}
}

/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/

/*
 * initialization_function used to set up the configuration of UART
 * and also start is
 * the function takes configuration structure contains {mode,parity,baudrate}
 * the global interrupt must set to when using interrupt mode
 */
void UART_Initilialize(const UART_config  *UART_config_ptr)
{

	switch(UART_config_ptr->Mode)
	{
	case UART_Poling:

		UART_Init(UART_config_ptr->Parity,UART_config_ptr->BaudRate) ;

		break;
	case UART_Interrupt:

		UART_Init(UART_config_ptr->Parity,UART_config_ptr->BaudRate) ;

		UCSRB |=(1<<RXCIE);   // enable RX Interrupt

		break ;
	}
}


void UART_Init(UART_Parity parity ,UART_BaudRate baudrate)
{
	uint16 BAUD_PRESCALE;
	/* U2X = 1 for double transmission speed */
	UCSRA = (1<<U2X);

	/************************** UCSRB Description **************************
	 * RXCIE  USART RX Complete Interrupt Enable
	 * TXCIE  USART TX Complete Interrupt Enable
	 * UDRIE  USART Data Register Empty Interrupt Enable
	 * RXEN   Receiver Enable
	 * TXEN   Transmitter Enable
	 * UCSZ2  0 For 8-bit data mode
	 * RXB8 & TXB8  used for 9-bit data mode
	 ***********************************************************************/
	UCSRB = (1<<RXEN) | (1<<TXEN);
	/************************** UCSRC Description **************************
	 * URSEL   The URSEL must be one when writing the UCSRC
	 * UMSEL   Asynchronous/Synchronous Operation
	 * UPM1:0  parity bit setup
	 * USBS    One/two stop bit
	 * UCSZ1:0 11 For 8-bit data mode
	 * UCPOL   = 0 Used with the Synchronous operation only
	 ***********************************************************************/
	UCSRC = (1<<URSEL);
	UCSRC = (UCSRC & 0xCF) | (parity<<4) ; // putting parity

#ifdef	UART_FRAME_8_bit
	UCSRC |= (1<<UCSZ1) | (1<<UCSZ0) ;
#endif

#ifdef	UART_FRAME_5_bit
	UCSRC &=~((1<<UCSZ1) | (1<<UCSZ0)) ;
#endif
#ifdef	UART_FRAME_6_bit
	UCSRC |=(1<<UCSZ0) ;
#endif
#ifdef	UART_FRAME_7_bit
	UCSRC |= (1<<UCSZ1) ;
#endif


	BAUD_PRESCALE=(((F_CPU / (baudrate * 8UL))) - 1) ;
	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	UBRRH = BAUD_PRESCALE>>8;
	UBRRL = BAUD_PRESCALE;
}

/*
 * pause / resume function used to enable driver to stop/start UART serial
 * whenever it require
 * this function doesn't effect on previous configuration
 */
void UART_Pause(void)
{
	UCSRB &=~((1<<RXEN) | (1<<TXEN));  //disable RX & TX
}

void UART_Resume(void)
{
	UCSRB |= (1<<RXEN) | (1<<TXEN);  //Enable RX &  TX
}

void UART_Interrupt_Enable(void)
{
	UCSRB |=(1<<RXCIE);   // enable RX Interrupt
}

void UART_Interrupt_Disable(void)
{
	UCSRB &=~(1<<RXCIE);   // Disable RX Interrupt
}


void UART_SendByte(const uint8 data)
{
	/* UDRE flag is set when the Tx buffer (UDR) is empty and ready for
	 * transmitting a new byte so wait until this flag is set to one */
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}
	/* Put the required data in the UDR register and it also clear the UDRE flag as
	 * the UDR register is not empty now */
	UDR = data;
	/************************* Another Method *************************
	UDR = data;
	while(BIT_IS_CLEAR(UCSRA,TXC)){} // Wait until the transimission is complete TXC = 1
	SET_BIT(UCSRA,TXC); // Clear the TXC flag
	*******************************************************************/
}

uint8 UART_RecieveByte(void)
{
	/* RXC flag is set when the UART receive data so wait until this
	 * flag is set to one */
	while(BIT_IS_CLEAR(UCSRA,RXC)){}
	/* Read the received data from the Rx buffer (UDR) and the RXC flag
	   will be cleared after read this data */
    return UDR;
}


void UART_SendString(const uint8 *Str)
{
	uint8 i = 0;
	while(Str[i] != '\0')
	{
		UART_SendByte(Str[i]);
		i++;
	}
	/************************* Another Method *************************
	while(*Str != '\0')
	{
		UART_sendByte(*Str);
		Str++;
	}
	*******************************************************************/
}

void UART_ReceiveString(uint8 *Str)
{
	uint8 i = 0;
	Str[i] = UART_RecieveByte();
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_RecieveByte();
	}
	Str[i] = '\0';
}


/*
 * calling back function enable you to use UART_ISR
 * Any function passed to callback function will be
 * called in ISR
 */

void UART_Callback(void(*function_ptr) (void))
{
	G_UART_RX=function_ptr ;
}

