// From: http://beej.us/guide/bgipc/output/html/multipage/mq.html
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
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
    { /* same key as kirk.c */
        perror("argv");
        exit(1);
    }

    if ((msqid = msgget(key, 0644)) == -1)
    { /* connect to the queue */
        perror("msgget");
        exit(1);
    }

    printf("spock: ready to receive messages, captain.\n");

    for (;;)
    { /* Spock never quits! */
        if (msgrcv(msqid, &buf, sizeof(buf.mtext), 0, 0) == -1)
        {
            perror("msgrcv");
            exit(1);
        }
        printf("spock: \"%s\"\n", buf.mtext);
    }

    return 0;
}
