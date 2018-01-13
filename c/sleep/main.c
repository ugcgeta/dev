#include <stdio.h>
#include <sys/time.h>

void main()
{

	struct timespec ts;
	struct timeval t1, t2;

	ts.tv_sec = 0;
	ts.tv_nsec = 200000000;

	while(1){
		gettimeofday(&t1, NULL);
		
		nanosleep(&ts, NULL);
		
		gettimeofday(&t2, NULL);
		printf("time = %lf\n", (t2.tv_sec - t1.tv_sec) + (t2.tv_usec - t1.tv_usec)*1.0E-6);
	}


}
