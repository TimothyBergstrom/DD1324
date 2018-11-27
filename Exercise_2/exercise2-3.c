#include <stdio.h>
#define M_PI 3.14159265358979323846  // Defines what pi is, so I can use it
 	
int main()
{ 
	{  // Creates small scope, variables only exist here
	int x=22, y=7;
	float pi;
	pi=x/y;  // No type casting
	printf("%f\n", pi);
	}
	
	{
	int x=22, y=7;
	double pi;
	pi=(double)x/(double)y; // Typecasting here, setting them to double
	/*Is there a way to print how many decimals there are in a variable, eg
	3.14 would just print 3.14, 3.141592 would print only 3.141592 etc... */
	printf("%.50f\n", pi);  // Print 50 decimals.
	printf("Diff = %.10f from real pi\n", (M_PI - pi));  // Compare "Real" pi with calculated pi
	}
	
	{
	int x=355, y=113;
	double pi;
	pi=(double)x/(double)y;
	printf("%.50f\n", pi);
	printf("Diff = %.10f from real pi\n", (M_PI - pi));
	}
	
	// x=355 and y=113 --> is better
	
	return 0;
}
