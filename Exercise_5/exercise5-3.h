// DEFINITIONS
#define NUMBER_OF_DECKS 2
#define NUMBER_OF_SYMBOLS 13
#define NUMBER_OF_SUITS 4
#define CARDS_IN_A_DECK 52
#define TOTAL_NUMBER_OF_CARDS NUMBER_OF_DECKS*CARDS_IN_A_DECK // THIS GODAMN PROBLEM
#define NUMBER_OF_SHUFFLES 50

// TYPE DEFINITIONS
struct card_structure {
	 //1 - 10 (ace can be 1 and 11) 
	 char value; 
	 // A,2,3,4,5,6,7,8,9,X,J,Q,K
	 // use 'X' symbol for "10", since "10" would require a string of two char
	 char face;
	 // C=clubs, D= diamonds, H= hearts, S=spades
	 char suit; 
};

extern struct card_structure card[];  // Declare an array with undefined length