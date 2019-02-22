#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

void strsplit (char* string, char sep, char* first, char* second){
	char* pos;
	pos = strstr(string, sep);
	// printf("%s\n", pos);
	*second = *(pos+1);
	*first = strchr(string, sep);
}

int main()

{

    char *str = "Geeksforgeeks";
    char *suffix = "f";
    char first[10];
    char second[10]; 
    // int result;
    strsplit(str, suffix, &first, &second);
    printf("Result is: %s\n", first);
    return 0;

}