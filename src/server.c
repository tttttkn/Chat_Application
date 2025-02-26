#include "socket.h"
#include <arpa/inet.h> // inet_ntoa()
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include "server.h"
#include "connection_handler.h"

in_port_t SERV_PORT = 0;

void server_start_listening()
{
    int sockfd, connfd, len, pid, ncli;
    struct sockaddr_in cli;
    struct sockaddr_in servaddr;

    sockfd = create_socket();
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    listening_socket(sockfd, &servaddr, MAXNCLI);

    len = sizeof(cli);
    // ncli = 0;
    while (1)
    {
        connfd = accept(sockfd, (SA *)&cli, &len);

        if (connfd < 0)
        {
            printf("server acccept failed...\n");
            exit(0);
        }
        printf("\nConnected with %s on port %d\n", inet_ntoa(cli.sin_addr), SERV_PORT);

        connection_data_t cli_data;
        cli_data.sockfd = connfd;
        cli_data.ip_address = inet_ntoa(cli.sin_addr);
        // ncli++;
        pthread_create(&cli_data.thread_id, NULL, (void *)&thread_cli_handler, &cli_data);

        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond, &mutex);
        pthread_mutex_unlock(&mutex);
        // pthread_join(cli_data.thread_id, NULL);
    }

    // After chatting close the socket
    close(sockfd);
}

void thread_cli_handler(void *arg)
{
    pthread_detach(pthread_self());
    connection_data_t cli_data = *((connection_data_t *)arg);

    add_connection_data(cli_data.ip_address, SERV_PORT, cli_data.sockfd, pthread_self());

    receiving_message(cli_data.sockfd);
}

// void get_ip_address()
// {
//     printf("Your computer IP Address: %s\n", inet_ntoa(servaddr.sin_addr));
// }
void set_listening_port(in_port_t port)
{
    // printf("Set server port: %d\n", port);
    SERV_PORT = port;
}

in_port_t get_listening_port()
{
    return SERV_PORT;
}