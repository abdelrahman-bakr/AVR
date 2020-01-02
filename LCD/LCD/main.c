#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "MRLCD.h"


int main(void)
{
	
	char PositionString[4];

    while (1) 
    {	
		for  (int j = 0 ; j < 4  ; j++)
		{
			for (int i =0 ; i < 20 ; i++)
		{
			
			itoa(i,PositionString,10);
			LCD_goto_location(13,2);
			LCD_send_string("X= ");
			LCD_send_string(PositionString);

			
			itoa(j,PositionString,10);
			LCD_goto_location(13,3);
			LCD_send_string("Y= ");
			LCD_send_string(PositionString);
			
			LCD_goto_location(i,j);
			LCD_send_string("x");
			
			
			
			_delay_ms(200);
			
			LCD_goto_location(i,j);
			LCD_send_string(" ");
			
			LCD_goto_location(13,2);
			LCD_send_string("      ");
			
			LCD_goto_location(13,3);
			LCD_send_string("      ");
			
			
		}
		
		}
    }
}

