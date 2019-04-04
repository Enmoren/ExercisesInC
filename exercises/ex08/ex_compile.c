/* Simple example using Glib.

From http://www.ibm.com/developerworks/linux/tutorials/l-glib/

gcc ex_compile.c -o ex_compile `pkg-config --cflags --libs glib-2.0`

*/

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

int main(int argc, char** argv) {
    GList* list = NULL;
    list = g_list_append(list, "Hello world!");
    printf("The first item is '%s'\n", (char *) g_list_first(list)->data);
    return 0;
}
