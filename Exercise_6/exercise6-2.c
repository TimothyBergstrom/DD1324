// INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exercise6-2.h"

// MAIN FUNCTION
int main(){
	FILE *ptr;  // Pointer to file
	ptr = fopen("saturn.ascii.pgm", "r");
	char line[200];
	int width = 640;
	int height = 480;
	if(ptr != NULL){  // Check if we can open file
		int line_count = 0;  // Count lines, clear the first 4
		while(fgets(line, sizeof(line), ptr)){
			if(line_count == 0){ 		// First line is the magic number
				char magic_number[3] = {line[0], line[1], '\0'};  // Will have "P2" in it. Make it into a string
				printf("%s\n", magic_number);  // Print it (if we want)
			}
			else if(line_count == 1){
				printf("%s", line);  // # made by...
			}
			else if(line_count == 2){
				/*  // Old code, tried to calculate width and height.
 				for(int i=0; i<200; ++i){
					if(line[i] == ' ' || line[i] == '\t'){
						//int split = i;
						break;
					}
				}
				*/
				//int width = 640;
				//int height = 480;
				//printf("%d %d\n", width, height);
			}
			else if(line_count == 3){
				int Maxval = atoi(line);
				printf("%d\n", Maxval);
				break;  // All lines after this contains our grey values
			}
			line_count++;
		}
		int GREY_LEVELS[width][height];  // Make matrix
		int w = 0;  // Count width rows
		int h = 0;  // Count height
		int content;  // Memory block for contents in the array
		for(int i = 0; !feof(ptr); ++i){  // Keep going until you reach end of file, we started at line 4
			if(w%width == 0 && w != 0){
				w = 0;  // reset width
				h++;  // add one to height count
			}
			fscanf(ptr, "%d", &content);  // Scan the line, convert any string to int if found. Write information to content
			GREY_LEVELS[w][h] = content;  // Store the found thing in array
			if((w < 3 && h == 0) || (h == 479 && w > 636)){  // Print if condition is true
				//printf("GREY_LEVELS[%d][%d] = %d\n", w, h, content);
			}
			w++;  // Count width
		}
		fclose(ptr);
		
		// SCALE
		int GREY_LEVELS_SCALED[width/SCALE_FACTOR][height/SCALE_FACTOR];  // Make new array, which is scaled
		for(int j=0; j < height; ++j){  // Height
			for(int i=0; i < width; ++i){  // Width
				if(i%SCALE_FACTOR == 0 && j%SCALE_FACTOR == 0){  // If scale factor = 5, take every fifth column on every fifth row
					int i_scale = i/SCALE_FACTOR;  // Convert index to scaled index
					int j_scale = j/SCALE_FACTOR;
					GREY_LEVELS_SCALED[i_scale][j_scale] = GREY_LEVELS[i][j]; // Store it in scaled
					if((i_scale < 8 && j_scale == 0) || (j_scale == 95 && i_scale > 115)){  // Print condition
						printf("GREY_LEVELS_SCALED[%d][%d] = %d\n", i_scale, j_scale,
						GREY_LEVELS_SCALED[i_scale][j_scale]);
					}
				}
			}
		}
	}
}