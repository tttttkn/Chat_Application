#include "client.h"

#include <stdio.h>
#include "connection_handler.h"



void connect_to_server(char* ip, in_port_t port)
{
    int sockfd;
    struct sockaddr_in servaddr;

    sockfd = create_socket();
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(ip);
    servaddr.sin_port = htons(port);


    // printf("Connecting to socket...%s\n", ip);
    connect_to_socket(sockfd, &servaddr);
    
    serv_data_t serv_data;
    serv_data.ip_address = inet_ntoa(servaddr.sin_addr);
    serv_data.sockfd = sockfd;
    serv_data.port = port;

    pthread_create(&serv_data.thread_id, NULL, (void*) &thread_serv_handler,(void*) &serv_data);
    
    pthread_mutex_lock(&mutex);
    pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&mutex);


    // pthread_join(serv_data.thread_id, NULL);
    // // After chatting close the socket
    // close(sockfd);
}


void thread_serv_handler(void* arg)
{
    pthread_detach(pthread_self());
    serv_data_t serv_data = *((serv_data_t*) arg);
    // printf("serv_data.ip_address: %s\n", serv_data.ip_address);
    // printf("serv_data.sockfd: %d\n", serv_data.sockfd);
    // printf("serv_data.port: %d\n", serv_data.port);
    add_connection_data(serv_data.ip_address, serv_data.port, serv_data.sockfd, pthread_self());
    receiving_message(serv_data.sockfd);
    close(serv_data.sockfd);
}