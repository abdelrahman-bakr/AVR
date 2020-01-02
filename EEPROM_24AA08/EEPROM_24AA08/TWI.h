/******************************************************************************
 *
 * Module:      I2C
 * File Name:   I2C.h
 * Target MC:   AVR
 * Description: Source file for the UART AVR driver
 *
 * version :    1.0
 * created :    7:16:48 AM
 * Author  :    Abdelrhman khafaga
 *
 *******************************************************************************/


#ifndef TWI_H_
#define TWI_H_

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"


/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum
{
	TWI_Poling,TWI_Interrupt
}TWI_Mode ;


typedef struct
{
	TWI_Mode   Mode     ;
	uint8      Address  ;

}TWI_config ;


/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* I2C Status Bits in the TWSR Register */
#define TWI_START           0x08 // start has been sent
#define TWI_REP_START       0x10 // repeated start
#define TWI_MT_SLA_W_ACK    0x18 // Master transmit ( slave address + Write request ) to slave + ACK received from slave
#define TWI_MT_SLA_W_NACK   0x20 // Master transmit ( slave address + Write request ) to slave + NOT ACK received from slave
#define TWI_MT_DATA_ACK     0x28 // Master transmit data and ACK has been received from Slave.
#define TWI_MT_DATA_NACK    0x30 // Master transmit data and NOT ACK has been received from Slave.

#define TWI_MT_SLA_R_ACK    0x40 // Master transmit ( slave address + Read request ) to slave + ACK received from slave
#define TWI_MT_SLA_R_NACK   0x48 // Master transmit ( slave address + Read request ) to slave + NOT ACK received from slave
#define TWI_MR_DATA_ACK     0x50 // Master received data and send ACK to slave
#define TWI_MR_DATA_NACK    0x58 // Master received data but doesn't send ACK to slave

#define TWI_SR_SLA_W_ACK    0x60 // Slave Received ( slave address + Write request ) + ACK Transmit from slave
#define TWI_SR_GCALL_ACK    0x70 // Slave Received General Call + ACK Transmit from slave
#define TWI_SR_DATA_ACK     0x80 // Previously addressed with own SLA+W; data has been received; ACK has been returned
#define TWI_SR_DATA_NACK    0x88 // Previously addressed with own SLA+W; data has been received; NOT ACK has been returned
#define TWI_SR_GC_DATA_ACK  0x90 // Previously addressed with General Call; data has been received; ACK has been returned
#define TWI_SR_GC_DATA_NACK 0x98 // Previously addressed with General Call; data has been received; NOT ACK has been returned
#define TWI_STOP            0xA0 // STOP condition or repeated START condition has been received while still addressed as slave

#define TWI_SR_SLA_R_ACK    0xA8 // Slave Received ( slave address + Read request ) + ACK Transmit from slave
#define TWI_ST_DATA_ACK     0xB8 // Slave Transmit data and ACK has been received
#define TWI_ST_DATA_NACK    0xC0 // Slave Transmit data and NOT ACK has been received
#define TWI_ST_LAST_DATA    0xC8 // Slave Transmit LAST data and ACK has been received


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void TWI_initialize(const TWI_config* TWI_config_ptr);
void TWI_Send_Start(void);
void TWI_Send_Stop(void);
void TWI_Enable(void);
void TWI_Disable(void);

void TWI_Write(uint8 data);
uint8 TWI_Read_ACK(void);
uint8 TWI_Read_NACK(void);
uint8 TWI_Status(void);
uint8 TWI_Send_String(uint8 address,const uint8* str_ptr);
void TWI_Receive_String(uint8* buffer);
void TWI_Callback(void(*function_ptr) (void));


#endif /* I2C_H_ */
