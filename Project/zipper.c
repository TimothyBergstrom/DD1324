#include "zipper.h"

int main(int argc, char** argv){
    if (argc < 2) {  // If no argument when running code
		fprintf(stderr, "%sERROR: No input detected %s\n", RED, RESET);
		fprintf(stderr,"%sUsage: ./zipper <name_of_pgm_file> %s\n", RED, RESET);
		return -1;  // return 0 --> good
    }
	else if(strstr(argv[1], ".pgm") == NULL){
		fprintf(stderr, "%sERROR: Non-pgm file added to input %s\n", RED, RESET);
		fprintf(stderr,"%sUsage: ./viewer <name_of_pgm_file>%s\n", RED, RESET);
		return -1;
	}
	
	FILE *file_ptr;  // Pointer to file
	char filepath[100] = "";  // buffer for concatenating strings, need to define them as empty to stop undefined behavior
	strcat(filepath, "pgm_images/");  // file folder
	strcat(filepath, argv[1]);  // file name, argv[0] --> ./zipper
	file_ptr = fopen(filepath, "r");  // try to open file in read mode
	if(file_ptr != NULL){  // Check if we can open file
		printf("%sOpened %s successfully %s\n", BLUE, filepath, RESET);
		// Declare variables to use for extracting data
		int width;
		int height;
		
		// Functions to extract data
		pgm_info(file_ptr, &width, &height);
		int **grey_values = arraycreate(height, width);  // Gives pointer to pointer matrix where all pointers point to a memory in heap
		arrayfill(grey_values, height, width, file_ptr);  // grey_values[height][width] = [nrows][ncolumns]
		int TOTAL_NUMBER_OF_COMPRESSED_SEQUENCES = calculate_compression(grey_values, height, width);
		int **compressed_image = compress(grey_values, height, width, TOTAL_NUMBER_OF_COMPRESSED_SEQUENCES);
		
		// Write to file
		write_to_file(filepath, width, height, TOTAL_NUMBER_OF_COMPRESSED_SEQUENCES, compressed_image);		
				
		// Handle memory when done
		free_memory(grey_values, height);
		free_memory(compressed_image, 1);  // Only 1, since it is a pointer to a pointer of a vector
		grey_values = NULL;  // Good measure to clear all pointers after freeing memory
		compressed_image = NULL;
		return 0;  // Return 0, since everything went well
	}
	else{
	  fprintf(stderr, "%sERROR: The file %s was not found %s\n", RED, argv[1], RESET);
	  fprintf(stderr, "%sEither the name of the file was was misspelled or the file is not in the pgm_images folder %s\n", RED, RESET);
	  fprintf(stderr, "%sUsage: ./zipper <name_of_pgm_file> %s\n", RED, RESET);
      return -1;  // return 0 --> good
	}
}

