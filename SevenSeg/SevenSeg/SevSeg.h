/*
 * SevSeg.h
 *
 * Created: 01/08/2019 07:50:15 م
 *  Author: MR.X
 */ 
#ifndef SevSeg_H_
#define SevSeg_H_
#define  F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

char SevSeg_write_num(int num );
char ButtonPressed(char reg , char pin );
void inc_99(void);


#endif
