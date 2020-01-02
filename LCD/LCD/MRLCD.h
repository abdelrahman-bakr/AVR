#ifndef LCD
#define LCD

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#define LCDData			 PORTC
#define LCDDataDir		 DDRC
#define LCDControl		 PORTD
#define LCDControlDir	 DDRD
#define ENABLE			 5
#define READWRITE		 7
#define RegisterSelect	 2

char ColumnsPositions[4] = {0 , 64 , 20 , 84};

void LCD_peekapoo(void);
void LCD_busy(void);
void LCD_command(unsigned char command);
void LCd_send_char(unsigned char character);
void LCD_send_string( char *text );
void LCD_goto_location(uint8_t x ,uint8_t y);
void LCD_initialize(void);



#endif