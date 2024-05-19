#include <stdint.h>
#include <stdbool.h>
#include "debug_uart.h"
#include "drv_i2c.h"

// a pointer to this is a null pointer, but the compiler does not
// know that because "sram" is a linker symbol from sections.lds.
extern uint32_t sram;

typedef struct {
    volatile uint32_t OUT;
    volatile uint32_t IN;
    volatile uint32_t OE;
} PICOGPIO;

typedef struct {
    union {
        volatile uint32_t REG;
        volatile uint16_t IOW;
        struct {
            volatile uint8_t IO;
            volatile uint8_t OE;
            volatile uint8_t CFG;
            volatile uint8_t EN; 
        };
    };
} PICOQSPI;

typedef struct {
    union {
		volatile uint32_t RBR;
		volatile uint32_t THR;
    };
	volatile uint32_t IER;
	volatile uint32_t IIR;
	volatile uint32_t LCR;
	volatile uint32_t MCR;
	volatile uint32_t LSR;
	volatile uint32_t MSR;
    
} ST_UART_IP;


#define QSPI0 ((PICOQSPI*)0x81000000)
#define GPIO0 ((PICOGPIO*)0x82000000)
//#define UART0 ((PICOUART*)0x83000000)
#define UART_IP ((ST_UART_IP*)0x84000000)
//#define I2C_IP ((ST_I2C_IP*)0x85000000)

#define FLASHIO_ENTRY_ADDR ((void *)0x80000054)

void (*spi_flashio)(uint8_t *pdata, int length, int wren) = FLASHIO_ENTRY_ADDR;

#define QSPI_REG_CRM  0x00100000
#define QSPI_REG_DSPI 0x00400000

void cmd_set_crm(int on)
{
    if (on) {
        QSPI0->REG |= QSPI_REG_CRM;
    } else {
        QSPI0->REG &= ~QSPI_REG_CRM;
    }
}

int cmd_get_crm() {
    return QSPI0->REG & QSPI_REG_CRM;
}

void cmd_set_dspi(int on)
{
    if (on) {
        QSPI0->REG |= QSPI_REG_DSPI;
    } else {
        QSPI0->REG &= ~QSPI_REG_DSPI;
    }
}

int cmd_get_dspi() {
    return QSPI0->REG & QSPI_REG_DSPI;
}

void cmd_read_flash_id()
{
    int pre_dspi = cmd_get_dspi();

    cmd_set_dspi(0);
    
    uint8_t buffer[4] = { 0x9F, /* zeros */ };
    spi_flashio(buffer, 4, 0);

    for (int i = 1; i <= 3; i++) {
        putchar(' ');
        print_hex(buffer[i], 2);
    }
    putchar('\n');

    cmd_set_dspi(pre_dspi);
}

// --------------------------------------------------------

uint32_t cmd_benchmark(bool verbose, uint32_t *instns_p)
{
    uint8_t data[256];
    uint32_t *words = (void*)data;

    uint32_t x32 = 314159265;

    uint32_t cycles_begin, cycles_end;
    uint32_t instns_begin, instns_end;
    __asm__ volatile ("rdcycle %0" : "=r"(cycles_begin));
    __asm__ volatile ("rdinstret %0" : "=r"(instns_begin));

    for (int i = 0; i < 20; i++)
    {
        for (int k = 0; k < 256; k++)
        {
            x32 ^= x32 << 13;
            x32 ^= x32 >> 17;
            x32 ^= x32 << 5;
            data[k] = x32;
        }

        for (int k = 0, p = 0; k < 256; k++)
        {
            if (data[k])
                data[p++] = k;
        }

        for (int k = 0, p = 0; k < 64; k++)
        {
            x32 = x32 ^ words[k];
        }
    }

    __asm__ volatile ("rdcycle %0" : "=r"(cycles_end));
    __asm__ volatile ("rdinstret %0" : "=r"(instns_end));

    if (verbose)
    {
        print("Cycles: 0x");
        print_hex(cycles_end - cycles_begin, 8);
        putchar('\n');

        print("Instns: 0x");
        print_hex(instns_end - instns_begin, 8);
        putchar('\n');

        print("Chksum: 0x");
        print_hex(x32, 8);
        putchar('\n');
    }

    if (instns_p)
        *instns_p = instns_end - instns_begin;

    return cycles_end - cycles_begin;
}

