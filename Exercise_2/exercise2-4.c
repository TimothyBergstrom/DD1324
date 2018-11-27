#include <stdio.h>
#include <stdlib.h>  // for ldiv_t
#include <math.h>  // for floor function
/* SUPERDUPERIMPORTANT:
since math.h is included, you need to include "-lm" when compiling with gcc to link the
library to the compiled file */

int date_converter_ldiv_t(int input_num_of_days){
	ldiv_t output;
	
	// Calculate num of years, reminder to weeks
	output = ldiv(input_num_of_days, 365);  // Days in a year
	int num_of_years = output.quot;  // Quotient
	int num_of_weeks = output.rem;  // Reminder
	
	// Calculate num of weeks, reminder to days
	output = ldiv(num_of_weeks, 7);  // Days in a year, can just overwrite old variable
	num_of_weeks = output.quot;  // Overwrite old variable, no need to declare
	int num_of_days = output.rem;
	
	printf("Converting using ldiv_t\n");
	printf("%d days converts to:\n", input_num_of_days);
	printf("%d years, %d weeks, %d days\n", num_of_years, num_of_weeks, num_of_days);
}

int date_converter_mod(int input_num_of_days){
	
	input_num_of_days = (double) input_num_of_days;
	int num_of_years;
	int num_of_weeks;
	int num_of_days;
	int day_counter;
	
	num_of_years = floor((double) input_num_of_days / 365.0);  // Get amount of years, ignore reminder
	day_counter = input_num_of_days % 365; // Reminder = amount of days which does not fit in a year
	num_of_weeks = floor((double) day_counter / 7.0);  // Get weeks, ignore reminder
	num_of_days = day_counter%7; // The reminder is days

	num_of_years = (int)num_of_years;
	num_of_weeks = (int)num_of_weeks;
	num_of_days = (int)num_of_days;
	
	printf("Converting using modulus\n");
	printf("%d days converts to:\n", input_num_of_days);
	printf("%d years, %d weeks, %d days\n", num_of_years, num_of_weeks, num_of_days);
}
 	
int main(int argc, char** argv)
{ 
	// Utilizing code from fib.c (if that's ok)
    int input_num_of_days;
    if (argc < 2) {  // If no argument when running code
      fprintf(stderr, "You need to declare the number of days\n");  // fprintf(stream, what_to_print)
	  fprintf(stderr, "Max amount of days: 2,147,483,647\n");
      fprintf(stderr, "Usage: exercise2-4 num_of_days\n");
      return -1;  // return 0 --> good
    }
    input_num_of_days = atoi(argv[1]);
	date_converter_ldiv_t(input_num_of_days);
	printf("\n"); // Extra space between prints
	date_converter_mod(input_num_of_days);
	
	return 0;
}
