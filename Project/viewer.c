// INCLUDES
#include "viewer.h"

// MAIN FUNCTION
int main(int argc, char** argv){
	if (argc < 3) {  // If no argument when running code
		fprintf(stderr, "%sERROR: Incorrect input detected %s\n", RED, RESET);
		fprintf(stderr,"%sUsage: ./viewer <name_of_zipped_pgm_file> <SCALE_FACTOR>%s\n", RED, RESET);
		return -1;  // return 0 --> good
    }
	else if(strstr(argv[1], ".zip") == NULL){
		fprintf(stderr, "%sERROR: Non-zipped file added to input %s\n", RED, RESET);
		fprintf(stderr,"%sUsage: ./viewer <name_of_zipped_pgm_file> <SCALE_FACTOR>%s\n", RED, RESET);
		return -1;
	}
	
	FILE *file_ptr;  // Pointer to file
	char filepath[100] = "";  // buffer for concatenating strings, need to define them as empty to stop undefined behavior
	strcat(filepath, "pgm_images/");  // file folder
	strcat(filepath, argv[1]);  // file name, argv[0] --> ./viewer
	int SCALE_FACTOR = atoi(argv[2]);
	file_ptr = fopen(filepath, "r");  // try to open file in read mode
	if(file_ptr != NULL){  // Check if we can open file
		printf("%sOpened %s successfully%s\n", BLUE, filepath, RESET);
		int width;
		int height;
		int TOTAL_NUMBER_OF_COMPRESSED_SEQUENCES;
		read_zip_pgm(file_ptr, &height, &width, &TOTAL_NUMBER_OF_COMPRESSED_SEQUENCES);
		printf("%sScaling factor: %d%s\n", MAGENTA, SCALE_FACTOR, RESET);
		printf("%sImage width: %d%s\n", MAGENTA, width, RESET);
		printf("%sImage height: %d%s\n", MAGENTA, height, RESET);
		int **decoded_image = arraycreate(height, width);  // Problem: If arraycreate is called within a function, it is delocated after the function run ends
		decoded_image = decode(file_ptr, height, width, TOTAL_NUMBER_OF_COMPRESSED_SEQUENCES, decoded_image);
		
		int height_scaled = height/SCALE_FACTOR;
		int width_scaled = width/SCALE_FACTOR;
		int **scaled_image = arraycreate(height_scaled, width_scaled); 
		scaled_image = scale_image(height, width, SCALE_FACTOR,  decoded_image, scaled_image);
		arraydisplay(scaled_image, height_scaled, width_scaled);
		
		// Handle memory and file pointer
		fclose(file_ptr);
		free_memory(decoded_image, height);	
		free_memory(scaled_image, height_scaled);
	}
	else{
	  fprintf(stderr, "%sERROR: The file %s was not found %s\n", RED, argv[1], RESET);
	  fprintf(stderr, "%sEither the name of the file was was misspelled or the file is not in the pgm_images folder %s\n", RED, RESET);
      fprintf(stderr,"%sUsage: ./viewer <name_of_zipped_pgm_file> <SCALE_FACTOR>%s\n", RED, RESET);
      return -1;  // return 0 --> good
	}
}

void read_zip_pgm(FILE *file_ptr, int *height_pointer, int *width_pointer, int *TOTAL_NUMBER_OF_COMPRESSED_SEQUENCES_pointer){  // Need to return multiple, so I'll just change the value on memory of the pointer
	char line[200];  // Buffer line
	int line_count = 0;  // Count lines, clear the first 3
	while(fgets(line, sizeof(line), file_ptr)){
		if(line_count == 0){	// First line is the width
			sscanf(line, "%d", width_pointer);  // & means "store in memory of...", while sscanf scans a line
		}
		else if(line_count == 1){  // Second line is the height
			sscanf(line, "%d", height_pointer);
		}
		else if(line_count == 2){
			sscanf(line, "%d", TOTAL_NUMBER_OF_COMPRESSED_SEQUENCES_pointer);  // & means "store in memory of...", while sscanf scans a line
			break;
		}
		line_count++;
	}
	return;
}

