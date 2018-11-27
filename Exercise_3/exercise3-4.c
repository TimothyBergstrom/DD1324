#include <stdio.h>
#include <stdlib.h>  // For atoi
#include <string.h>

int check_if_in_array(int letter, char *array, int size_of_array){
	for(int i = 0; i < size_of_array; i++){
		if(letter == array[i]){
			/* Really nice thing, works as bool if not 0. Can use it for multiple purposes.
			However: if you find something and it is the first index in array, it will return 0.
			Fix: add +1 to return and remove it afterwards. Could split it into two functions, one
			which works as a bool function and one that fetches index, but this is cleaner, but makes
			the code a little more difficult to understand */
			return 1+i;  
		}
	}
	return 0;
}

void error_print(){
      fprintf(stderr, "Usage: ./exercise3-4 fs\n");
	  fprintf(stderr, "f = face, (2, 3, 4, 5, 6, 7, 8, 9, J, Q, K, A)\n");
	  fprintf(stderr, "s = suit, (h, d, s, c)\n");
}

int main(int argc, char** argv){  
	if(argc<2){
		fprintf(stderr, "To few or many inputs\n");  // fprintf(stream, what_to_print)
		error_print();
		return -1;
	}
	else if (strlen(argv[1]) > 2 || strlen(argv[1]) < 2) {  // Im cheating here and using an inbuilt function strlen
		fprintf(stderr, "To few or many inputs\n");  // fprintf(stream, what_to_print)
		error_print();
		return -1;  // return 0 --> good, else = bad
    }
	// If we come here, first input length checks out, go and see if correct input and run what you need

	/* Very important fact here: By finding the index of input, we can use the same index if we have everything in the
	same order. However, lists of strings need to be have the length of the largest string + 1, due to need to fit in \0,
	or else we will also get the next value in array. 
	Ex: Diamonds = 8 characters. If it is in arr[0][8], we will also get arr[1][8], due to overlapping memory. 
    + 1 fixes that issue and we can fit the whole string in the array and call on them without overlapping */
	char faces_index[12] = {'2', '3', '4', '5', '6', '7', '8', '9', 'J', 'Q', 'K', 'A'}; // Faces
	char faces_names[12][6] = {"2", "3", "4", "5", "6", "7", "8", "9", "Jack", "Queen", "King", "Ace"};
	char faces_values[12][8] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "10", "10", "1 or 11"};
	
	char suits_index[4] = {'h', 'd', 's', 'c'};  // suit
	char suits_names[4][9] = {"Hearts", "Diamonds", "Spades", "Clubs"};
	
	if(check_if_in_array(argv[1][0], faces_index, 12) && check_if_in_array(argv[1][1], suits_index, 4)){
		int i = check_if_in_array(argv[1][0], faces_index, 12) - 1;
		int j = check_if_in_array(argv[1][1], suits_index, 4) - 1;
		char buffer[50];
		sprintf(buffer, "%s of %s, value = %s\n", faces_names[i], suits_names[j], faces_values[i]);
		printf("%s", buffer);
	}
	else{
		printf("Error in input\n");
		error_print();
		return -1;
	}
}	