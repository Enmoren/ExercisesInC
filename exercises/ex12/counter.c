/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

counter = 0
address of i is 0x7f384e8aaf14
counter = 0
address of i is 0x7f384e0a9f14
counter = 1
address of i is 0x7f384d8a8f14
counter = 1
address of i is 0x7f384d0a7f14
counter = 3
address of i is 0x7f3847ffef14
Final value of counter is 5

The children access the shared variable, counter, without synchronization, so
several threads can read the same value of counter before any threads increment it.
In this case, threads are running concurrently. Different threads accessing
value of counter concurrently might read same value. This is synchronization error.
However, the final result is correct. 

counter = 0
address of i is 0x7f7cb1d0cf14
counter = 0
counter = 0
address of i is 0x7f7cb250df14
counter = 1
address of i is 0x7f7cb0d0af14
counter = 0
address of i is 0x7f7cabffef14
counter = 4
address of i is 0x7f7caaffcf14
counter = 5
address of i is 0x7f7caa7fbf14
counter = 6
address of i is 0x7f7ca9ffaf14
address of i is 0x7f7cb150bf14
counter = 2
address of i is 0x7f7cab7fdf14
counter = 8
address of i is 0x7f7ca97f9f14
Final value of counter is 10


*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_CHILDREN 10

/* Print an error message and exit.
*/
void perror_exit(char *s)
{
    perror(s);
    exit(-1);
}

/* Call malloc and exit if it fails.
*/
void *check_malloc(int size)
{
    void *p = malloc(size);
    if (p == NULL) {
        perror_exit("malloc failed");
    }
    return p;
}

/* Structure that contains variables shared between threads.
*/
typedef struct {
    int counter;
} Shared;

/* Allocate the shared structure.
*/
Shared *make_shared()
{
    Shared *shared = check_malloc(sizeof(Shared));
    shared->counter = 0;
    return shared;
}

/* Create a child thread.
*/
pthread_t make_thread(void *(*entry)(void *), Shared *shared)
{
    int ret;
    pthread_t thread;

    ret = pthread_create(&thread, NULL, entry, (void *) shared);
    if (ret != 0) {
        perror_exit("pthread_create failed");
    }
    return thread;
}

/* Wait for a child thread.
*/
void join_thread(pthread_t thread)
{
    int ret = pthread_join(thread, NULL);
    if (ret == -1) {
        perror_exit("pthread_join failed");
    }
}

/* Code run by the child threads.
*/
void child_code(Shared *shared)
{
    printf("counter = %d\n", shared->counter);
    int i;
    printf("address of i is %p\n", &i);
    shared->counter++;
}

/* Entry point for the child threads.
*/
void *entry(void *arg)
{
    Shared *shared = (Shared *) arg;
    child_code(shared);
    pthread_exit(NULL);
}

int main()
{
    int i;
    pthread_t child[NUM_CHILDREN];

    Shared *shared = make_shared();

    for (i=0; i<NUM_CHILDREN; i++) {
        child[i] = make_thread(entry, shared);
    }

    for (i=0; i<NUM_CHILDREN; i++) {
        join_thread(child[i]);
    }

    printf("Final value of counter is %d\n", shared->counter);
    return 0;
}
