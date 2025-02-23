#ifndef SOCKET_H
#define SOCKET_H

#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <arpa/inet.h> // inet_ntoa()
#include <unistd.h> // read(), write(), close()

// #define MAX 80 


int create_socket();

void listening_socket(int sockfd, struct sockaddr_in* servaddr, uint16_t max_clients);

void connect_to_socket(int sockfd, struct sockaddr_in* servaddr);

#endif