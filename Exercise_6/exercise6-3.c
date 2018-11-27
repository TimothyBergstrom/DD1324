// INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exercise6-3.h"

char symbol_chooser();  // Simple way to fetch symbols

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
				//char magic_number[3] = {line[0], line[1], '\0'};  // Will have "P2" in it. Make it into a string
				//printf("%s\n", magic_number);  // Print it (if we want)
			}
			else if(line_count == 1){
				//printf("%s", line);  // # made by...
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
				//int Maxval = atoi(line);
				//printf("%d\n", Maxval);
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
					if((i_scale < 3 && j_scale == 0) || (j_scale == 95 && i_scale > 124)){  // Print condition
						//printf("GREY_LEVELS_SCALED[%d][%d] = %d\n", i_scale, j_scale,
						//GREY_LEVELS_SCALED[i_scale][j_scale]);
					}
				}
			}
		}
		int i_scale = width/SCALE_FACTOR;  // Reuse variable name.
		int j_scale = height/SCALE_FACTOR;
		char GREY_LEVELS_SCALED_IMAGE[i_scale][j_scale];  // Make new for image, which contains chars
		for(int j=0; j < j_scale; ++j){  // Height
			for(int i=0; i < i_scale; ++i){ // Width
				GREY_LEVELS_SCALED_IMAGE[i][j] = symbol_chooser(GREY_LEVELS_SCALED[i][j]); // Choose symbol depending on grey value
			}
		}
		FILE *ptr;
		ptr = fopen("saturn.ascii.txt", "w"); // Make new file where you store the image
		for(int j=0; j < j_scale; ++j){
			for(int i=0; i < i_scale; ++i){ 
				fputc(GREY_LEVELS_SCALED_IMAGE[i][j], ptr);
				//printf("%c", GREY_LEVELS_SCALED_IMAGE[i][j]);
			}
			fputc('\n', ptr);
			//printf("\n");
		}
		fclose(ptr);
		printf("Made file saturn.ascii.txt. Note that opening the file in wordpad or anteckningar does not work! Please use something like notepad++\n");
	}
}

char symbol_chooser(int content){
	if(0 <= content && content < 25){
		return ' ';
	}
	else if(25 <= content && content < 50){
		return '.';
	}
	else if(50 <= content && content < 75){
		return ':';
	}
	else if(75 <= content && content < 100){
		return '-';
	}
	else if(100 <= content && content < 125){
		return '=';
	}
	else if(125 <= content && content < 150){
		return '+';
	}
	else if(150 <= content && content < 175){
		return '*';		
	}
	else if(175 <= content && content < 200){
		return '#';
	}
	else if(200 <= content && content < 225){
		return '&';
	}
	else if(225 <= content && content < 250){
		return '%';
	}
	else if(250 <= content && content < 255){
		return '@';
	}
	return ' '; // Should not reach here
}