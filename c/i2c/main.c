#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include <linux/i2c-dev.h> // I2C用インクルード
#include <fcntl.h>
#include <sys/ioctl.h>

#define I2C_DEVICE_NAME		"/dev/i2c-1"
#define I2C_SLAVE_ADDRESS	(0xEE)

int main(int argc, char **argv)
{
	
	int i2c_fd;

	if((i2c_fd = open(I2C_DEVICE_NAME, O_RDWR)) < 0){
		fprintf(stderr,"Faild to open i2c ¥n");
		return 1;
	}
	if (ioctl(i2c_fd, I2C_SLAVE, I2C_SLAVE_ADDRESS) < 0) {
		fprintf(stderr,"Unable to get bus slave access¥n");
		return 1;
	}
	
	__s32 res1 = i2c_smbus_write_byte_data(i2c_fd, 0xF4, 0x2E);
	__s32 res2 = i2c_smbus_read_word_data(i2c_fd, 0xF6);
	if(res < 0){
		fprintf(stderr,"Error i2c_smbus_read_word_data()¥n");
		return 1;
	}
	printf("%x\n",res)
	
	return 0;
}