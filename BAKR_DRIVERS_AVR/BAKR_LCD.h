#ifndef BAKR_LCD_H_
#define BAKR_LCD_H_ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#define LCDData			 PORTB
#define LCDDataDir		 DDRB
#define LCDControl		 PORTA
#define LCDControlDir	 DDRA
#define ENABLE			 5
#define READWRITE		 7
#define RegisterSelect	 2
#define CLEAR_SCREEN 0x01 




char ColumnsPositions[4] = {0 , 64 , 20 , 84};

void LCD_peekapoo(void);
void LCD_busy(void);
void LCD_command(unsigned char command);
void LCD_clear_screen(void);
void LCd_send_char(unsigned char character);
void LCD_send_string( char *text );
void LCD_goto_location(uint8_t x ,uint8_t y);
void LCD_initialize(void);



#endif