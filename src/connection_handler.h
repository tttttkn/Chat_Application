#ifndef CONNECTION_HANDLER
#define CONNECTION_HANDLER

#include <netinet/in.h>
#include <pthread.h>
#define MAXCONN 10

extern pthread_mutex_t mutex;
extern pthread_cond_t cond;

typedef struct
{
    int sockfd;
    pthread_t thread_id;
    in_port_t port;
    char *ip_address;
} connection_data_t;

void send_message(int conn_id, char *msg);

void add_connection_data(char *ip_address, in_port_t port, int sockfd, pthread_t thread_id);

void receiving_message(int sockfd);

void terminate_connection(int conn_id);

void remove_connection_from_list(int conn_id);

int find_conn_id_by_sockfd(int sockfd);

extern connection_data_t conn_data[MAXCONN];

extern int nconn;

#endif // CONNECTION_HANDLER