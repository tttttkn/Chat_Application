#include "connection_handler.h"
#include "server.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>

connection_data_t conn_data[MAXCONN];
int nconn = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
// static nfds = 0;

void send_message(int conn_id, char *msg)
{
    printf("connid: %d\n", conn_id);
    printf("sockfd: %d\n", conn_data[conn_id].sockfd);
    printf("connid: %s\n", msg);
    if (write(conn_data[conn_id].sockfd, msg, strlen(msg)) == -1)
    {
        printf("Can not send message\n");
    }
    else
    {
        printf("Send message successfully\n");
    }
}

void add_connection_data(char *ip_address, in_port_t port, int sockfd, pthread_t thread_id)
{
    pthread_mutex_lock(&mutex);
    conn_data[nconn].ip_address = ip_address;
    conn_data[nconn].port = port;
    conn_data[nconn].sockfd = sockfd;
    conn_data[nconn].thread_id = thread_id;
    // printf("connection added number: %d\n", nconn);
    // printf("ip_address: %s\n", conn_data[nconn].ip_address);
    // printf("Port: %d\n", conn_data[nconn].port);
    // printf("sockfd: %d\n", conn_data[nconn].sockfd);
    // printf("thread id: %ld\n", conn_data[nconn].thread_id);
    nconn++;

    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);

    // char buf[1024];
    // while (1)
    // {
    //     bzero(buf, 1024);
    //     if (read(sockfd, buf, 1024) != 0)
    //     {
    //         printf("Message: %s\n", buf);
    //     }
    // }
}

void receiving_message(int sockfd)
{
    int nfds = sockfd + 1;
    fd_set readfds;
    char buf[1024];
    while (1)
    {
        FD_ZERO(&readfds);

        FD_SET(sockfd, &readfds);

        select(nfds, &readfds, NULL, NULL, NULL);
        bzero(buf, 1024);
        read(sockfd, buf, 1024);
        printf("\nMessage from : %s\n", buf);
    }
}
