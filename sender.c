/* Pars SARICA */

#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include "queuesage.h"

int main()
{
    msg msg_obj;
    setup(&msg_obj, "/queuesage");
    send_msg(&msg_obj, "Roketimsi m2ler", 0);
    return 0;
}

