#include <stdio.h>
#include <stdlib.h>

int n;  // This is a global variable, any function can use it
long int fact = 1;  // global variable

void factorial();  // declare the lonely function

int main(){
	//int example;  // This is a local variable
	printf("Factorial n = ");
	scanf("%d", &n);  // Changes memory of n (global) to input
	factorial();  // No input here
	printf("Factorial = %ld\n", fact);
}

void factorial(){
	for (int count = 0; count < n; ++count){
		fact *= n - count;  // Will do n*(n-1)*(n-2)...
	}
}