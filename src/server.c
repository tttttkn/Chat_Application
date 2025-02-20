#include "socket.h"
#include <arpa/inet.h> // inet_ntoa()
#include <stdio.h>
#define SA struct sockaddr

static in_port_t PORT = 0;

void server_start_listening()
{
    int sockfd, connfd, len, pid;
    struct sockaddr_in cli;
    struct sockaddr_in servaddr;

    sockfd = create_socket();
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    listening_socket(sockfd, &servaddr);

    len = sizeof(cli);

    while (1)
    {
        connfd = accept(sockfd, (SA *)&cli, &len);
        if (connfd < 0)
        {
            printf("server acccept failed...\n");
            exit(0);
        }

        pid = fork();

        switch (pid)
        {
        case 0: // child process
            close(sockfd);
            // handler
            close(connfd);
            exit(EXIT_SUCCESS);
            break;
        case -1: // fork failed
            exit(EXIT_FAILURE);
            break;
        default: // parent process
            close(connfd);
            break;
        }

    }

    // function for chat
    // func(connfd);

    // After chatting close the socket
    close(sockfd);
}

// void get_ip_address()
// {
//     printf("Your computer IP Address: %s\n", inet_ntoa(servaddr.sin_addr));
// }
void set_listening_port(in_port_t port)
{
    // printf("Set server port: %d\n", port);
    PORT = port;
}

in_port_t get_listening_port()
{
    return PORT;
}