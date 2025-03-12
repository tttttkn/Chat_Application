#include "client.h"
#include <stdio.h>

void connect_to_server(char ip[], in_port_t port)
{
    int sockfd;
    struct sockaddr_in servaddr;

    sockfd = create_socket();
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    if (inet_pton(AF_INET, ip, &servaddr.sin_addr) <= 0)
    {
        printf("Invalid IP address: %s\n", ip);
        return;
    }
    servaddr.sin_port = htons(port);

    connect_to_socket(sockfd, &servaddr);

    connection_data_t serv_data;
    strcpy(serv_data.ip_address, inet_ntoa(servaddr.sin_addr));
    serv_data.sockfd = sockfd;
    serv_data.port = port;

    pthread_create(&serv_data.thread_id, NULL, (void *)&thread_serv_handler, (void *)&serv_data);

    // Wait for the thread to be added to the connection list
    pthread_mutex_lock(&mutex);
    pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&mutex);
}

void thread_serv_handler(void *arg)
{
    pthread_detach(pthread_self());
    connection_data_t serv_data = *((connection_data_t *)arg);

    add_connection_data(serv_data.ip_address, serv_data.port, serv_data.sockfd, pthread_self());

    receiving_message(serv_data.sockfd);
}