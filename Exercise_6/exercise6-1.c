// INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// MAIN FUNCTION
int main(){
	FILE *ptr;
	ptr = fopen("saturn.ascii.pgm", "r");
	char line[200];
	int width = 640;
	int height = 480;
	if(ptr != NULL){
		// First line is the magic number
		int line_count = 0;
		while(fgets(line, sizeof(line), ptr)){
			if(line_count == 0){
				char magic_number[3] = {line[0], line[1], '\0'};  // Will have "P2" in it. Make it into a string
				printf("%s\n", magic_number);
			}
			else if(line_count == 1){
				printf("%s", line);// Ignore
			}
			else if(line_count == 2){
				for(int i=0; i<200; ++i){
					if(line[i] == ' ' || line[i] == '\t'){
						//int split = i;
						break;
					}
				}
				//int width = 640;
				//int height = 480;
				printf("%d %d\n", width, height);
			}
			else if(line_count == 3){
				int Maxval = atoi(line);
				printf("%d\n", Maxval);
				break;
			}
			line_count++;
		}
		int GREY_LEVELS[width][height];
		int w = 0;
		int h = 0;
		int content;
		for(int i = 0; !feof(ptr); ++i){
			if(w%width == 0 && w != 0){
				w = 0;
				h++;
			}
			fscanf(ptr, "%d", &content);
			GREY_LEVELS[w][h] = content;
			if((w < 3 && h == 0) || (h == 479 && w > 631)){
				printf("GREY_LEVELS[%d][%d] = %d\n", w, h, GREY_LEVELS[w][h]);
			}
			w++;
		}
	}
}
