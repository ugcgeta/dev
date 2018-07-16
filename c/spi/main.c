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

bool SSD1331_writeData(unsigned char* tx, int txSize)
{

	GPIO_outValue(Port_DC, "1");
	if( SPI_write(tx, txSize) ){
		return false;
	}

	return true;
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





	SSD1331_close("24", "25");
	return true;
}
