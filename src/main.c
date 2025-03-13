#include <stdio.h>
#include <pthread.h>

#include "helper/help.h"
#include "command_handler/command_handler.h"
#include "server/server.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("\nUsage: %s <port>\n", argv[0]);
        exit(0);
    }

    print_help();

    set_listening_port(atoi(argv[1]));

    pthread_t user_handler;
    pthread_create(&user_handler, NULL, command_handler, NULL);

    server_start_listening();
    pthread_join(user_handler, NULL);

    return 0;
}