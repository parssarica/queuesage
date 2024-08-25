/* Pars SARICA */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

typedef struct _msg
{
    mqd_t mq;
    struct mq_attr attr;
    char buffer[256];
}msg;

int setup(msg* message, char* qn)
{
    message->attr.mq_flags = 0;
    message->attr.mq_maxmsg = 10;
    message->attr.mq_msgsize = 256;
    message->attr.mq_curmsgs = 0;
    
    message->mq = mq_open(qn, O_RDWR | O_CREAT | O_NONBLOCK, S_IRUSR | S_IWUSR, &(message->attr));
    if(message->mq == (mqd_t)-1)
    {
        perror("mq_open");
        return (mqd_t)-1;
    }
    return message->mq;
}

int send_msg(msg* message, char* msg, int priority)
{
    strncpy(message->buffer, msg, strlen(msg) + 1);
    if(mq_send(message->mq, message->buffer, sizeof(message->buffer), priority) == -1)
    {
        perror("mq_send");
        return -1;
    }
    return 0;
}

int receive(msg* message, unsigned int* priority, char** msg)
{
    int bytes_received = mq_receive(message->mq, message->buffer, 256, priority);
    if(bytes_received == -1)
    {
        perror("mq_receive");
        return -1;
    }
    strncpy(*msg, message->buffer, 256);
    return bytes_received;
}

int terminate_queue(msg* message)
{
    if(mq_close(message->mq) == -1)
    {
        perror("mq_close");
        return -1;
    }
    return 0;
}
