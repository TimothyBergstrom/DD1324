#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <unistd.h>

// Function prototypes
int **arraycreate();  // Tell the compiler "Hey, I will return a pointer to a pointer"
int **arraytranspose();
int **arraymultiply();
void free_memory();  // Void because I dont need to return anything
void arrayfill();
void arraydisplay();

int main(){
	int nrows;	// the number of rows in the array
	int ncolumns;	// the number of columns in the array
	printf("Enter the number of rows followed by the number of columns: ");
	scanf("%d %d", &nrows, &ncolumns);  // & = in the memory of the variables
	printf("You requested a size of %dx%d.\n", nrows, ncolumns);
	int **pointer_array = arraycreate(nrows, ncolumns);  // Gives pointer to pointer matrix where all pointers point to a memory in heap 
	printf("Filling the array with random numbers\n");
	int lower = 1; int upper = 4;  // set lower and upper limit for randomness
	arrayfill(pointer_array, nrows, ncolumns, lower, upper);  // Fill with random numbers
	printf("Displaying array\n");
	arraydisplay(pointer_array, nrows, ncolumns);
	printf("Transposing array\n");
	int **transposed_array = arraytranspose(pointer_array, ncolumns, nrows);  // Gets transposed array back
	printf("Displaying transposed array\n");
	arraydisplay(transposed_array, ncolumns, nrows); 
	printf("Multiplying transposed and original array\n");
	int **result = arraymultiply(pointer_array, transposed_array, nrows, ncolumns);  // Multiplication
	printf("Displaying multiplied array\n");
	arraydisplay(result, nrows);
	free_memory(pointer_array, nrows);
	free_memory(transposed_array, ncolumns);
	free_memory(result, nrows);  // 2:3 x 3:2 --> 2:2 --> means that need to free a 2:2 matrix
	pointer_array = NULL;  // Remove the pointers, to truly clean the memory
	transposed_array = NULL;
	result = NULL;
	return 0;
}

// Function declarations
int **arraycreate(int nrows, int ncolumns){  // Important to have **, since it declares what it returns
	printf("Allocating memory for %dx%d array\n", nrows, ncolumns);
	int *p;  // Makes a pointer to an int
	int pointer_size = sizeof(p);  // IMPORTANT: The size of a pointer depends if 32 bit or 64 bit. This check what system you have
	int **pointer_array = malloc(nrows*pointer_size);  // Pointer to an array of pointers
	for(int i=0; i<nrows; ++i){
		pointer_array[i] = (int*) malloc(ncolumns * sizeof(int));
	}
	return pointer_array;  // Returns a pointer to a pointer
}

int **arraytranspose(int **pointer_array, int ncolumns, int nrows){
	int **transposed_array = arraycreate(ncolumns, nrows);  // transposed array is flipped from normal, i.e 2:3 --> 3:2
	for(int i=0; i<nrows; ++i){
		for(int j=0; j<ncolumns; ++j){
			transposed_array[j][i] = pointer_array[i][j];
		}
	}
	return transposed_array;
}

int **arraymultiply(int **arr1, int **arr2, int r1, int c1){
	printf("Multiplying arrays %dx%d x %d%d\n", r1, c1, c1, r1);
	int dot_product;
	int **result = arraycreate(r1, r1);  // Size of arr * transposed_arr = nrows:nrows (2:3 x 3:2 --> 2:2)
	for(int i=0; i<r1; ++i){
		for(int j=0; j<c1; ++j){
			dot_product = 0;
			for(int k=0; k<r1; k++){
				dot_product += arr1[i][k] * arr2[k][j];  // Could rename i, j and k to something more sensible, but oh well...
			}
			result[i][j] = dot_product;
		}
	}
	return result;
}

void arrayfill(int **pointer_array, int nrows, int ncolumns, int lower, int upper){
	time_t t;  // Without seeding, you get the same number all the time. One way I found out is using time as seed works well
	srand(time(&t));  // Gets seed depending on time
	for(int i=0; i<nrows; ++i){
		for(int j=0; j<ncolumns; ++j){
			pointer_array[i][j] = (rand()%upper)+lower;  // Adds random number in range lower <--> upper
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
	free(pointer_array);  // Also need to free the pointer to the pointer array
	printf("Freed memory\n");
}

