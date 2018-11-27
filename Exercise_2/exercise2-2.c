#include <stdio.h>
#include <wchar.h>  // To print utf-8 symbols or unicode
#include <locale.h>  // To set locale, needed to print in console
#define RED "\x1B[0;31m"  // Found a way to print in color, this codes for red
#define RESET "\x1B[0m"  // This resets color
 	
int main()
{ 
	char name[] = "Timothy Bergström";
	int day = 2;
	char month[] = "May";
	int year = 1995;
	int age = 23;
	char phone[] = "[REDACTED]";
	double fav_num = 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647;
	setlocale(LC_ALL, ""); // Set all locales to environment's default locale, needed for printing utf-8
	wchar_t fav_letter = 937;  // Ω symbol, utf-8. THIS WILL NOT PRINT IF TERMINAL IS NOT SET TO UTF-8!!
	printf("Name:\t\t\t %s\n", name);  // \t is tab, used to get nice intendation
	printf("Birthday:\t\t %s %d, %d\n", month, day, year);
	printf("Age:\t\t\t %d\n", age);
	printf("Phone:\t\t\t %s%s%s\n", RED, phone, RESET);  // prints red colors and resets
	printf("Favorite number:\t %.48f\n", fav_num); // Prints a float/double with 48 decimals
	printf("Favorite letter:\t %lc\n", fav_letter);  // lc = long character
	return 0;
}
