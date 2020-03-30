/*
3) Spock has an infinite for loop that checks if msqid exists. If not then exit with flag 1.
4) Spock checks first if message queue with id 0644 exists. If not then output "msgget: No such file or directory".
5) Spock is will only receive messages through the message queue.
7) kirk destroys the message queue with condition "if (msgctl(msqid, IPC_RMID, NULL) == -1)"
8) kirkKey sends a message to each spockKey in a queue by order of execution.
*/

// From: http://beej.us/guide/bgipc/output/html/multipage/mq.html
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct my_msgbuf
{
    long mtype;
    char mtext[200];
};

int main(int argc, char *argv[])
{
    struct my_msgbuf buf;
    int msqid;
    key_t key;

    if (argc != 2)
    {
        perror("argc");
        exit(1);
    }

    if ((key = atoi(argv[1])) == 0)
    {
        perror("argv");
        exit(1);
    }

    if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1)
    {
        perror("msgget");
        exit(1);
    }

    printf("Enter lines of text, ^D to quit:\n");

    buf.mtype = 1; /* we don't really care in this case */

    while (fgets(buf.mtext, sizeof buf.mtext, stdin) != NULL)
    {
        int len = strlen(buf.mtext);

        /* ditch newline at end, if it exists */
        if (buf.mtext[len - 1] == '\n')
            buf.mtext[len - 1] = '\0';

        if (msgsnd(msqid, &buf, len + 1, 0) == -1) /* +1 for '\0' */
            perror("msgsnd");
    }

    if (msgctl(msqid, IPC_RMID, NULL) == -1)
    {
        perror("msgctl");
        exit(1);
    }

    return 0;
}
