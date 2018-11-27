#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){  // argc = argument count, argv = argument vector
	printf("argc = %d \n", argc);
	int counter;
	char output;
	for(int i = 0; i < argc; i++){
		printf("argv[%i] = %s \n", i, argv[i]);
		counter = 0;  // Reset counter
		output = ' ';  // Reset output
		while(output != '\0') {  // all strings ends with \0
			output = argv[i][counter];
			if(output != '\0'){  // DO NOT count if output is '\0'
				counter = counter + 1;
			}
		}
		printf("length = %d\n", counter);
	}
}	