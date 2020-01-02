/*
 * BAKR_7SEG.c
 *
 * Created: 27/08/2019 07:11:50 م
 *  Author:ABDELRAHMAN BAKR 
 */ 
#include "BAKR_7SEG.h"

void write_num(char x){
		switch (x ){
			case 0 :
			SEVEN_SEG_PORT = ZERO;
			break; 
			case 1 :
			SEVEN_SEG_PORT = ONE;
			break;
			case 2 :
			SEVEN_SEG_PORT = TWO;
			break;
			case 3 :
			SEVEN_SEG_PORT = THREE;
			break;
			case 4 :
			SEVEN_SEG_PORT = FOUR;
			break;
			case 5 :
			SEVEN_SEG_PORT = FIVE;
			break;
			case 6 :
			SEVEN_SEG_PORT = SIX;
			break;
			case 7 :
			SEVEN_SEG_PORT = SEVEN;
			break;
			case 8 :
			SEVEN_SEG_PORT = EIGHT;
			break;
			case 9 :
			SEVEN_SEG_PORT = NINE;
			break;
			
		}
}
void sequence(void ){
	
	SEVEN_SEG_PORT = ZERO;
	_delay_ms(100);
	SEVEN_SEG_PORT = ONE;
	_delay_ms(100);
	SEVEN_SEG_PORT = TWO;
	_delay_ms(100);
	SEVEN_SEG_PORT = THREE;
	_delay_ms(100);
	SEVEN_SEG_PORT = FOUR;
	_delay_ms(100);
	SEVEN_SEG_PORT = FIVE;
	_delay_ms(100);
	SEVEN_SEG_PORT = SIX;
	_delay_ms(100);
	SEVEN_SEG_PORT = SEVEN;
	_delay_ms(100);
	SEVEN_SEG_PORT = EIGHT;
	_delay_ms(100);
	SEVEN_SEG_PORT = NINE;
	_delay_ms(100);
	
}