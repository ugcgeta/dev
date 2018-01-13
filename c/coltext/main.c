#include <stdio.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

void putColor(unsigned int value)
{
	const unsigned int UNDER_LIMIT=20 * 4;
	const unsigned int UPPER_LIMIT=30 * 4;
	const unsigned int BASE_CODE=235;
	
	unsigned int limitValue;
	unsigned int colorCode;

	limitValue = MIN( MAX(value, UNDER_LIMIT), UPPER_LIMIT);
	colorCode = ((limitValue - UNDER_LIMIT)>>1) + BASE_CODE;
	
	printf("\e[48;5;%dm  \e[m",colorCode);

}
void main()
{

	//printf("\e[31m%s\n\e[m","RED");
	
	int i,j;
	puts("  0 1 2 3 4 5 6 7");
	for(i=0;i<8;i++){
		printf("%d",i);
		for(j=0;j<8;j++){

			putColor((i+j+18)*4);
		
		}
		putchar('\n');
	}

	for(i=18*2;i<32*2;i++){
	//	putColor(i*2);
	}


}
