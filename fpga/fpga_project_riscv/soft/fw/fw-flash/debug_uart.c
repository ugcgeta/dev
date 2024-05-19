#include <stdint.h>
#include <stdbool.h>
#include "debug_uart.h"

int putchar(int c);
void print(const char *p);
void print_hex(uint32_t v, int digits);
void print_dec(uint32_t v);

void debug_print(const char *p)
{
#if ENABLE_DEBUG_PRINT
	print(p);
#endif
}

void debug_print_hex(uint32_t v, int digits)
{
#if ENABLE_DEBUG_PRINT
    print_hex(v, digits);
#endif
}

void debug_print_dec(uint32_t v)
{
#if ENABLE_DEBUG_PRINT
	print_dec(v);
#endif
}

int putchar(int c)
{	
    if (c == '\n')
        UART0->DATA = '\r';
    UART0->DATA = c;
    
    return c;
}

void print(const char *p)
{
    while (*p)
        putchar(*(p++));
}

void print_hex(uint32_t v, int digits)
{
    for (int i = 7; i >= 0; i--) {
        char c = "0123456789abcdef"[(v >> (4*i)) & 15];
        if (c == '0' && i >= digits) continue;
        putchar(c);
        digits = i;
    }
}

void print_dec(uint32_t v)
{
    if (v >= 100) {
        print(">=100");
        return;
    }

    if      (v >= 90) { putchar('9'); v -= 90; }
    else if (v >= 80) { putchar('8'); v -= 80; }
    else if (v >= 70) { putchar('7'); v -= 70; }
    else if (v >= 60) { putchar('6'); v -= 60; }
    else if (v >= 50) { putchar('5'); v -= 50; }
    else if (v >= 40) { putchar('4'); v -= 40; }
    else if (v >= 30) { putchar('3'); v -= 30; }
    else if (v >= 20) { putchar('2'); v -= 20; }
    else if (v >= 10) { putchar('1'); v -= 10; }

    if      (v >= 9) { putchar('9'); v -= 9; }
    else if (v >= 8) { putchar('8'); v -= 8; }
    else if (v >= 7) { putchar('7'); v -= 7; }
    else if (v >= 6) { putchar('6'); v -= 6; }
    else if (v >= 5) { putchar('5'); v -= 5; }
    else if (v >= 4) { putchar('4'); v -= 4; }
    else if (v >= 3) { putchar('3'); v -= 3; }
    else if (v >= 2) { putchar('2'); v -= 2; }
    else if (v >= 1) { putchar('1'); v -= 1; }
    else putchar('0');
}

char getchar_prompt(char *prompt)
{
    int32_t c = -1;

    uint32_t cycles_begin, cycles_now, cycles;
    __asm__ volatile ("rdcycle %0" : "=r"(cycles_begin));

    if (prompt)
        print(prompt);

    // if (prompt)
        // GPIO0->OUT = ~0;
        // reg_leds = ~0;

    while (c == -1) {
        __asm__ volatile ("rdcycle %0" : "=r"(cycles_now));
        cycles = cycles_now - cycles_begin;
        if (cycles > 12000000) {
            if (prompt)
                print(prompt);
            cycles_begin = cycles_now;
            // if (prompt)
                // GPIO0->OUT = ~GPIO0->OUT;
                // reg_leds = ~reg_leds;
        }
        c = UART0->DATA;
    }
    // if (prompt)
        // GPIO0->OUT = 0;
        // reg_leds = 0;
    return c;
}

char getchar()
{
    return getchar_prompt(0);
}

//#define CLK_FREQ        25175000
#define CLK_FREQ        27000000
#define UART_BAUD       115200


void debug_uart_init()
{
    UART0->CLKDIV = CLK_FREQ / UART_BAUD - 2;
}