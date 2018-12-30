#include<stdio.h>
#include<math.h>

float testFloat(float in1 , float in2){

	return in1*in2;
}

float testSin(float in1){

	return sinf(in1);
}


int main(int argc, char *argv[]){

	float a,b,c;
	
	a = 0.5f * argc;
	b = 0.2f;

	//c = testFloat(a,b);
	c = testSin(a);

	printf("%lf\n",c);

	return 0;
}
