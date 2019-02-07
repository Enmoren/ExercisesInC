#include <stdio.h>

/* add: return the sum of x and y */
int add(int x, int y) {
int z = x + y;
return z;
}
/* addp: add the pointees of p1 and p2,
and store the result in the pointee of p3. */
void addp(int* p1, int* p2, int* p3) {
*p3 = *p1 + *p2;
}
/* test_add: test add and print the result. */
void test_add() {
int sum = add(3, 4);
printf("%d\n", sum);
}
/* test_addp: test addp and print the result */
void test_addp() {
int a = 3;
int b = 4;
int c;
addp(&a, &b, &c);
printf("%d\n", c);
}
/* check_parity: return "n is even" if n is even,
and "n is odd" otherwise */
char* check_parity(int n) {
switch (n%2) {
case 0:
return "n is even";
case 1:
return "n is odd";
}
}
void main() {
test_add();
test_addp();
int n = 6;
char *s = check_parity(n);
printf("%s\n", s);
}