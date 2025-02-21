#ifndef SERVER_H
#define SERVER_H


void server_start_listening();
void get_ip_address();
void set_listening_port(in_port_t port);
in_port_t get_listening_port();
void wait_handler(int sig);

#endif