#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "./gpio.h"
bool GPIO_open(char* portNum)
{
	int fd = 0;

	// open GPIO
	fd = open("/sys/class/gpio/export", O_WRONLY);
	if (fd < 0) {
		printf("GPIO export open error.\n");
		return false;
	}
	// set GPIO  pin
	// 第3引数は書き込みデータ数(末尾NULL文字含む)
	write(fd, portNum, strlen(portNum)+1);
	close(fd);

	return true;
}

bool GPIO_setDir(char* portNum, char* inout)
{
	int fd = 0;
	char dirStr[40];

	sprintf(dirStr, "/sys/class/gpio/gpio%s/direction", portNum);
	// set GPIO output
	fd = open(dirStr, O_WRONLY);
	if (fd < 0) {
		printf("GPIO direction open error.\n");
		printf("%s\n",dirStr);
		return false;
	}
	write(fd, inout, strlen(inout)+1);
	close(fd);
	
	return true;
}

bool GPIO_outValue(char* portNum, char* portValue)
{
	int fd = 0;
	char dirStr[40];

	sprintf(dirStr, "/sys/class/gpio/gpio%s/value", portNum);
	// output to GPIO
	fd = open(dirStr, O_WRONLY);
	if (fd < 0) {
		printf("GPIO value open error.\n");
		printf("%s\n", dirStr);
		return false;
	}

	write(fd, portValue, strlen(portValue)+1);
	close(fd);
	
	return true;
}

bool GPIO_close(char* portNum)
{
	int fd = 0;

	// remove GPIO
	fd = open("/sys/class/gpio/unexport", O_WRONLY);
	if (fd < 0) {
		printf("GPIO unexport open error.\n");
		return false;
	}
	write(fd, portNum, strlen(portNum)+1);
	close(fd);
	
	return true;
}

