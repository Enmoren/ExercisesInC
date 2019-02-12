/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE 10
#define BUFFER_SIZE 20

// This code won't use global variable, but change 
// the value through reference. 

// int end_of_file = 0;
// int bad_input = 0;

/* add_array: Adds up the elements of an array.
*
*  array: int pointer
*  n: number of elements in the array
*
*  returns: total
*/
int add_array(int array[], int n) {
    int i;
    int total = 0;

    for (i=0; i<n; i++) {
        total += array[i];
    }
    return total;
}

/* read_integer: Reads an integer from stdin.
*
*   returns: integer
*/
int read_integer(int* number_ptr) {
    char *res;
    char buffer[BUFFER_SIZE];
    char *end;
    // int number;

    // read a string    
    res = fgets(buffer, sizeof(buffer), stdin);
    if (res == NULL) {
        // end_of_file = 1;
        return -1;
    }

    // check if the length of the string it too long
    *number_ptr = strtol(buffer, &end, 10);
    if (strlen(buffer) == BUFFER_SIZE) {
        // bad_input = 1;
        return -2;
    }

    //printf("%s, %d\n", buffer, (int)strlen(buffer));

    // convert to integer
    *number_ptr = atoi(buffer);

    // check for invalid input.  Notice that atoi returns 0
    // for invalid input, so we can't allow the used to enter 0.
    if (*number_ptr == 0) {
        // bad_input = 1;
        return -2;
    }
    return 0;
}

int main()
{
    int i;
    int res;
    int array[ARRAY_SIZE];
    int val;

    for (i=0; i<ARRAY_SIZE; i++) {
        int flag = read_integer(&val);
        //printf("%d\n", res);

        if (flag == -1) {
            int total = add_array(array, i);
            printf("total %d\n", total);
            return 0;
        }

        if (flag == -2) {
            printf("Invalid input.\n");
            return -1;
        }
        array[i] = val;
    }

    // if we get to the end of the loop, the user entered
    // too many numbers
    printf("Too many numbers.\n");
    return -1;
}
