#ifndef CLIENT_H
#define CLIENT_H

#include "socket.h"
#include <pthread.h>
#include "connection_handler.h"

void connect_to_server(char ip[], in_port_t port);

void thread_serv_handler(void *serv_data);

#endif