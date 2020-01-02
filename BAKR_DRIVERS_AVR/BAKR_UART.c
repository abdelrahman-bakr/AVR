/*
 * BAKR_UART.c
 *
 * Created: 27/08/2019 07:47:04 م
 *  Author: ABDELRAHMAN BAKR 
 */ 

#include "BAKR_UART.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
static volatile void (*G_UART_RX)  (void)='\0' ;
static volatile void (*G_UART_TX)  (void)='\0' ;
/*******************************************************************************
 *                                ISR'S                                        *
 *******************************************************************************/



void UART_Initialize( const UART_CONFIG* UART_config_ptr)
{
	
	switch(UART_config_ptr->MODE)
	{
		case UART_POLLING:

		UART_Init(UART_config_ptr->PARITY,UART_config_ptr->BR) ;

		break;
		case UART_INTERRUPT:

		UART_Init(UART_config_ptr->PARITY ,UART_config_ptr->BR) ;

		UCSRB |=(1<<RXCIE);   // enable RX Interrupt

		break ;
		}
} 

UART_Init(const UART_PARITY PARITY , const UART_BAUDRATE BR) {
		uint16_t BAUD_PRESCALE;
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
	UCSRC  = (1<<URSEL);
	UCSRC |= (1<<URSEL)|(UCSRC & 0xCF) | (PARITY<<4) ; // putting parity

#ifdef	UART_FRAME_8_bit
UCSRC |= (1<<URSEL)|(1<<UCSZ1) | (1<<UCSZ0) ;
#endif

#ifdef	UART_FRAME_5_bit
UCSRC &=~((1<<URSEL)|(1<<UCSZ1) | (1<<UCSZ0)) ;
#endif
#ifdef	UART_FRAME_6_bit
UCSRC |=(1<<URSEL)|(1<<UCSZ0) ;
#endif
#ifdef	UART_FRAME_7_bit
UCSRC |= (1<<URSEL)|(1<<UCSZ1) ;
#endif

BAUD_PRESCALE=(((F_CPU / (BR * 8UL))) - 1) ;
/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
UBRRH = BAUD_PRESCALE>>8;
UBRRL = BAUD_PRESCALE;

	
}
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


void UART_TX( unsigned char data )
{
	/* Wait for empty transmit buffer*/
	while( !( UCSRA & (1<< UDRE)) ) ;

	/* Put data into buffer, sends the data*/
	UDR = data ;
}
void UART_TX_STRING(char * data ){
	 
		while(*data > 0)
			UART_TX(*data++);
			
		UART_TX('\0');
	 
	
}

char UART_RX()
{
	while(! (UCSRA & (1 << RXC) ) );
	return UDR;
}
void UART_RX_STRING(char * data){
	
	uint8_t i = 0;
	data[i] = UART_RX();
	
	while(data[i] != '#')
	{
		i++;
		data[i] = UART_RX();
	}
	data[i] = '\0';
}

void UART_Callback(void(*function_ptr) (void))
{
	G_UART_RX=function_ptr ;
}

