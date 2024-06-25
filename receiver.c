/* Pars SARICA */

#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include "queuesage.h"

int main()
{
    msg message;
    unsigned int priority;
    char* msg;
    msg = malloc(256);
    setup(&message, "/queuesage");
    receive(&message, &priority, &msg);
    printf("%s\n", msg);
    receive(&message, &priority, &msg);
    printf("%s\n", msg);
    terminate_queue(&message);
    free(msg);
}
