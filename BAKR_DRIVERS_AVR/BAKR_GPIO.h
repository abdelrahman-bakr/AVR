/*
 * BAKR_GPIO.h
 *
 * Created: 27/08/2019 05:24:40 م
 *  Author: ABDELRAHMAN BAKR 
 */ 

#ifndef BAKR_GPIO 
#define BAKR_GPIO

//bit operation 
#define SET_BIT(reg,pin) reg |= (1<<pin)
#define CLR_BIT(reg,pin) reg &=~(1<<pin)
#define TOG_BIT(reg,pin) reg ^= (1<<pin)
#define READ_BIT(reg,pin) (reg & (1<<pin))




// IO PORTS REGISTERS A 
#define myPORTA  *((volatile unsigned char * const) 0x3B) 
#define myDDRA   *((volatile unsigned char * const) 0x3A) 
#define myPINA   *((volatile unsigned char * const) 0x39) 
// IO PORTS REGISTERS B
#define myPORTB  *((volatile unsigned char * const) 0x38)
#define myDDRB   *((volatile unsigned char * const) 0x37)
#define myPINB   *((volatile unsigned char * const) 0x36)
// IO PORTS REGISTERS C
#define myPORTC  *((volatile unsigned char * const) 0x35)
#define myDDRC   *((volatile unsigned char * const) 0x34)
#define myPINC  *((volatile unsigned char * const) 0x33) 
// IO PORTS REGISTERS D
#define myPORTD  *((volatile unsigned char * const) 0x32)
#define myDDRD   *((volatile unsigned char * const) 0x31)
#define myPIND   *((volatile unsigned char * const) 0x30)


#endif
