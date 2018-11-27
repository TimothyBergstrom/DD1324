#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "shuffle.h"
#include "exercise5-3.h"

// FUNCTION DEFINITIONS
void shuffle(){
	// From exercise4-2.c
	time_t t;  // Without seeding, you get the same number all the time. One way I found out is using time as seed works well
	srand(time(&t));  // & is the memory which t is located. t will update every second.
	int r1;  // Random number 1
	int r2;  // Random numver 2

	/* THIS GODDAMNED PROBLEM
	https://stackoverflow.com/questions/6865727/weird-mod-operator-result-when-using-define
	int r;
	r=rand();
	r1 = (r%max_cards);  // Interval is between 0 to TOTAL_NUMBER_OF_CARDS
	r2 = (r%TOTAL_NUMBER_OF_CARDS);
	printf("r1 is %d\n", r1);
	printf("r2 is %d\n", r2);
	WILL NOT PRINT THE SAME!!!
	*/
	int max_cards = TOTAL_NUMBER_OF_CARDS;  // need to make it into a temporary variable due to preprocessing shenanigans
	for(int i=0; i<NUMBER_OF_SHUFFLES; ++i){		
		for(int c=0; c<TOTAL_NUMBER_OF_CARDS; ++c){
			r1 = (rand()%max_cards);
			r2 = (rand()%max_cards);
			struct card_structure tmp1 = card[r1];
			struct card_structure tmp2 = card[r2];
			card[r1] = tmp2;
			card[r2] = tmp1;
		}
	}
}