#include <stdio.h>
#include <stdlib.h>

int main()
{
	int nrows;	// the number of rows in the array
	int ncolumns;	// the number of columns in the array

	printf("Enter the number of rows followed by the number of columns: ");
	scanf("%d %d", &nrows, &ncolumns);  // & = in the memory of...
	printf("You requested a size of %dx%d.\n", nrows, ncolumns);
	return 0;
}

