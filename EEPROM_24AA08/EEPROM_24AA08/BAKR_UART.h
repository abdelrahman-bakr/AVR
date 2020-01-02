/*
 * BAKR_UART.h
 *
 * Created: 27/08/2019 07:46:53 م
 *  Author: ABDELRAHMAN BAKR 
 */ 
#ifndef BAKR_USART_H_
#define BAKR_USART_H_ 
#define F_CPU 1000000
#define UART_FRAME_8_bit



#include <avr/io.h>
#include <util/delay.h>

typedef enum{
	NO_PARITY = 0,
	ODD_PARITY =1, 
	EVEN_PARITY =2 ,
	}UART_PARITY;
	
typedef enum{
		UART_POLLING,
		UART_INTERRUPT,
		}UART_MODE;

typedef enum{
	UART_BR_1200=1200,UART_BR_2400=2400,UART_BR_4800=4800,UART_BR_9600=9600,UART_BR_14400=14400,
	UART_BR_19200=19200,UART_BR_38400=38400,UART_BR_57600=57600,UART_BR_115200=115200
	}UART_BAUDRATE;

typedef struct{
	UART_BAUDRATE BR ; 
	UART_MODE MODE ; 
	UART_PARITY PARITY ; 
	}UART_CONFIG;

void	UART_Initialize(const UART_CONFIG* UART_CONFIG_PTR);
void	UART_Init( const UART_PARITY UART_PARITY , const UART_BAUDRATE UART_BR );
void	UART_Pause(void);
void	UART_Resume(void);
void	UART_Interrupt_Enable(void);
void	UART_Interrupt_Disable(void);

void	UART_TX( unsigned char data ); 
char    UART_RX(void);
void	UART_TX_STRING(char * data );
void    UART_RX_STRING(char * data);
void UART_Callback(void(*function_ptr) (void));


#endif
