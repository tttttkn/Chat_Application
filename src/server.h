#ifndef SERVER_H
#define SERVER_H

#define SA struct sockaddr
#define MAXNCLI 5
#include <pthread.h>

typedef struct
{
    char *ip_address;
    int connfd;
    pthread_t thread_id;
} cli_data_t;

void thread_cli_handler(void* cli_data);
void server_start_listening();
void get_ip_address();
void set_listening_port(in_port_t port);
in_port_t get_listening_port();
void wait_handler(int sig);

extern in_port_t SERV_PORT;

extern cli_data_t cli_data;

#endif