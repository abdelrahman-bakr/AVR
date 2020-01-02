/*
 * BAKR_DELAY.c
 *
 * Created: 27/08/2019 06:30:17 م
 *  Author: ABDELRAHMAN BAKR 
 */ 
#ifndef BAKR_DELAY 
#define BAKR_DELAY 

#define clock 8000000 
#define error_ratio 30 

unsigned long delay_count ; 

#define DELAY_MS(x) for (delay_count = (clock/1000)*x/error_ratio ; delay_count >0 ;delay_count--){asm("NOP");}


#endif