// Function declarations
void pgm_info(FILE *file_ptr, int *width_pointer, int *height_pointer){
	char line[200];  // Buffer line
	int line_count = 0;  // Count lines, clear the first 4
	while(fgets(line, sizeof(line), file_ptr)){
		if(line_count == 0){	// First line is the magic number
			// Ignore magic number, could extract with: char magic_number[3] = {line[0], line[1], '\0'};
		}
		else if(line_count == 1){
			// Ignore author line
		}
		else if(line_count == 2){
			sscanf(line, "%d %d", width_pointer, height_pointer);  //while sscanf scans a line
		}
		else if(line_count == 3){
			// Ignore Maxval, could extract with: int Maxval = atoi(line);
			break;  // All other lines after this contains our grey values, break loop
		}
		line_count++;
	}
	return;
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

int calculate_compression(int **pointer_array, int height, int width){
	int TOTAL_NUMBER_OF_COMPRESSED_SEQUENCES = 0;
	int value = pointer_array[0][0];  // Int in sequence
	// Calculate TOTAL_NUMBER_OF_COMPRESSED_SEQUENCES first
	for(int i=0; i<height; ++i){
		for(int j=0; j<width; ++j){
			if(pointer_array[i][j] == value){ 	
				// Pass
			}
			else {
				TOTAL_NUMBER_OF_COMPRESSED_SEQUENCES++;
				value = pointer_array[i][j];
			}
		}
	}
	TOTAL_NUMBER_OF_COMPRESSED_SEQUENCES++;  // +1 for last value in array
	return TOTAL_NUMBER_OF_COMPRESSED_SEQUENCES;
}

int **compress(int **pointer_array, int height, int width, int TOTAL_NUMBER_OF_COMPRESSED_SEQUENCES){
	printf("%sCompressing image %s\n", BLUE, RESET);
	int *p;  // Makes a pointer to an int
	int pointer_size = sizeof(p);  // IMPORTANT: The size of a pointer depends if 32 bit or 64 bit. This check what system you have
	int **compressed_image = malloc(pointer_size);  // Pointer to an array of pointers, only 1 of them due to it will only be a vector and to be compatible with the free function
	compressed_image[0] = (int*) malloc(TOTAL_NUMBER_OF_COMPRESSED_SEQUENCES * 2 * sizeof(int));  // times two, since length(N) and N
	
	// RLE compress
	int counter = 0;  // Container for length of sequence
	int value = pointer_array[0][0];  // Int in sequence
	int index_of_compressed = 0;
	for(int i=0; i<height; ++i){
		for(int j=0; j<width; ++j){
			if(pointer_array[i][j] == value){ 	
				counter++;
			}
			else {
				compressed_image[0][index_of_compressed] = counter;  // First is length(N)
				compressed_image[0][index_of_compressed+1] = value;  // Next comes N
				index_of_compressed = index_of_compressed + 2;  // Next index should start 2 further
				
				// reset
				value = pointer_array[i][j];
				counter = 1;  // 1 here, because first run it will start at 0,0
			}
		}
	}
	// Add last value in array
	compressed_image[0][index_of_compressed] = counter;  // First is length(N)
	compressed_image[0][index_of_compressed+1] = value;  // Next comes N
	
	// Done
	return compressed_image;
}

void arrayfill(int **grey_values, int height, int width, FILE *file_ptr){
	int w = 0;  // Count width (columns)
	int h = 0;  // Count height (rows)
	int content;  // Memory block for contents in the array
	for(int i = 0; !feof(file_ptr); ++i){  // Keep going until you reach end of file, we started at line 4 from the pointer
		if(w%width == 0 && w != 0){
			w = 0;  // reset width
			h++;  // add one to height count
			if(h == height){  // end of file
				break;
			}
		}
		fscanf(file_ptr, "%d", &content);  // Scan the line, convert any string to int if found. Write information to content
		grey_values[h][w] = content;  // Store the found thing in array
		w++;  // Count width
	}
	fclose(file_ptr);  // Close files
}

void write_to_file(char filepath[100], int width, int height, int TOTAL_NUMBER_OF_COMPRESSED_SEQUENCES, int **compressed_image){
	char filepath_compress[100] = "";  // I do this, since I want to keep the filepath for the uncompressed file, need to define them as empty to stop undefined behavior;
	strcat(filepath_compress, filepath);  // Add filepath to filepath_compress
	strcat(filepath_compress, ".zip");  // filepath + ".zip"
	FILE *file_ptr;
	file_ptr = fopen(filepath_compress, "w");  // try to open file in read mode
	if(file_ptr != NULL){  // Check if we can open file
		fprintf(file_ptr, "%d\n", width);  // Width
		fprintf(file_ptr, "%d\n", height);  // Height
		fprintf(file_ptr, "%d\n", TOTAL_NUMBER_OF_COMPRESSED_SEQUENCES);  // TOTAL_NUMBER_OF_COMPRESSED_SEQUENCES
		for(int i=0; i < TOTAL_NUMBER_OF_COMPRESSED_SEQUENCES*2; ++i){
			fprintf(file_ptr, "%d ", compressed_image[0][i]); // Space between each value
		}
		
		// Compression level calculation
		/*
		Normal pmg: "N + blankspace" for each pixel  <-- 2 (note that some pixels have multiple chars, ex 255)
		Compressed pmg: "len(N) + blankspace + N + blankspace" for each pixel <-- 4 per pixel (note that len(N) can be multiple chars)
		Due to this problem, it is difficult to calculate compression levels. Its better to just compare file sizes
		*/
		
		fclose(file_ptr);  // Close file, before doing anything
		file_ptr = fopen(filepath, "r");  // try to open file in read mode		
		fseek(file_ptr, 0, SEEK_END); // seek to end of file which is already opened, float because large size and need to use float for calculation
		float size_pgm = ftell(file_ptr);
		fclose(file_ptr);  // Close file
		
		fopen(filepath_compress, "r");  // Reuse file_ptr for opening zip
		fseek(file_ptr, 0, SEEK_END);  // Go to end and get size
		float size_compress = ftell(file_ptr);
		fclose(file_ptr);  // Close file

		float compression_rate = size_pgm / size_compress;
		printf("%sCompression rate: %.2f %s\n", MAGENTA, compression_rate, RESET);
		float file_size_difference = 100 * size_compress / size_pgm;
		printf("%sFile size difference: .zip file is %.2f percent of original file size %s\n", MAGENTA, file_size_difference, RESET);
	}
	else {
	  fprintf(stderr, "%sERROR: Couldn't write zipped file %s %s\n", RED, filepath_compress, RESET);
	}
}

void free_memory(int **pointer_array, int height){
	for(int i=0; i<height; i++){
		free(pointer_array[i]);  // Free for each row
	}
	free(pointer_array);  // Also need to free the pointer to the pointer array
	printf("Freed memory\n");
}

