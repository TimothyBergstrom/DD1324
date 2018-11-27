// INCLUDES
#include <stdio.h>
#include <stdlib.h>

// DEFINITIONS
#define NUMBER_OF_DECKS 2
#define NUMBER_OF_SYMBOLS 13
#define NUMBER_OF_SUITS 4
#define CARDS_IN_A_DECK 52
#define TOTAL_NUMBER_OF_CARDS NUMBER_OF_DECKS*CARDS_IN_A_DECK

// FUNCTION PROTOYPES
void initialize();
void print_deck();

// GLOBAL VARIABLES
struct card_structure {
	 //1 - 10 (ace can be 1 and 11) 
	 char value; 
	 // A,2,3,4,5,6,7,8,9,X,J,Q,K
	 // use 'X' symbol for "10", since "10" would require a string of two char
	 char face;
	 // C=clubs, D= diamonds, H= hearts, S=spades
	 char suit; 
};
struct card_structure card[TOTAL_NUMBER_OF_CARDS];

// MAIN FUNCTION
int main(){
	initialize();
	printf("Initial card order from %d decks\n", NUMBER_OF_DECKS);
	print_deck();
}

// FUNCTION DEFINITIONS
void initialize(){
	// From exercise3-4
	char faces_index[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'X', 'J', 'Q', 'K'}; // Faces
	//char faces_names[12][6] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "Jack", "Queen", "King"};
	char faces_values[13] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', 'X', 'X', 'X', 'X'};
	char suits_index[4] = {'C', 'D', 'H', 'S',};  // suit
	//char suits_names[4][9] = {"Clubs","Diamonds", "Hearts", "Spades"};
	int card_counter = 0;
	for(int deck = 0; deck < NUMBER_OF_DECKS; deck++){
		for(int s=0; s<NUMBER_OF_SUITS; ++s){  // Iterate through suits, ++s means use s as it is, THEN add +1
			for(int f=0; f<NUMBER_OF_SYMBOLS; ++f){  // Iterate through faces
				card[card_counter].face = faces_index[f];
				card[card_counter].suit = suits_index[s];
				card[card_counter].value = faces_values[f];
				card_counter++;
			}				
		}
	}
}

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