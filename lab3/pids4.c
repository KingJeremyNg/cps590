/*
    Question 2 -    The ppid returns 1 because the parent process finishes before the getppid() call finishes.
                    pid 1 is the parent process of all processes.

    Question 3 -    All the instructions are sent to the cpu quickly.
                    The cpu executes them in parallel which will return a ppid of 1 or the correct parent pid depending on whether or not the instructions were completed in time.
*/

#define _GNU_SOURCE //for Ubuntu
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int pid, fpid, ppid;

    fpid = fork();

    printf("fpid is %d\n", fpid);

    if (fpid > 0)
    {
        pid = getpid();
        ppid = getppid();
        printf("\nThis is Parent. My pid %d. My parent's pid %d\n", pid, ppid);
    }
    else if (fpid == 0)
    {
        pid = getpid();
        ppid = getppid();
        printf("\nThis is Child. My pid %d. My parent's pid %d\n", pid, ppid);
    }
    else
    {
        printf("fork failed\n");
    }

    wait(5);
    return (0);
}