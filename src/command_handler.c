#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "command_handler.h"
#include "client.h"


#define MAX 1024

void command_handler()
{
    char buff[MAX];
    while (1)
    {
        bzero(buff, MAX); // Clear the buffer
        get_input_from_user(buff);
        User_input *usr_input = get_command_from_user(buff);
        command_parser(usr_input);




        free(usr_input);
        usr_input = NULL;
    }
}

void get_input_from_user(char *buff)
{
    int n = 0;
    printf("Enter a command: ");
    while ((buff[n++] = getchar()) != '\n')
        ;

    buff[n] = '\0';
    // printf("Command entered: %s\n", buff);
}

User_input *get_command_from_user(char buff[])
{
    User_input *usr_input;
    // char* str[] = (char*) malloc(sizeof(char*))
    char *token = strtok(buff, " "); // First call of strok

    int n = 0;
    while (token != NULL)
    {
        usr_input = (User_input *)realloc(usr_input, (n + 1) * sizeof(User_input));
        usr_input[n].str = token;
        // printf("%s\n", usr_input[n].str);
        ++n;
        // Next call of strok
        token = strtok(NULL, " ");
    }
    return usr_input;
}

bool command_parser(User_input *usr_input)
{
    if (strcmp(usr_input[0].str, "connect") == 0)
    {
        printf("Connecting to %s...\n", usr_input[1].str);
        connect_to_server(usr_input[1].str, 5000);
    }
    else
    {
        printf("Connect failed\n");
    }
    return true;
}