/* TO COMPILE:
gcc exercise5-2.c init.c -o exercise5-2
*/

// INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include "exercise5-2.h"
#include "init.h"

// FUNCTION PROTOTYPES
void print_deck();

// DEFINITIONS
struct card_structure card[TOTAL_NUMBER_OF_CARDS];

// MAIN FUNCTION
int main(){
	initialize();
	printf("Initial card order from %d decks\n", NUMBER_OF_DECKS);
	print_deck();
}

// FUNCTION DECLARATION
void print_deck(){
	for(int c=0; c<TOTAL_NUMBER_OF_CARDS; ++c){
		if(c%25 == 0 && c != 0){  // When 24 cards in a row, print next row
			printf("\n");
		}
		printf("%c", card[c].face);
		printf("%c ", card[c].suit);
		//printf("%d", cards[c].value);
	}
	printf("\n");
}