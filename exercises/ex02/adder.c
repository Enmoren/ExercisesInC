/* 
Take user input and sum their values 
Author: Enmo Ren
Franklin W. Olin College of Engineering
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//maximal digits of input number, considering terminator and "\n"
const int expectedLength = 12;
//maximal number of inputs
const int maxNum = 10;

int get_input(int* array){
	int index = 0;
	int flag = 0;

	for (int i = 0; i < maxNum; i++){
		array[i] = 0;
	}

	while (flag == 0){
		printf("Enter an integer:\n");
		fflush(stdin);
		char input[expectedLength];
		fgets(input, expectedLength+1, stdin);

		if (feof(stdin)){
			printf("Exit\n");
			return 0;
		} 
		
		if (index >= maxNum){
			printf("Error: Exceeds maximal number of accepted length\n");
			return -1;
		}

		int len = strlen(input);
		if (len >= expectedLength){
			printf("Error: Exceeds buffer length\n");
			return -1;
		}

		if (atoi(input) == 0){
			printf("Error: Can not be converted to integer\n");
			return -1;
		}

		array[index] = atoi(input);
		index++;

	}
}

void get_sum(int* sum, int* array){
	int i;
	for (i = 0; i < maxNum; i++){
		*sum += array[i];
	}
}

int main(){
	int sum = 0;
	int array[maxNum]; 

	puts("Please enter up to 10 integers\n");
	int flag = get_input(array);
	if (flag == 0){
		get_sum(&sum, array);
		printf("Sum of input integers is %d\n", sum);
	}
	return 0;
}