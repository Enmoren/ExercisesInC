#include <stdio.h>
#include <stdlib.h>

/* The optimization homework I did is included in hello.c
 * file. And all assembly code could be find in ex01 folder.
 */

/*
 * Program to calculate the count of cards in the shoe.
 * This code is released under the MIT License.
 * (c)2019, The Olin College.
 */

/* Update the count based on the val passed in. If the 
 * val is bigger than 2 but less than 7, the count get
 * incremented. If val equals 10, the count decreases 
 * by 1.  

 * val: value based on card_name
 * count: output result to display
 */
void updateCurrentCount(int val, int *count){
	if ((val > 2) && (val < 7)) {
			(*count)++;
		} else if (val == 10) {
			(*count)--;
		}
		printf("Current count: %i\n", *count);
}

/* Update val based on the input card name.
 * Return error message once received a val
 * out of range. 

 * val: value based on card_name
 * card_name: input string 
 */
int defaultVal(int val, char * card_name){
	val = atoi(card_name);
	if ((val< 1)||(val > 10)){
		puts("I don't understand that value!");
		return 0;
	}
	return val;
}

/* Based on the user input string, update val 
 * then use updateCurrentCount() to calculate
 * count value.  

 * val: value based on card_name
 * count: output result to display
 * card_name: input string from user
 */
void updateValCount(int val, int *count, char *card_name){
	switch(card_name[0]) {
			case 'K':
			case 'Q':
			case 'J':
				val = 10;
				break;
			case 'A':
				val = 11;
				break;
			case 'X':
				return;
			default:
				val = defaultVal(val, card_name);
				break;
	}
	updateCurrentCount(val, count);
}

/* Ask for the card name, and only take the first two char
 * of the user input. Calculate/update val and count.  

 * val: value based on card_name
 * count: output result to display
  * card_name: input string from user
 */
int main()
{
	char card_name[3];
	int count = 0;
	int val = 0;
	do {
		puts("Enter the card_name: ");
		scanf("%2s", card_name);
		if(card_name[1]!='\n')
			while((getchar())!='\n');
		updateValCount(val, &count, card_name);
	} 
	while (card_name[0] != 'X');
	return 0;
}