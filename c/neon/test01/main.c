#include<stdio.h>

float testFloat(float in1 , float in2){

	return in1*in2;
}

int main(){

	float a,b,c;
	
	a = 0.5f;
	b = 0.2f;

	c = testFloat(a,b);

	printf("%lf\n",c);

	return 0;
}
