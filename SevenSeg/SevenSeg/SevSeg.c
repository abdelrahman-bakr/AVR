/*
 * SevSeg.c
 *
 * Created: 01/08/2019 07:51:31 م
 *  Author: MR.X
 */ 
#include "SevSeg.h"

char SevSeg_write_num(int num  )
{ char port ;
	
	if (num == 0 )
	{
		port = 0b01000000;
	}
	else if (num == 1 )
	{
		port = 0b01111001 ;
	}
	else if (num == 2 )
	{
		port = 0b00100100 ;
	}
	else if (num == 3)
	{
		port = 0b00110000 ;
	}
	else if (num == 4 )
	{
		port = 0b00011001 ;
	}
	else if (num == 5 )
	{
		port = 0b00010010 ;
	}
	else if (num == 6 )
	{
		port = 0b00000010 ;
	}
	else if (num == 7 )
	{
		port = 0b01111000 ;
	}
	else if (num == 8 )
	{
		port = 0b00000000 ;
	}
	else if (num == 9 )
	{
		port = 0b00010000 ;
	}
	return port ;
}

char ButtonPressed(char reg , char pin )
{
	if (reg & (1<<pin))
	{
		_delay_ms(500);
		if(reg & (1<<pin))
		{
			return 1 ;
		}
	}
	else return 0 ;
}

void inc_99(void){
	
	 int i = 0 ;
	 int j = 0 ;
	while(i< 10)
	{
		if(ButtonPressed(PINA,PINA0))
		{
			PORTB^=(1<<PB0);
			PORTC = SevSeg_write_num(i);
			PORTD = SevSeg_write_num(j);
			j++;
			
		}
		if (j == 10 )
		{
			j =0 ;
			i++ ;
		}
		
	}
	
	
}
