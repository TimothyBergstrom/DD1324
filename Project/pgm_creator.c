#include <stdio.h>
#include <stdlib.h>

int main(){
	FILE *file_ptr;  // Pointer to file
	file_ptr = fopen("pgm_images/worst_compression.pgm", "w");
	for(int i = 0; i < 256; i++){
		for(int j = 0; j < 256; j++){
			if(j%2 == 0){	
				fputc('1', file_ptr);
			}
			else{
				fputc('0', file_ptr);
			}
			fputc(' ', file_ptr);
		}
		fputc('\n', file_ptr);
	}
	fclose(file_ptr);
}