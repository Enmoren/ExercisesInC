/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

/* returns the address of array */
int *foo() {
    int i;
    int array[SIZE];

    printf("%p\n", array);

    for (i=0; i<SIZE; i++) {
        array[i] = 42;
    }
    return array;
}

/* tries to access array, however, it ends up storing
array at the same address.
*/
void bar() {
    int i;
    int array[SIZE];

    printf("%p\n", array);

    for (i=0; i<SIZE; i++) {
        array[i] = i;
    }
}

/* main() intends to print values stored in array.
However, due to the fact that the pointer of array
points to a stack allocated data, error will occur. 
*/

int main()
{
    int i;
    int *array = foo();
    bar();

    for (i=0; i<SIZE; i++) {
        printf("%d\n", array[i]);
    }

    return 0;
}

/* 1) The program intends to declare an array, and initialized
every element to 42 through foo() function. The bar() function
supposes to assign new value, which interrelates with its index,
to array. 

2) When I tried to compile it, it gives me a warning, saying 
"warning: function returns address of local variable [-Wreturn-local-addr]
     return array;" 
It means local variable won't be able to access after the function,
indicating that returning a pointer to that local variable may cause
error. 

3) After I ran the program, a segmentation fault occured.
It happens due to the fact that the pointer returned from the 
function is trying to access a local variable within the function.
However, local variable is stored in the stack. After the funciton finishs,
the local variable gets taken off the stack, causing a segementation fault.

4) The print statements in foo() and bar() prints the same address. 
I think it might result from the fact that they allocate the same 
space in stack.
*/
