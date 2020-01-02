/******************************************************************************
 *
 * Module:      UART
 * File Name:   UART.h
 * Target MC:   AVR 
 * Description: Source file for the UART AVR driver
 *
 * version :    1.0
 * created :    7:16:48 AM 
 * Author  :    Abdelrhman khafaga
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

#define UART_FRAME_8_bit

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	UART_Poling,UART_Interrupt
}UART_Mode ;

typedef enum
{
	UART_No_Parity,UART_Even_Parity=2,UART_Odd_Parity
}UART_Parity ;


typedef enum
{
	UART_BR_1200=1200,UART_BR_2400=2400,UART_BR_4800=4800,UART_BR_9600=9600,UART_BR_14400=14400,
	UART_BR_19200=19200,UART_BR_38400=38400,UART_BR_57600=57600,UART_BR_115200=115200
}UART_BaudRate ;

typedef struct
{
	UART_Mode     Mode     ;
	UART_Parity   Parity   ;
	UART_BaudRate BaudRate ;

}UART_config ;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void UART_Initilialize(const UART_config  *UART_config_ptr);
void UART_Init(UART_Parity parity ,UART_BaudRate baudrate);
void UART_Pause(void);
void UART_Resume(void);
void UART_Interrupt_Enable(void);
void UART_Interrupt_Disable(void);

void UART_SendByte(const uint8 data);
uint8 UART_RecieveByte(void);
void UART_SendString(const uint8 *Str);
void UART_ReceiveString(uint8 *Str);
void UART_Callback(void(*function_ptr) (void));

#endif /* UART_H_ */
