

#include "SevSeg.h"



int main(void)
{
	DDRC = 0b11111111;
	DDRD = 0b11111111;
	DDRB |=(1<<PB0);
    PORTB &=  ~(1<<PB0);
   
    while (1) 
    {		
		inc_99();
		
    }
}

