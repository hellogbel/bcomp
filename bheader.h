#ifndef _BCOMP_H_
#define _BCOMP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 2048
#define TRUE 1
#define FALSE 0

struct regs;
typedef void (*micro_command_t)(struct regs *);

unsigned short get_address(char* title);
unsigned short get_data(int* finish_input);
void push(unsigned short val, unsigned short* mem, unsigned short* top);
void fill_mem(unsigned short* mem, unsigned short* top, int* finish_input);

#endif
