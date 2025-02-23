
#ifndef HELP_H
#define HELP_H
#include "connection_handler.h"

void print_help(const char* port);

void print_list_connections(const connection_data_t connection_data[], const int connection_count);

void print_server_port();
#endif