int **decode(FILE *file_ptr, int height, int width, int TOTAL_NUMBER_OF_COMPRESSED_SEQUENCES, int **pointer_array){
	// file_prt is now on line 3
	int **compressed_image = arraycreate(1, TOTAL_NUMBER_OF_COMPRESSED_SEQUENCES*2);  // We have no idea how long the compression is, so lets make a vector
	char c;
	int index_compression_image = 0;
	int index_store_char = 0;
	char store_char[100] = ""; // This can handle very large compressions
	while((c = fgetc(file_ptr)) != EOF){  // We have no idea how long the line is, but we know that each char has a certain size
		if(c == '\0' || c == '\n'){  // Is at end
			break;
		}
		else if(c == ' '){
			compressed_image[0][index_compression_image] = atoi(store_char);
			index_store_char = 0;  // Reset
			memset(&store_char[0], 0, sizeof(store_char));  // I want to fully clear the string
			index_compression_image++;  // Add one
		}
		else{
			store_char[index_store_char] = c;
			index_store_char++;
		}
	}
	int h = 0;  // Count height
	int w = 0;  // Count width
	int counter;  // How many of value
	int value;
	for(int i=0; i<TOTAL_NUMBER_OF_COMPRESSED_SEQUENCES*2 + 1; i = i + 2){ // Next index should start 2 further
		counter = compressed_image[0][i];  // First is length(N)
		value = compressed_image[0][i+1];  // Next comes N
		for(int j=0; j<counter; j++){
			if(w%width == 0){
				w = 0;
				h++;
				if(h >= height){
					break;  // End of file
				}
			}
			pointer_array[h][w] = value;
			w++;
		}
	}
	return pointer_array;
}

int **scale_image(int height, int width, int SCALE_FACTOR, int **pointer_array, int **scale_pointer_array){
	for(int i=0; i < height; ++i){  // Height
		for(int j=0; j < width; ++j){  // Width
			if(i%SCALE_FACTOR == 0 && j%SCALE_FACTOR == 0){  // Ex: if scale factor = 5, take every fifth column on every fifth row
				int i_scale = i/SCALE_FACTOR;  // Convert index to scaled index
				int j_scale = j/SCALE_FACTOR;
				if(i_scale > height/SCALE_FACTOR - 1 || j_scale > width/SCALE_FACTOR - 1){  // Quick check it it is out of bounds, can happen with odd SCALE_FACTOR
					break;
				}
				scale_pointer_array[i_scale][j_scale] = pointer_array[i][j]; // Store it in scaled
				}
		}
	}
	int i_scale = height/SCALE_FACTOR;  // Reuse variable names.
	int j_scale = width/SCALE_FACTOR;
	for(int i=0; i < i_scale; ++i){  // Height
		for(int j=0; j < j_scale; ++j){ // Width
			// NOTE: scale_pointer_array has size int, while it is replaced by char. No need to create a new char array
			scale_pointer_array[i][j] = symbol_chooser(scale_pointer_array[i][j]); // Choose symbol depending on grey value
		}
	}	
	return scale_pointer_array;
}

void arraydisplay(int **pointer_array, int height, int width){	
	for(int i=0; i<height; ++i){
		for(int j=0; j<width; ++j){
			printf("%c", pointer_array[i][j]);  // Changed this function to output chars instead
		}
		printf("\n");
	}
	
	// OPTIONAL: Stores output to txt file
	FILE *file_ptr;
	file_ptr = fopen("output.txt", "w");
	for(int i=0; i<height; ++i){
		for(int j=0; j<width; ++j){
			fputc(pointer_array[i][j], file_ptr);
		}
		fputc('\n', file_ptr);
	}
	fclose(file_ptr);
	printf("Stored output to output.txt\n");
}

int **arraycreate(int height, int width){  // Important to have **, since it declares what it returns
	printf("%sAllocating memory for a %d x %d array %s\n", BLUE, height, width, RESET);
	int *p;  // Makes a pointer to an int
	int pointer_size = sizeof(p);  // IMPORTANT: The size of a pointer depends if 32 bit or 64 bit. This check what system you have
	int **pointer_array = malloc(height*pointer_size);  // Pointer to an array of pointers
	for(int i=0; i<height; ++i){
		pointer_array[i] = (int*) malloc(width * sizeof(int));
	}
	return pointer_array;  // Returns a pointer to a pointer
}

char symbol_chooser(int content){
  char classes[11] = {' ', '.', ':', '-', '=', '+', '*', '#', '&', '%', '@'}; //Classes of ascii symbols
  int interval = 25; //The range interval is 25
  int index = content/interval;  // Not float, so will round to closest natural number
  if(index > 10 || index < 0){  // Quick check, if the values are larger or smaller than 0 to 255
	  return ' ';
  }
  else{
	  return classes[index];
  }
}

void free_memory(int **pointer_array, int height){
	for(int i=0; i<height; i++){
		free(pointer_array[i]);  // Free for each row
	}
	free(pointer_array);  // Also need to free the pointer to the pointer array
	printf("Freed memory\n");
}