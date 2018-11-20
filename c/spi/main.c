#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include <getopt.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

#include <stdbool.h>
#include "./gpio.h"

#define IOCTL_ERROR (-1)
#define SPI_MODE_SET (SPI_MODE_3)
#define SPI_SPEED_SET (500000)
#define SPI_BITS_SET (8)
static int SPI_Device;
static char Port_DC[3];

bool SPI_init()
{

	int ret;
	unsigned char mode = SPI_MODE_SET;
	unsigned char bits = SPI_BITS_SET;
	unsigned int speed = SPI_SPEED_SET;
	
	// spi open
	SPI_Device = open("/dev/spidev0.0", O_RDWR);
	
	// spi mode
	ret = ioctl(SPI_Device, SPI_IOC_WR_MODE, &mode);
	if (ret == IOCTL_ERROR){
		puts("can't set spi mode");
		return false;
	}

	// bits per word
	ret = ioctl(SPI_Device, SPI_IOC_WR_BITS_PER_WORD, &bits);
	if (ret == IOCTL_ERROR){
		puts("can't set bits per word");
		return false;
	}

	// max speed hz
	ret = ioctl(SPI_Device, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
	if (ret == IOCTL_ERROR){
		puts("can't set max speed hz");
		return false;
	}

	printf("spi mode: %d\n", mode);
	printf("bits per word: %d\n", bits);
	printf("max speed: %d Hz (%d KHz)\n", speed, speed/1000);
	
	return true;
}


bool SPI_write(unsigned char* tx, int txSize)
{
	unsigned char* rx[txSize];
	int ret;

	struct spi_ioc_transfer tr = {
		.tx_buf = (unsigned long)tx,
		.rx_buf = (unsigned long)rx,
		.len = txSize,
		.delay_usecs = 0,
		.speed_hz = SPI_SPEED_SET,
		.bits_per_word = SPI_BITS_SET,
	};

	ret = ioctl(SPI_Device, SPI_IOC_MESSAGE(1), &tr);
	if (ret < 1){
		puts("can't send spi message");
		return false;
	}

	return true;

}

bool SSD1331_init(char* portRst, char* portDC)
{
	
	// SPI open
	SPI_init();
	
	// GPIO set
	// open GPIO Reset
	if( !GPIO_open(portRst) ){
		return false;
	};

	// wait 0.1 sec
	usleep(100000);
	
	// set GPIO output
	if( !GPIO_setDir(portRst, "out") ){
		return false;
	}
	
	// output "1" to GPIO
	if( !GPIO_outValue(portRst, "1") ){
		return false;
	}
	
	// open GPIO Data/Command
	if( !GPIO_open(portDC) ){
		return false;
	};

	// wait 0.1 sec
	usleep(100000);
	
	// set GPIO output
	if( !GPIO_setDir(portDC, "out") ){
		return false;
	}
	
	// output "1" to GPIO
	if( !GPIO_outValue(portDC, "1") ){
		return false;
	}

	strcpy(Port_DC, portDC);
	
	// HW Reset
	GPIO_outValue(portRst, "0");

	// wait 1 sec
	usleep(1000000);

	GPIO_outValue(portRst, "1");
	
	return true;
}

bool SSD1331_writeCommand(unsigned char* tx, int txSize)
{

	GPIO_outValue(Port_DC, "0");
	if( SPI_write(tx, txSize) ){
		return false;
	}

	return true;
}

bool SSD1331_writeOneCommand(unsigned char tx)
{
	
	return SSD1331_writeCommand(&tx, 1);
}

bool SSD1331_writeData(unsigned char* tx, int txSize)
{

	GPIO_outValue(Port_DC, "1");
	if( SPI_write(tx, txSize) ){
		return false;
	}

	return true;
}
bool SSD1331_writeOneData(unsigned char tx)
{
	
	return SSD1331_writeData(&tx, 1);
}
bool SSD1331_close(char* portRst, char* portDC)
{
	GPIO_close(portRst);
	GPIO_close(portDC);
	
	close(SPI_Device);

	return true;
}

int main()
{
	SSD1331_init("24", "25");

	SSD1331_writeOneCommand(0xAE); //Set Display Off
	SSD1331_writeOneCommand(0xA0); //Remap & Color Depth setting　
	SSD1331_writeOneCommand(0x32); //A[7:6] = 00; 256 color. A[7:6] = 01; 65k color format
	SSD1331_writeOneCommand(0xA1); //Set Display Start Line
	SSD1331_writeOneCommand(0x00);
	SSD1331_writeOneCommand(0xA2); //Set Display Offset
	SSD1331_writeOneCommand(0x00);
	SSD1331_writeOneCommand(0xA4); //Set Display Mode (Normal)
	SSD1331_writeOneCommand(0xA8); //Set Multiplex Ratio
	SSD1331_writeOneCommand(63); //15-63
	SSD1331_writeOneCommand(0xAD); //Set Master Configration
	SSD1331_writeOneCommand(0x8E); //a[0]=0 Select external Vcc supply, a[0]=1 Reserved(reset)
	SSD1331_writeOneCommand(0xB0); //Power Save Mode
	SSD1331_writeOneCommand(0x1A); //0x1A Enable power save mode. 0x00 Disable
	SSD1331_writeOneCommand(0xB1); //Phase 1 and 2 period adjustment
	SSD1331_writeOneCommand(0x74);
	SSD1331_writeOneCommand(0xB3); //Display Clock DIV
	SSD1331_writeOneCommand(0xF0);
	SSD1331_writeOneCommand(0x8A); //Pre Charge A
	SSD1331_writeOneCommand(0x81);
	SSD1331_writeOneCommand(0x8B); //Pre Charge B
	SSD1331_writeOneCommand(0x82);
	SSD1331_writeOneCommand(0x8C); //Pre Charge C
	SSD1331_writeOneCommand(0x83);
	SSD1331_writeOneCommand(0xBB); //Set Pre-charge level
	SSD1331_writeOneCommand(0x3A);
	SSD1331_writeOneCommand(0xBE); //Set VcomH
	SSD1331_writeOneCommand(0x3E);
	SSD1331_writeOneCommand(0x87); //Set Master Current Control
	SSD1331_writeOneCommand(0x06);
	SSD1331_writeOneCommand(0x15); //Set Column Address
	SSD1331_writeOneCommand(0x00);
	SSD1331_writeOneCommand(95);
	SSD1331_writeOneCommand(0x75); //Set Row Address
	SSD1331_writeOneCommand(0x00);
	SSD1331_writeOneCommand(63);
	SSD1331_writeOneCommand(0x81); //Set Contrast for Color A
	SSD1331_writeOneCommand(0xFF);
	SSD1331_writeOneCommand(0x82); //Set Contrast for Color B
	SSD1331_writeOneCommand(0xFF);
	SSD1331_writeOneCommand(0x83); //Set Contrast for Color C
	SSD1331_writeOneCommand(0xFF);
	SSD1331_writeOneCommand(0xAF); //Set Display On
	usleep(200000); //0xAFコマンド後最低100ms必要


	{
		int i, j;
		unsigned char R, G, B, Dot1, Dot2;
		 

		 for(j=0; j<64; j++){ //画面黒塗りつぶし
			for(i=0; i<96; i++){
				SSD1331_writeOneData(0);
			}
		 }

		 R = 7; G = 0; B = 0; //256 color : R (0-7), G (0-7), B (0-3) 
		 Dot1 = (R << 5) | (G << 2) | B;
		  
		  R = 0; G = 0; B = 3; //256 color : R (0-7), G (0-7), B (0-3) 
		  Dot2 = (R << 5) | (G << 2) | B;
		   
		   for(j=0; j<64; j++){
			for(i=0; i<96; i++){
				if(j<8 && i<16) {
					SSD1331_writeOneData(Dot1);
				}else{
					SSD1331_writeOneData(Dot2);
				}
			}
		   }
	}

	usleep(20000000); //0xAFコマンド後最低100ms必要

	SSD1331_close("24", "25");
	return true;
}
