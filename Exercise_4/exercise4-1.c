#include <stdio.h>
#include <stdlib.h>  // For atoi

int addition();  // Function declarations
int subtraction();
int multiplication();

int main(int argc, char** argv){  // argc = argument count, argv = argument vector
	if (argc < 4) {  // If no argument when running code
      fprintf(stderr, "Error: you need to add two integers and a operation symbol\n");  // fprintf(stream, what_to_print)
	  fprintf(stderr, "Operation symbols = x, +, -\n");
      fprintf(stderr, "Usage: ./exercise4-1 <int1> <int2> <operation_symbol>\n");
      return -1;  // return 0 --> good, else = bad
    }
    long int n1 = atoi(argv[1]); // Long int can hold -2,147,483,647 to 2,147,483,647, int can only hold -32,767 to 32,767
	long int n2 = atoi(argv[2]);
	char operator = argv[3][0];  // [0] at the end, because it comes as a string. I dont care about \0
	if(operator == 'x'){
		int long result;
		result = multiplication(n1, n2);
		printf("Multiplication: %ld\n", result);
	}
	else if(operator == '+'){	
		int long result;
		result = addition(n1, n2);
		printf("Addition: %ld\n", result);
	}
	else if(operator == '-'){
		int long result;
		result = subtraction(n1, n2);
		printf("Subtraction: %ld\n", result);
	}
	else{
		fprintf(stderr, "Error, you need to enter a valid operation symbol");
		fprintf(stderr, "Operation symbols = x, +, -\n");
	}
}	

int addition(long int a, long int b){  // function prototype
    long int c;
    c = a + b;
    return c;
}

int subtraction(long int a, long int b){
	long int c;
	c = a - b;
	return c;
}

int multiplication(long int a, long int b){
	long int c;
	c = a*b;
	return c;
}