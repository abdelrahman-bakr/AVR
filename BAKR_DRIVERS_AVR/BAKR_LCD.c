
#include "BAKR_LCD.h"

void LCD_busy(void)
{
	LCDDataDir = 0;
	LCDControl |= (1<<READWRITE);
	LCDControl &= ~(1<<RegisterSelect);
	while (LCDData >= 0x80)
	{
		LCD_peekapoo();
	}
	
	LCDDataDir = 0xFF;
	
}

void LCD_peekapoo(void)
{
	LCDControl |= (1<<ENABLE);
	asm volatile("nop");
	asm volatile("nop");
	LCDControl &= ~(1<<ENABLE);

}
void LCD_command(unsigned char command)
{
	LCD_busy();
	LCDData = command ;
	LCDControl &= ~(1<<READWRITE | 1<<RegisterSelect);
	LCD_peekapoo();
	LCDData = 0;
}

void LCD_send_string( char *text )
{
	while(*text > 0)
	{
		LCd_send_char(*text);
		*text++ ;
	}
	
}

void LCD_goto_location(uint8_t x ,uint8_t y)
{
	LCD_command( 0x80 +ColumnsPositions[y] + x);

	
}
void LCD_initialize(void)
{
	LCDControlDir |= (1<<ENABLE) | (1<<READWRITE) |(1<<RegisterSelect) ;
	_delay_ms(15);
	
	LCD_command(CLEAR_SCREEN); // clear screen
	_delay_ms(2);
	LCD_command(0x38) ;
	_delay_us(50);
	LCD_command(0b00001110);
	_delay_us(50);
}



void LCd_send_char(unsigned char character)
{
	LCD_busy();
	LCDData = character ;
	LCDControl &= ~(1<<READWRITE );
	LCDControl |= (1<<RegisterSelect);
	LCD_peekapoo();
	LCDData = 0;
	
}

void LCD_clear_screen(void){
	
	LCD_command(CLEAR_SCREEN);
}


