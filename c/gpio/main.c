#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	int fd = 0;
	{
		// open GPIO
		fd = open("/sys/class/gpio/export", O_WRONLY);
		if (fd < 0) {
			printf("GPIO export open error.\n");
			exit(1);
		}
		// set GPIO 26 pin
		// 第3引数は書き込みデータ数(末尾NULL文字含む)
		write(fd,"26",3);
		close(fd);
	}
	// wait 0.1 sec
	usleep(100000);
	
	// set GPIO26 output
	fd = open("/sys/class/gpio/gpio26/direction", O_WRONLY);
	if (fd < 0) {
		printf("GPIO26 direction open error.\n");
		exit(1);
	}
	write(fd,"out",4);
	close(fd);
	
	// output "1" to GPIO26
	fd = open("/sys/class/gpio/gpio26/value", O_WRONLY);
	if (fd < 0) {
		printf("GPIO26 value open error.\n");
		exit(1);
	}
	write(fd,"1",2);
	
	// wait 3 sec
	usleep(3 * 1000 * 1000);
	
	// output "0" to GPIO26
	write(fd,"0",2);
	close(fd);
	
	// remove GPIO26
	fd = open("/sys/class/gpio/unexport", O_WRONLY);
	if (fd < 0) {
		printf("GPIO26 unexport open error.\n");
		exit(1);
	}
	write(fd,"26",3);

	// close GPIO
	close(fd);
	
	return 0;
}

