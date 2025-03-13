#include "socket.h"

#define SA struct sockaddr

int create_socket()
{
    int sockfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("\nSocket creation failed...\n");
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
        printf("\nSocket bind failed...\n");
        exit(0);
    }

    if ((listen(sockfd, max_clients)) != 0)
    {
        printf("\nListen failed...\n");
        exit(0);
    }
}

void connect_to_socket(int sockfd, struct sockaddr_in *servaddr)
{
    if (connect(sockfd, (SA *)servaddr, sizeof(*servaddr)) != 0)
    {
        printf("\nConnection to %s failed...\n", inet_ntoa(servaddr->sin_addr));
    }
    else
    {
        printf("\nConnected to %s\n", inet_ntoa(servaddr->sin_addr));
    }
}