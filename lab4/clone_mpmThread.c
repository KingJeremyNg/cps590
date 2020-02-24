#define _GNU_SOURCE //for Ubuntu
#include <unistd.h>
#include <sched.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>

int x = 0;
int y = 0;

int do_something()
{
    x = 7;
    printf("This is process(thread) %d.\n", getpid());
    printf("x + y = %d\n", x + y);
    _exit(0);
}

int main(int argc, char *argv[])
{
    const int STACK_SIZE = 65536; // note stack grows down
    char *stack, *stackTop;
    int cret;

    stack = malloc(STACK_SIZE);
    if (stack == NULL)
    {
        perror("malloc");
        exit(1);
    }
    stackTop = stack + STACK_SIZE; /* Assume stack grows downward */

    cret = clone(do_something, stackTop, CLONE_VM, NULL);
    if (cret == -1)
    {
        perror("clone");
        exit(0);
    }

    y = 1;
    // parent keeps going here
    printf("This is process (thread) %d.\n", getpid());
    printf("x + y = %d\n", x + y);
    return 0;
}