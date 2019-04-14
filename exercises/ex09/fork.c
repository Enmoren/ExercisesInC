/* Example code for Exercises in C.

Copyright 2016 Allen B. Downey
License: MIT License https://opensource.org/licenses/MIT

Results after commenting out the exit statement after calling child_code
  Creating child 0.
  Hello from the parent.
  Hello from child 0.
  Hello from the parent.
  wait failed: No child processes
  ./fork: No child processes
  Child 24160 exited with error code 1.
  Elapsed time = 0.000682 seconds.


Result from running ./fork 3
Creating child 0.
Creating child 1.
Creating child 2.
Hello from child 0.
Hello from the parent.
Child 15540 exited with error code 0.
Hello from child 1.
Child 15541 exited with error code 1.
Hello from child 2.
Child 15542 exited with error code 2.
Elapsed time = 2.000937 seconds.



Creating child 0.
Hello from the parent.
Integer value in heap for child process is 0
Address of heap segmentin child process is 0x212b010
Integer value in stack is for child process 0
Address of stack segmentin child process is 0x7fff63c8330c  //Child process will copy the address spaces with same value, but the segement will be seperated
Global variable is 3
Address of global variable in child process is 0x6020ac
Hello from child 0.
Global variable in parent process is 0                    //Global value is not changed for parent process
Address of global variable in parent process is 0x6020ac
Integer value in heap for parent process is 66            //Integer stored in the heap is not changed for parent process
Address of heap segmentin parent process is 0x212b010
Integer value in stack is for parent process 66           //Integer stored in the stack is not changed for parent process
Address of stack segmentin parent process is 0x7fff63c8330c
Child 24211 exited with error code 0.
Elapsed time = 0.000680 seconds.

Since the code and static segements are constant, theoretically they should share
the same thing.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <wait.h>


// errno is an external global variable that contains
// error information
extern int errno;
int global = 0;


// get_seconds returns the number of seconds since the
// beginning of the day, with microsecond precision
double get_seconds() {
    struct timeval tv[1];

    gettimeofday(tv, NULL);
    return tv->tv_sec + tv->tv_usec / 1e6;
}


void child_code(int i)
{
    sleep(i);
    global = 3;

    printf("Global variable is %d\n", global);
    printf("Address of global variable in child process is %p\n", &global);
    printf("Hello from child %d.\n", i);
}

// main takes two parameters: argc is the number of command-line
// arguments; argv is an array of strings containing the command
// line arguments
int main(int argc, char *argv[])
{
    int status;
    pid_t pid;
    double start, stop;
    int i, num_children;
    int stack = 66;
    int *heap = (int*)malloc(128);
    *heap = 66;

    // the first command-line argument is the name of the executable.
    // if there is a second, it is the number of children to create.
    if (argc == 2) {
        num_children = atoi(argv[1]);
    } else {
        num_children = 1;
    }

    // get the start time
    start = get_seconds();

    for (i=0; i<num_children; i++) {

        // create a child process
        printf("Creating child %d.\n", i);
        // printf("Global variable is %d\n", errno);
        // printf("Address of global variable in parent process is %p\n", &errno);
        pid = fork();

        /* check for an error */
        if (pid == -1) {
            fprintf(stderr, "fork failed: %s\n", strerror(errno));
            perror(argv[0]);
            exit(1);
        }

        /* see if we're the parent or the child */
        if (pid == 0) {
            *heap = 0;
            printf("Integer value in heap for child process is %d\n", *heap);
            printf("Address of heap segmentin child process is %p\n", heap);

            stack = 0;
            printf("Integer value in stack is for child process %d\n", stack);
            printf("Address of stack segmentin child process is %p\n", &stack);

            child_code(i);
            exit(i);
        }
    }

    /* parent continues */
    printf("Hello from the parent.\n");

    for (i=0; i<num_children; i++) {
        pid = wait(&status);

        if (pid == -1) {
            fprintf(stderr, "wait failed: %s\n", strerror(errno));
            perror(argv[0]);
            exit(1);
        }

        printf("Global variable in parent process is %d\n", global);
        printf("Address of global variable in parent process is %p\n", &global);

        printf("Integer value in heap for parent process is %d\n", *heap);
        printf("Address of heap segmentin parent process is %p\n", heap);

        printf("Integer value in stack is for parent process %d\n", stack);
        printf("Address of stack segmentin parent process is %p\n", &stack);

        // check the exit status of the child
        status = WEXITSTATUS(status);
        printf("Child %d exited with error code %d.\n", pid, status);
    }
    // compute the elapsed time
    stop = get_seconds();
    printf("Elapsed time = %f seconds.\n", stop - start);

    exit(0);
}
