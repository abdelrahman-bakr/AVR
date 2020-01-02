#define F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>
#include "BAKR_KEYPAD.h"
#include "BAKR_UART.h"
#include "BAKR_LCD.h"
#include "BAKR_I2C.h"

#define SET_BIT(reg,pin) reg |= (1<<pin)
#define CLR_BIT(reg,pin) reg &=~(1<<pin)
#define TOG_BIT(reg,pin) reg ^= (1<<pin)
#define READ_BIT(reg,pin) (reg & (1<<pin))

#define EEPROM_WRITE_ADDRESS 0xA8
#define EEPROM_READ_ADDRESS  0xA9 

#define YELLOW_LED PA0 
#define GREEN_LED  PA3 
#define RED_LED    PA1
#define SERVO      PA4    

#define NEW_PASS_BUTTON PA6   


int  EEPROM_Read();
void EEPROM_Save(char* password); 
int get_password_No_Display(char * password);
int get_password_Display(char * password);
void new_password_prompt();
void door_closed(void); 
void door_opened(void); 


int main(void)
{
	//UART_CONFIG config = {UART_BR_9600,UART_POLLING,NO_PARITY} ;
	//UART_Initialize(&config);
	
	int real_password,test_password,EEPROM_password ;
	char password[8] = {0} ;
	
	DDRA  |= (1<<YELLOW_LED)|(1<<RED_LED)|(1<<GREEN_LED)|(1<<SERVO) ;
	PORTA &= ~ (1<<YELLOW_LED)|(1<<RED_LED)|(1<<GREEN_LED)|(1<<SERVO);
	DDRA &= ~(1<<NEW_PASS_BUTTON) ; 
	
	Keypad_init();
	LCD_initialize();
	LCD_peekapoo();
	I2C_Init();
	door_closed();			
	

	
	
			
		new_password_prompt();
	real_password = get_password_No_Display(password);	// get the password from the user for the first time
	PORTA &= ~(1<<YELLOW_LED);
	EEPROM_Save(password);  	//save the password to eeprom location 0x00 
		
	
	while(1)
	{	
		
			
	
		
			
			LCD_clear_screen();
			LCD_goto_location(0,0);
			_delay_ms(10);
			LCD_send_string("enter password:  ");      // prompt the user to enter the password
			
			test_password = get_password_Display(password); // get the password
			
			EEPROM_password = EEPROM_Read();	// get the password saved in the EEPROM
			_delay_ms(500);
			
			LCD_clear_screen();
			LCD_goto_location(0,0);
			_delay_ms(10);
			LCD_send_string("authenticating..");
			LCD_goto_location(0,2);
			if (EEPROM_password == test_password)
			{
				
				LCD_send_string("success");
				PORTA |= (1<<GREEN_LED) ;
				door_opened();
			}
			else
			{
				LCD_send_string("failed");
				PORTA |= (1<<RED_LED) ;
				door_closed();

			}
		
	}
	return 0;
}
int EEPROM_Read(){
	
		
		
char y ;
char pass2[8] = {0} ;
	 
	I2C_Start(EEPROM_WRITE_ADDRESS); 
	I2C_Write(0x00); 
	I2C_Repeated_Start(EEPROM_READ_ADDRESS) ;
	_delay_ms(10);
	
	for(int i = 0 ; i < 8 ; i++){
		if(i<7 )
		{
			y = I2C_Read_Ack();
			_delay_ms(100);
			pass2[i]  = y  ;
		}
		else {
			y = I2C_Read_Nack();
			_delay_ms(100);
			pass2[i]  = y  ;
		}
	
	}
	I2C_Stop();
	 return atoi(pass2);
	
	
	
	
}

int get_password_No_Display(char * password){
	char x ;
	
	int counter = 0 ;
	int password_int;
	
	while(counter<8){
		
		x = Keypad_getkey();
		
		switch(x){
			
			case 'A':
			break;
			
			default :
			LCd_send_char('*');
			_delay_ms(100);
			password[counter] = x ;
			counter++ ;
			break;
		}
		
		
	}
	password_int = atoi(password);
	return password_int ;
}

int get_password_Display(char * password){
	char x ;
	
	int counter = 0 ;
	int password_int;
	
	while(counter<8){
		
		x = Keypad_getkey();
		
		switch(x){
			
			case 'A':
			break;
			
			default :
			LCd_send_char(x);
			_delay_ms(100);
			password[counter] = x ;
			counter++ ;
			break;
		}
		
		
	}
	password_int = atoi(password);
	return password_int ;
}
void EEPROM_Save(char * password){
	  
	   
	I2C_Start(EEPROM_WRITE_ADDRESS);
	I2C_Write(0x00);
	
	for (int i = 0 ; i <8 ; i++)
	{
		I2C_Write(password[i]);
		_delay_ms(100);

	}
	I2C_Stop();
	_delay_ms(10);
}

void new_password_prompt(){
	
	 PORTA |= (1<<YELLOW_LED) ;
	 LCD_clear_screen();
	 LCD_goto_location(0,0);
	 _delay_ms(10);
	 LCD_send_string("new  password:  ");      // prompt the user to enter the password for the first time
	 _delay_ms(500);
	}

void door_closed(void){
	
	PORTA |= (1<<SERVO) ;
	_delay_us(1000);
	PORTA &= ~ (1<<SERVO);
	_delay_ms(2000);
	
}
void door_opened(void){
	
	PORTA |= (1<<SERVO) ;
	_delay_us(1500);
	PORTA &= ~ (1<<SERVO);
	_delay_ms(2000);
	
}

	