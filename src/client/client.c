#include "client.h"
#include <stdio.h>

void connect_to_server(char ip[], in_port_t port)
{
    if (is_valid_server(ip, port) == -1)
    {
        return;
    }

    int sockfd;
    struct sockaddr_in servaddr;

    sockfd = create_socket();
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(ip);
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

    receiving_message(&serv_data);
}

void get_local_ip_address(char *buffer, size_t buflen)
{
    struct ifaddrs *ifaddr, *ifa;
    int family;
    char host[NI_MAXHOST];

    if (getifaddrs(&ifaddr) == -1)
    {
        perror("getifaddrs");
        exit(EXIT_FAILURE);
    }

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
    {
        if (ifa->ifa_addr == NULL)
            continue;

        family = ifa->ifa_addr->sa_family;

        if (family == AF_INET)
        {
            if (strcmp(ifa->ifa_name, "lo") != 0) // Skip loopback interface
            {
                strncpy(buffer, host, buflen);
                break;
            }
        }
    }

    freeifaddrs(ifaddr);
}

int is_valid_server(char ip[], in_port_t port)
{
    // Check if the IP address is valid
    struct sockaddr_in servaddr;
    if (inet_pton(AF_INET, ip, &servaddr) <= 0)
    {
        printf("\nInvalid IP address: %s\n", ip);
        return -1;
    }

    char local_ip_address[INET_ADDRSTRLEN];
    get_local_ip_address(local_ip_address, INET_ADDRSTRLEN);

    // Check if the client is trying to connect to itself
    if (strcmp(ip, local_ip_address) == 0 && port == get_listening_port())
    {
        printf("\nCannot connect to itself.\n");
        return -1;
    }

    // Check if the port is valid
    if (port < 1024 || port > 65535)
    {
        printf("\nInvalid port number: %d\n", port);
        return -1;
    }

    // Check if server is already connected
    for (int i = 0; i < nconn; i++)
    {
        if (strcmp(ip, conn_data[i].ip_address) == 0 && port == conn_data[i].port)
        {
            printf("\nAlready connected to %s on port %d\n", ip, port);
            return -1;
        }
    }

    return 0;
}