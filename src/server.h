#ifndef SERVER_H
#define SERVER_H

#include <pthread.h>

#define SA struct sockaddr
#define MAXNCLI 5

void thread_cli_handler(void *cli_data);
void server_start_listening();
void get_ip_address();
void set_listening_port(in_port_t port);
in_port_t get_listening_port();

extern in_port_t SERV_PORT;

#endif