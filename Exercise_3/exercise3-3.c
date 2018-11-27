#include <stdio.h>
#include <stdlib.h>  // For atoi


int main(int argc, char** argv){  // argc = argument count, argv = argument vector
	if(argc<2){
		fprintf(stderr, "No input!\n");  // fprintf(stream, what_to_print)
		return -1;
	}
	/* Please note: Some characters seems to break the code, such as !. I have no idea why, probably because they
	are non-ascii character and occupies slightly more than one byte*/
	int output = ' ';  // ' ' does not have a \0, its a char. " " does though
	int counter = 0;
	
	// Calculate length of string
	while(output != '\0'){
		output = argv[1][counter];  // Only considers first input
		if(output != '\0'){  // DO NOT count if output is '\0'
			counter = counter + 1;
		}
	}
	/* Counter is now new length of string	
	Important note: char is basically just an ASCII number, can be considered as such
	OBS: If you add it to a new array, you have to have it +1 in size to allocate \0 character
	and also print it, due to residue memory being printed
	*/
	for(int i = 0; i < counter; i++){
		if(argv[1][i] <= 122 && argv[1][i] >= 97){  // z = 122, a = 97
			argv[1][i] = argv[1][i] - 32; // Z = 90, A = 65, -32 to convert to CAPS
		}
		argv[1][i] = argv[1][i];  // Do nothing if not lower case
	}
	printf("%s\n", argv[1]);
}	