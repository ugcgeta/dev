#ifndef _GPIO_H_
#define _GPIO_H_

#include <stdbool.h>

bool GPIO_open(char* portNum);
bool GPIO_setDir(char* portNum, char* inout);
bool GPIO_outValue(char* portNum, char* portValue);
bool GPIO_close(char* portNum);

#endif
