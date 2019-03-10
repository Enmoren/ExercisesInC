/*  Implementations of linked list in c

Author: Enmo Ren
Copyright (c) Enmo Corporation.

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software.

Result from running Valgrind:
==13015== Memcheck, a memory error detector
==13015== Copyright (C) 2002-2015, and GNU GPL'd, by Julian Seward et al.
==13015== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
==13015== Command: ./a.out
==13015==
==13015==
==13015== HEAP SUMMARY:
==13015==     in use at exit: 0 bytes in 0 blocks
==13015==   total heap usage: 4 allocs, 4 frees, 412 bytes allocated
==13015==
==13015== All heap blocks were freed -- no leaks are possible
==13015==
==13015== For counts of detected and suppressed errors, rerun with: -v
==13015== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


void free_anything(int *p) {
    free(p);
}

int read_element(int *array, int index) {
    int x = array[index];
    return x;
}

int main()
{
    // int never_allocated; This variable is never used, I commented it out
    int *free_twice = malloc(sizeof (int));
    int *use_after_free = malloc(sizeof (int));
    int *never_free = malloc(sizeof (int));

    int array1[100];
    int *array2 = malloc(100 * sizeof (int));

    // valgrind does not bounds-check static arrays
    // read_element(array1, -1); Commented it out to make sure read element in bound
    read_element(array1, 1);
    read_element(array1, 100);
    // free(array1);

    // but it does bounds-check dynamic arrays
    read_element(array2, 1);
    read_element(array2, 99);
    free(array2);

    // and it catches use after free
    *use_after_free = 17;
    free(use_after_free);

    // never_free is definitely lost
    *never_free = 17;
    free(never_free);

    // the following line would generate a warning
    // free(&never_allocated);

    // but this one doesn't
    // free_anything(&never_allocated);

    free(free_twice);
    // free(free_twice);

    return 0;
}
