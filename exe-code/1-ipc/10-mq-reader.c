#include <errno.h>
#include <mqueue.h> // `gcc -lrt`
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#define MSG_SIZE 100
#define MSGQUEUE_NAME "/bazinga"


/*
Message queue is a more advanced method of communication
Here messages have priority and the messages are 
read in the priority order

If more messages have the same pririry, it's a fifo

The pipe is not a file, but has a name that starts with "/"

It is required to compile it with the real time library of posix: `gcc -lrt`

*/

int main()
{
    char buf[MSG_SIZE];
    unsigned int prio;
    mqd_t mqd = mq_open(MSGQUEUE_NAME, O_RDONLY, 0664, NULL);  // "opaque data type": just use it and don't ask what it is.
    if (mqd < 0) {
        printf ("error - mq_open()");
        return 1;
    }
    struct mq_attr attr; // attributes struct
    mq_getattr(mqd, &attr);

    printf ("Nr. messages in the queue: %ld / %ld [maxsize=%ld]\n",
        attr.mq_curmsgs, // messages currently in the que
        attr.mq_maxmsg,  // maximum number of messages
        attr.mq_msgsize);// maximum dimension of each message

    while (attr.mq_curmsgs != 0) {
        ssize_t size = mq_receive(mqd, buf, MSG_SIZE, &prio);

        if (size < 0) {
            printf("main - mq_receive()");
            return 1;
        }
        printf("Received a message len=%ld with priority=%d: %s\n",
            size, prio, buf);

        mq_getattr (mqd, &attr);
    }
    printf("No messages left in the queue.\n");
    mq_close(mqd);
    return 0;    
    
}
