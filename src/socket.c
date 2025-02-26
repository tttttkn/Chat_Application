#include "socket.h"
#include <stdio.h>

#define SA struct sockaddr

int create_socket()
{
    int sockfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
    {
        return sockfd;
    }
}

void listening_socket(int sockfd, struct sockaddr_in *servaddr, uint16_t max_clients)
{

    if ((bind(sockfd, (SA *)servaddr, sizeof(*servaddr))) != 0)
    {
        printf("socket bind failed...\n");
        exit(0);
    }

    if ((listen(sockfd, max_clients)) != 0)
    {
        printf("Listen failed...\n");
        exit(0);
    }
}

void connect_to_socket(int sockfd, struct sockaddr_in *servaddr)
{
    if (connect(sockfd, (SA *)servaddr, sizeof(*servaddr)) != 0)
    {
        printf("connection to %s failed...\n", inet_ntoa(servaddr->sin_addr));
    }
    else
    {
        printf("connected to %s..\n", inet_ntoa(servaddr->sin_addr));
    }
}