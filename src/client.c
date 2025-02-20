#include "client.h"

#include <stdio.h>

void connect_to_server(char *ip, in_port_t port)
{
    int sockfd;
    struct sockaddr_in servaddr;

    sockfd = create_socket();
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(ip);
    servaddr.sin_port = htons(port);

    printf("Connecting to socket...\n");
    connect_to_socket(sockfd, &servaddr);

    // function for chat
    // func(sockfd);
    while(1);

    // After chatting close the socket
    printf("close socket\n");
    close(sockfd);
}