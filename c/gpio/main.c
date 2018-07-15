#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include "./gpio.h"

int main(int argc, char **argv)
{
	
	// open GPIO26 
	if( !GPIO_open("26") ){
		exit(0);
	};

	// wait 0.1 sec
	usleep(100000);
	
	// set GPIO26 output
	if( !GPIO_setDir("26", "out") ){
		exit(0);
	}
	
	// output "1" to GPIO26
	if( !GPIO_outValue("26", "1") ){
		exit(0);
	}
	
	// wait 3 sec
	usleep(3 * 1000 * 1000);
	
	// output "0" to GPIO26
	if( !GPIO_outValue("26", "0") ){
		exit(0);
	}
	
	// remove GPIO26
	if( GPIO_close("26") ){
		exit(0);
	}
	
	return 0;
}

