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

void setup(msg* message, char* qn);
void send_msg(msg* message, char* msg, int priority);
void receive(msg* message, unsigned int* priority, char** msg);
void terminate_queue(msg* message);
