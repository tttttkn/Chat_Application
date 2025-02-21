#include "help.h"
#include <stdio.h>

void print_help(const char* port)
{
    printf("*********************** CHAT APPLICATION **********************\n");
    printf("Use the commands below:\n");
    printf("1. help\t\t\t\t\t: Display user interface options\n");
    printf("2. myip\t\t\t\t\t: Display IP address of this server\n");
    printf("3. myport\t\t\t\t: Display listening port of this app\n");
    printf("4. connect <destination> <port no>\t: Connect to another computer\n");
    printf("5. list\t\t\t\t\t: List all the current connections of this computer\n");
    printf("6. terminate <connection id>\t\t: Terminate the connection\n");
    printf("7. send <connection id> <message>\t: Send a message to the connection\n");
    printf("8. exit\t\t\t\t\t: Close all connections and terminate this app\n");
    printf("***************************************************************\n");
    // printf("Application listening on port %s\n", port);
}