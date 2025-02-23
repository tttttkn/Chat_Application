#ifndef CLIENT_H
#define CLIENT_H

#include "socket.h"
#include <pthread.h>
typedef struct 
{
    char* ip_address;
    int sockfd;
    pthread_t thread_id;
    in_port_t port;
} serv_data_t;

void connect_to_server(char* ip, in_port_t port);

void thread_serv_handler(void* serv_data);

#endif