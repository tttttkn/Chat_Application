#ifndef SERVER_H
#define SERVER_H

#define SA struct sockaddr
#define MAXNCLI 5
#include <pthread.h>

void thread_cli_handler(void *cli_data);
void server_start_listening();
void get_ip_address();
void set_listening_port(in_port_t port);
in_port_t get_listening_port();
void wait_handler(int sig);

extern in_port_t SERV_PORT;

#endif