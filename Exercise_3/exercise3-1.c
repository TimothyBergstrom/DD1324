#include <stdio.h>
#include <stdlib.h>  // For atoi


int main(int argc, char** argv){  // argc = argument count, argv = argument vector
	if (argc < 2) {  // If no argument when running code
      fprintf(stderr, "foobar requires a integer to run\n");  // fprintf(stream, what_to_print)
      fprintf(stderr, "Usage: ./exercise3-1 integer\n");
      return -1;  // return 0 --> good, else = bad
    }
    int n = atoi(argv[1]);
	
	for(int i = 1; i <= n; i++){
		if(i%5 == 0 && i%3 == 0) {  // || = OR
			printf("foobar\n");
		}
		else if (i%3 == 0) {
			printf("foo\n");
		}
		else if (i%5 == 0) {
			printf("bar\n");
		}
		else {
			printf("%d\n",i);
		}
	}
}	