#include <stdio.h>
#include <stdlib.h>

//#include <getopt.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

#include <stdbool.h>

#define IOCTL_ERROR (-1)
#define SPI_MODE_SET (SPI_MODE_SET)
#define SPI_SPEED_SET (500000)
#define SPI_BITS_SET (8)
static int SPI_Device;

bool SPI_write(unsigned char* tx, int txSize)
{
	unsigned char* rx[txSize];

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

bool SSD1331_writeCommand(unsigned char* tx, int txSize)
{

	if( SPI_write(tx, txSize) ){
		return false;
	}

	return true;
}

int main()
{
	SPI_Device = open("/dev/spidev0.0", O_RDWR);

	int ret;
	unsigned char mode = SPI_MODE_SET;
	unsigned char bits = SPI_BITS_SET;
	unsigned int speed = SPI_SPEED_SET;

	// spi mode
	ret = ioctl(SPI_Device, SPI_IOC_WR_MODE, &mode);
	if (ret == IOCTL_ERROR){
		puts("can't set spi mode");
		return;
	}

	// bits per word
	ret = ioctl(SPI_Device, SPI_IOC_WR_BITS_PER_WORD, &bits);
	if (ret == IOCTL_ERROR){
		puts("can't set bits per word");
		return;
	}

	// max speed hz
	ret = ioctl(SPI_Device, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
	if (ret == IOCTL_ERROR){
		puts("can't set max speed hz");
		return;
	}

	printf("spi mode: %d\n", mode);
	printf("bits per word: %d\n", bits);
	printf("max speed: %d Hz (%d KHz)\n", speed, speed/1000);
	
	





}