void cmd_benchmark_all()
{
    uint32_t instns = 0;

    print("default        ");

    cmd_set_dspi(0);
    cmd_set_crm(0);

    print(": ");
    print_hex(cmd_benchmark(false, &instns), 8);
    putchar('\n');

    print("dspi-");
    print_dec(0);
    print("         ");

    cmd_set_dspi(1);

    print(": ");
    print_hex(cmd_benchmark(false, &instns), 8);
    putchar('\n');

    print("dspi-crm-");
    print_dec(0);
    print("     ");

    cmd_set_crm(1);

    print(": ");
    print_hex(cmd_benchmark(false, &instns), 8);
    putchar('\n');

    print("instns         : ");
    print_hex(instns, 8);
    putchar('\n');
}

volatile int i;
// --------------------------------------------------------

//#define CLK_FREQ        25175000
#define CLK_FREQ        27000000

void main()
{
	debug_uart_init();

    GPIO0->OE = 0x3F;
    GPIO0->OUT = 0x3F;
	
	i2c_init(I2C_CLK_FREQ_100K);

    cmd_set_crm(1);
    cmd_set_dspi(1);

    print("\n");
    print("  ____  _          ____         ____\n");
    print(" |  _ \\(_) ___ ___/ ___|  ___  / ___|\n");
    print(" | |_) | |/ __/ _ \\___ \\ / _ \\| |\n");
    print(" |  __/| | (_| (_) |__) | (_) | |___\n");
    print(" |_|   |_|\\___\\___/____/ \\___/ \\____|\n");
    print("\n");
    print("        On Lichee Tang Nano-9K\n");
    print("\n");

    for ( i = 0 ; i < 10000; i++);
    GPIO0->OUT = 0x3F ^ 0x01;
    for ( i = 0 ; i < 10000; i++);
    GPIO0->OUT = 0x3F ^ 0x02;
    for ( i = 0 ; i < 10000; i++);
    GPIO0->OUT = 0x3F ^ 0x04;
    for ( i = 0 ; i < 10000; i++);
    GPIO0->OUT = 0x3F ^ 0x08;
    for ( i = 0 ; i < 10000; i++);
    GPIO0->OUT = 0x3F ^ 0x10;
    for ( i = 0 ; i < 10000; i++);
    GPIO0->OUT = 0x3F ^ 0x20;
    for ( i = 0 ; i < 10000; i++);
    GPIO0->OUT = 0x3F;
    for ( i = 0 ; i < 10000; i++);
    GPIO0->OUT = 0x00;
    for ( i = 0 ; i < 10000; i++);
    GPIO0->OUT = 0x3F;
    for ( i = 0 ; i < 10000; i++);

    while (1)
    {
        print("\n");
        print("Select an action:\n");
        print("\n");
        print("   [1] Toggle led 1\n");
        print("   [2] Toggle led 2\n");
        print("   [3] Toggle led 3\n");
        print("   [4] Toggle led 4\n");
        print("   [5] Toggle led 5\n");
        print("   [6] Toggle led 6\n");
        print("   [F] Get flash mode\n");
        print("   [I] Read SPI flash ID\n");
        print("   [S] Set Single SPI mode\n");
        print("   [D] Set DSPI mode\n");
        print("   [C] Set DSPI+CRM mode\n");
        print("   [B] Run simplistic benchmark\n");
        print("   [A] Benchmark all configs\n");
    	print("   [W] write UART_IP 123\n");
    	print("   [R] read UART_IP 1char\n");
    	print("   [Z] read ALL reg UART_IP\n");
    	print("   [x] read i2c\n");
    	print("   [X] write i2c\n");
    	print("   [V] read ALL reg i2c \n");
        
        for (int rep = 10; rep > 0; rep--)
        {
            print("\n");
            print("IO State: ");
            print_hex(GPIO0->IN, 8);
            print("\n");

            print("\n");

            print("Command> ");
            char cmd = getchar();
            if (cmd > 32 && cmd < 127)
                putchar(cmd);
            print("\n");

            switch (cmd)
            {
            case 'F':
            case 'f':
                print("\n");
                print("SPI State:\n");
                print("  DSPI ");
                if ( cmd_get_dspi() )
                    print("ON\n");
                else
                    print("OFF\n");
                print("  CRM  ");
                if ( cmd_get_crm() )
                    print("ON\n");
                else
                    print("OFF\n");

                break;

            case 'I':
            case 'i':
                cmd_read_flash_id();
                break;

            case 'S':
            case 's':
                cmd_set_dspi(0);
                cmd_set_crm(0);
                break;

            case 'D':
            case 'd':
                cmd_set_crm(0);
                cmd_set_dspi(1);
                break;

            case 'C':
            case 'c':
                cmd_set_crm(1);
                cmd_set_dspi(1);
                break;

            case 'B':
            case 'b':
                cmd_benchmark(1, 0);
                break;

            case 'A':
            case 'a':
                cmd_benchmark_all();
                break;
            case 'W':
            case 'w':
                UART_IP->THR = '1';
            	putchar('1');
            	UART_IP->THR = '2';
            	putchar('2');
            	UART_IP->THR = '3';
            	putchar('3');
            	
                break;
            case 'R':
            	{
            	uint32_t temp = UART_IP->RBR;
            	print("char : ");
            	putchar(temp);
            	putchar('\n');
            	print("PBR : ");
            	print_hex(temp, 4);
            	putchar('\n');
            	}
            	break;
            case 'r':
                //putchar(UART_IP->RBR);
            	//print("PBR : ");
            	//print_hex(UART_IP->RBR, 2);
            	//putchar('\n');
            	putchar('\n');
            	print("IER adr: ");
            	print_hex((uint32_t)(&(UART_IP->IER)), 8);
            	print("IER : ");
            	print_hex(UART_IP->IER, 2);
            	putchar('\n');
            	print("IIR adr: ");
            	print_hex((uint32_t)(&(UART_IP->IIR)), 8);
            	print("IIR : ");
            	print_hex(UART_IP->IIR, 2);
            	putchar('\n');
            	print("LSR : ");
            	print_hex(UART_IP->LSR, 2);
            	putchar('\n');
            	print("MSR : ");
            	print_hex(UART_IP->MSR, 2);
            	putchar('\n');
                break;
            case 'z':
            case 'Z':
            	{
            		int i=0;
            		uint32_t reg;
            		for(i=0;i<7;i++){
            			putchar('0'+i);
            			putchar(':');
            			print_hex((volatile uint32_t)((0x84000000)+i*4), 8);
            			
            			reg = *((volatile uint32_t*)(0x84000000+i*4));
            			putchar(':');
            			print_hex(reg, 4);
            			putchar('\n');
            		}
            		putchar('\n');
            		
            	}
                break;
			case 'x':
            	{
            		uint32_t distance;
            		uint8_t resvData[2];
            		i2c_read_reg(0x40, 0x5E, resvData, 2);
            		//print(" \n i2c_read_reg = \n");
            		//print_hex(resvData[0], 2);
            		//print_hex(resvData[1], 2);
            		distance = ((resvData[0]*16+resvData[1]) >>4) >> 2;
            		print(" \n distance = ");
            		print_dec(distance);
            		print(" \n");
            	}
            	break;
            case 'X':
            	{
            		print("I2C write : \n");
            	}
            	break;
			case 'v':
            case 'V':
            	{
            		print("I2C ALL reg : \n");
            		int i=0;
            		uint32_t reg;
            		for(i=0;i<5;i++){
            			putchar('0'+i);
            			putchar(':');
            			print_hex((volatile uint32_t)((0x85000000)+i*4), 8);
            			
            			reg = *((volatile uint32_t*)(0x85000000+i*4));
            			putchar(':');
            			print_hex(reg, 4);
            			putchar('\n');
            		}
            		putchar('\n');
            		
            	}
                break;
            case '1':
                GPIO0->OUT ^= 0x00000001;
                break;

            case '2':
                GPIO0->OUT ^= 0x00000002;
                break;

            case '3':
                GPIO0->OUT ^= 0x00000004;
                break;

            case '4':
                GPIO0->OUT ^= 0x00000008;
                break;

            case '5':
                GPIO0->OUT ^= 0x00000010;
                break;

            case '6':
                GPIO0->OUT ^= 0x00000020;
                break;

            default:
                continue;
            }
        }
    }
}

void irqCallback() {

}