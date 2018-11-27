#include <stdio.h>
#include <stdlib.h>  // For rand()
#include <time.h>

int main(){
	int lucky_number;
	int guess;
	time_t t;  // Without seeding, you get the same number all the time. One way I found out is using time as seed works well
	srand(time(&t));  // & is the memory which t is located. t will update every second.
	lucky_number = (rand()%9)+1;  // Without +1, the interval is between 0 and 9
	for(int i = 0; i < 2; i++){ // You only get two chances
		printf("Guess your lucky number! (Between 1 and 10) = ");
		scanf("%d", &guess);  // & points to where guess is stored in memory
		if(guess > 10 || guess < 0){  // if you enter 11, a character or whatever
			printf("Out of range. Guess again\n");
		}
		else if(guess < lucky_number){
		printf("Wrong guess. It is higher\n");
		}
		else if(guess > lucky_number){
			printf("Wrong guess. It is lower\n");
		}
		else if(guess == lucky_number){
			printf("You got it! It was %d", lucky_number);
			return 0;
		}
	}
	printf("Too bad, you did your best though. It was %d\n", lucky_number);
	return 0;
}