#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "command_handler.h"
#include "client.h"
#include <unistd.h>
#include "connection_handler.h"
#include "help.h"
#include "server.h"

#define MAX 1024

void command_handler()
{
    char buf[MAX];
    while (1)
    {
        bzero(buf, MAX); // Clear the buffer
        get_input_from_user(buf);
        char **words = malloc(MAX * sizeof(char *));
        split_cmd_parser(buf, words);
        command_parser(words);

        // Free each string in the words array
        for (int i = 0; words[i] != NULL; i++)
        {
            free(words[i]);
        }
        // Free the words array itself
        free(words);
        words = NULL;
    }
}

void get_input_from_user(char *buff)
{
    printf("\nEnter a command: ");
    fgets(buff, MAX, stdin);
    buff[strlen(buff) - 1] = '\0';
}

bool command_parser(char *words[])
{
    // printf("word[0]: %s\n", words[0]);
    // printf("word[1]: %s\n", words[1]);
    // printf("word[2]: %s\n", words[2]);
    if (strcmp(words[0], "connect") == 0)
    {
        // printf("Connecting to %s...\n", words[1]);
        connect_to_server(words[1], atoi(words[2]));
    }
    else if (strcmp(words[0], "send") == 0)
    {
        // printf("Sending message...\n");

        send_message(atoi(words[1]), words[2]);
    }
    else if (strcmp(words[0], "list") == 0)
    {
        print_list_connections(conn_data, nconn);
    }
    else if (strcmp(words[0], "help") == 0)
    {
        print_help(SERV_PORT);
    }
    else if (strcmp(words[0], "myip") == 0)
    {
        // print_server_ip()
    }
    else if (strcmp(words[0], "myport") == 0)
    {
        print_server_port();
    }
    else if (strcmp(words[0], "terminate") == 0)
    {
        // printf("Terminating connection...\n");
        terminate_connection(atoi(words[1]));
    }
    else if (strcmp(words[0], "exit") == 0)
    {
        // printf("Exiting...\n");
        exit(0);
    }
    else
    {
        printf("Invalid command\n");
    }



    // printf("Cmd_parser done\n");
    return true;
}

void split_cmd_parser(char *buf, char *words[])
{
    char *temp = strtok(buf, " ");

    int i = 0;
    while (temp != NULL)
    {
        words[i++] = strdup(temp);
        temp = strtok(NULL, " ");
    }
    words[i] = NULL;
}