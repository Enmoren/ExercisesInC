/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>

/* Stack diagram included in github
*/

int var1;

void printAddress(){
    int var = 5;
	printf("Address of local variable is %p\n", &var);
}

int main ()
{
    int var2 = 5;
    int var3 = 6;
    int var4 = 6;

    void *p = malloc(128);
    void *a = malloc(128);
    char *s = "Hello, World";

/* After allocating new spaces and assigning address to
pointers, I printed the addresses of two pointers. The 
address of p is 0x2509010, which is 38834192 in decimal. 
While the address of a is 0x25090a0, which is 38834336 
in decimal. The comparision of addresses of two pointers
indicates that the heap does grow up, with a larger address
for the newly assigned space. 
*/

    printf ("Address of var2 is %p\n", &var2);
    printf ("Address of var3 is %p\n", &var3);
    printf ("Address of var4 is %p\n", &var4);


    printf ("p points to %p\n", p);
    printf ("a points to %p\n", a);
    printf ("s points to %p\n", s);

    printAddress();

/* I printed the addresses of local variable. The 
address of var2 is 0x7ffe3f562078, which is 140729961029752
in decimal. While the address of var3 is 0x7ffe3f56207c, 
which is 140729961029756 in decimal. 

Normally, the var2 and var3 are in stack, which supposes 
to grow downward. Whereas, the addresses I printed from 
var2 and var3 behave differently. The new variable has a 
higher address. 
*/

    void *memory1 = malloc(30);
    void *memory2 = malloc(30);

    printf ("memory1 points to %p\n", &memory1);
    printf ("memory2 points to %p\n", &memory2);

/* The memory1 has address of 0x1102540, which is 17835328 
in decimal. And the memory2 has address of 0x1102570, which 
is 17835376 in decimal. The space between them, 48 in decimal.
I also checked other sizes of spaces, and the spaces between 
them are constantly 48, which should be theoretically, according
to my belief, 32 bit. I confirmed the same code with other's 
computer, whereas, it gave me 32. 
*/
    return 0;
}
