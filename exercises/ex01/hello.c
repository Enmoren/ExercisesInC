#include <stdio.h>

int main() {
	int x = 5;
    printf("Hello, World!\n");
    return 0;
}

/* Can you find the code that corresponds to this line (int x = 5)?
   
   I think the line 17 corresponds to this line. 
   "movl	$5, -4(%rbp)"
 */

/* What happens if you turn on optimization using the flag -O2?
   
   Compared to "hello O0.s", "hello O2.s" has a shorter 
   main function section, and the "5" in "hello O0.s" also 
   disappears after being optimized.
 */

int main() {
	int x = 5;
    printf("%i/n", x);
    return 0;
}

/* Modify the printf statement to print x, then compile it with
   and without optimization. What effect does it have when you 
   print x?
   
   After optimization, the assembly language output becomes longer
   as it has more sections than it is without optimization. However,
   the main function itself becomes shorter. Special string like 
   "@progbits" shows up in the beginning of assembly code. 
   And "movl	$0, %eax" gets removed after optimization, which implies
   that "return 0" in the original code is condensed in the optimization 
   process. 

 */

int main() {
	int x = 5;
	int y = x + 1;
    printf("%i/n", y);
    return 0;
}

/* Add int y = x + 1; And then print the value of y (but not x). 
   Compile with and without optimization. What happens to x and y?
   
   After optimization, the "movl	$5, -8(%rbp)" is replaced by 
   "movl	$6, %edx" and "addl	$1, %eax" is disappeared, which 
   indicates that the addition is done by the compiler.

 */