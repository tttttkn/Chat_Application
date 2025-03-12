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

void send_message(int conn_id, char *msg)
{
    if (strlen(msg) > 100)
    {
        printf("Length of message exceed 100: %ld\n", strlen(msg));
    }
    else if (write(conn_data[conn_id].sockfd, msg, strlen(msg)) == -1)
    {
        printf("Can not send message\n");
    }
    else
    {
        printf("Message sent\n");
    }
}

void add_connection_data(char ip_address[], in_port_t port, int sockfd, pthread_t thread_id)
{
    pthread_mutex_lock(&mutex);

    // Copy the connection data to the connection list
    strcpy(conn_data[nconn].ip_address, ip_address);
    conn_data[nconn].port = port;
    conn_data[nconn].sockfd = sockfd;
    conn_data[nconn].thread_id = thread_id;

    nconn++;

    // Notify the main thread that a new connection has been added
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
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

        int num_read = read(sockfd, buf, 1024);
        if (num_read == 0)
        {
            int connection_id = find_conn_id_by_sockfd(sockfd);
            printf("\nLost connection with %s on port %d\n", conn_data[connection_id].ip_address, conn_data[connection_id].port);
            terminate_connection(connection_id);
        }
        else if (num_read > 0)
        {
            printf("\nMessage from : %s\n", buf);
        }
        else
        {
            printf("\nMessage error\n");
        }
    }
}

void terminate_connection(int conn_id)
{
    pthread_mutex_lock(&mutex);
    if (close(conn_data[conn_id].sockfd) == -1)
    {
    }
    else
    {
        pthread_cancel(conn_data[conn_id].thread_id);
        remove_connection_from_list(conn_id);
    }
    pthread_mutex_unlock(&mutex);
}

void remove_connection_from_list(int conn_id)
{
    pthread_mutex_lock(&mutex);
    for (int i = conn_id; i < nconn - 1; i++)
    {
        conn_data[i] = conn_data[i + 1];
    }
    nconn--;
    pthread_mutex_unlock(&mutex);
}

int find_conn_id_by_sockfd(int sockfd)
{
    int i = 0;
    pthread_mutex_lock(&mutex);
    for (i = 0; i < nconn; i++)
    {
        if (conn_data[i].sockfd == sockfd)
        {
            break;
        }
    }
    pthread_mutex_unlock(&mutex);

    return i;
}

void terminate_all_connections()
{
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < nconn; i++)
    {
        terminate_connection(i);
    }
    pthread_mutex_unlock(&mutex);
}
