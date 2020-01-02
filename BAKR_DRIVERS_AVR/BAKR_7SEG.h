/*
 * BAKR_7SEG.h
 *
 * Created: 27/08/2019 06:55:21 م
 *  Author: ABDELRAHMAN BAKR 
 */ 

#ifndef BAKR_7SEG_H_ 
#define BAKR_7SEG_H_ 

#include <avr/io.h>
#include <util/delay.h>

#define SEVEN_SEG_PORT PORTC 
#define SEVEN_SEG_DDR DDRC 


#define ZERO	0x40
#define ONE		0xF9 
#define TWO		0x24 
#define THREE	0x30
#define FOUR    0x19
#define FIVE	0x12 
#define SIX		0x02 
#define SEVEN	0x78 
#define EIGHT	0x00 
#define NINE	0x10 

void write_num(char x);
void sequence(void);


#endif