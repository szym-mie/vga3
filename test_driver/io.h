#ifndef _IO_H_
#define _IO_H_

#include <stdint.h>

#define IO_REG(IO_ADDR) *((volatile uint8_t *) IO_ADDR) 

// TODO
#define INT_VECT(VECT, HANDLER) void VECT(void) { HANDLER volatile asm("reti" ::); }  

#endif//_IO_H_
