
#ifndef _DEBUG_UART_H_
#define _DEBUG_UART_H_

#include <stdint.h>
#include <stdbool.h>


typedef struct {
    volatile uint32_t DATA;
    volatile uint32_t CLKDIV;
} PICOUART;

#define UART0 ((PICOUART*)0x83000000)

#define ENABLE_DEBUG_PRINT (1)

int putchar(int c);
void print(const char *p);
void print_hex(uint32_t v, int digits);
void print_dec(uint32_t v);
void debug_print(const char *p);
void debug_print_hex(uint32_t v, int digits);
void debug_print_dec(uint32_t v);

char getchar_prompt(char *prompt);
char getchar();

void debug_uart_init();
#endif
