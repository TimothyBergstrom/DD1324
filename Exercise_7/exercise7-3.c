#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function prototypes
int **arraycreate();  // Tell the compiler "Hey, I will return a pointer to a pointer"
void free_memory();
void arrayfill();
void arraydisplay();

int main(){
	int nrows;	// the number of rows in the array
	int ncolumns;	// the number of columns in the array
	printf("Enter the number of rows followed by the number of columns: ");
	scanf("%d %d", &nrows, &ncolumns);  // & = in the memory of...
	printf("You requested a size of %dx%d.\n", nrows, ncolumns);
	printf("Allocating memory for array\n");
	int **pointer_array = arraycreate(nrows, ncolumns);
	printf("Filling the array with random numbers\n");
	int lower = 1; int upper = 4;  // set lower and upper
	arrayfill(pointer_array, nrows, ncolumns, lower, upper);
	printf("Displaying array\n");
	arraydisplay(pointer_array, nrows, ncolumns);
	free_memory(pointer_array, nrows);
	printf("Freed memory\n");
	pointer_array = NULL;  // Remove the pointer
	return 0;
}

// Function declarations
int **arraycreate(int nrows, int ncolumns){
	int *p;
	int pointer_size = sizeof(p);  // IMPORTANT: The size of a pointer depends if 32 bit or 64 bit. This check what system you have
	int **pointer_array = malloc(nrows*pointer_size);  // Pointer to an array of pointers
	for(int i=0; i<nrows; ++i){
		pointer_array[i] = (int*) malloc(ncolumns * sizeof(int));
	}
	return pointer_array;
}

void arrayfill(int **pointer_array, int nrows, int ncolumns, int lower, int upper){
	time_t t;  // Without seeding, you get the same number all the time. One way I found out is using time as seed works well
	srand(time(&t));
	for(int i=0; i<nrows; ++i){
		for(int j=0; j<ncolumns; ++j){
			pointer_array[i][j] = (rand()%upper)+lower;
		}
	}
}

void arraydisplay(int **pointer_array, int nrows, int ncolumns){
	for(int i=0; i<nrows; ++i){
		for(int j=0; j<ncolumns; ++j){
			printf("%d ", pointer_array[i][j]);
		}
		printf("\n");
	}
}

void free_memory(int **pointer_array, int nrows){
	for(int i=0; i<nrows; i++){
		free(pointer_array[i]);  // Free for each row
	}
	free(pointer_array);  // Also need to free the array itself
}

