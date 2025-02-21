#include <stdio.h>
#include "socket.h"
#include "server.h"
#include "help.h"
#include <pthread.h>
#include "command_handler.h"
#include "client.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <port>\n", argv[0]);
        exit(0);
    }

    print_help(argv[1]);

    set_listening_port(atoi(argv[1]));
    
    server_start_listening();


    pthread_t user_handler;
    pthread_create(&user_handler,NULL,(void*) &command_handler,NULL);


    pthread_join(user_handler,NULL);
    return 0;
}