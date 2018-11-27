#include <stdio.h>
#include <stdlib.h>
#include "init.h"
#include "exercise5-2.h"

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