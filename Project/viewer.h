#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED "\x1B[0;31;1m"  // Found a way to print in color, this codes for red (bright)
#define GREEN "\x1B[0;32;1m"
#define YELLOW "\x1B[0;33;1m"
#define BLUE "\x1B[0;34;1m"
#define MAGENTA "\x1B[0;35;1m"
#define CYAN "\x1B[0;36;1m"
#define WHITE "\x1B[0;37;1m"
#define RESET "\x1B[0m"  // This resets color
#define Background_RED "\x1B[0;41;1m"
#define Background_GREEN "\x1B[0;42;1m"
#define Background_YELLOW "\x1B[0;43;1m"
#define Background_BLUE "\x1B[0;44;1m"
#define Background_MAGENTA "\x1B[0;45;1m"
#define Background_Cyan "\x1B[0;46;1m"
#define Background_WHITE "\x1B[0;47;1m"
#define Background_RESET "\x1B[0;40m"  // Same as black color

void read_zip_pgm();  // Get out data of zip pgm
int **decode();  // Decodes compression and creates an array with them
int **arraycreate();
int **scale_image();
void arraydisplay();
char symbol_chooser();  // Simple way to fetch symbols
void free_memory();

