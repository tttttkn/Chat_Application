

#include "command_handler.h"

void *command_handler()
{
    char command_input[MAX_INPUT_SIZE];

    while (1)
    {
        bzero(command_input, MAX_INPUT_SIZE);
        get_input_from_user(command_input);
        command_parser(command_input);
    }
}

void get_input_from_user(char *buff)
{
    printf("\nEnter a command: ");
    fgets(buff, MAX_INPUT_SIZE, stdin);
    buff[strlen(buff) - 1] = '\0';
}

void command_parser(char *command_input)
{
    char *command = strtok(command_input, " ");

    if (strcmp(command, "connect") == 0)
    {
        char *ip_address = strtok(NULL, " ");
        char *port = strtok(NULL, "");

        connect_to_server(ip_address, atoi(port));
    }
    else if (strcmp(command, "send") == 0)
    {
        char *conn_id_str = strtok(NULL, " ");
        char *msg = strtok(NULL, "");

        send_message(atoi(conn_id_str), msg);
    }
    else if (strcmp(command, "list") == 0 && strtok(NULL, " ") == NULL)
    {
        print_list_connections(conn_data, nconn);
    }
    else if (strcmp(command, "help") == 0 && strtok(NULL, " ") == NULL)
    {
        print_help(SERV_PORT);
    }
    else if (strcmp(command, "myip") == 0 && strtok(NULL, " ") == NULL)
    {
        // print_server_ip()
    }
    else if (strcmp(command, "myport") == 0 && strtok(NULL, " ") == NULL)
    {
        print_server_port();
    }
    else if (strcmp(command, "terminate") == 0)
    {
        char *conn_id_str = strtok(NULL, " ");
        if (strtok(NULL, " ") == NULL)
        {
            terminate_connection(atoi(conn_id_str));
        }
        else
        {
            printf("\nInvalid command\n");
        }
    }
    else if (strcmp(command, "exit") == 0 && strtok(NULL, " ") == NULL)
    {
        terminate_all_connections();
        exit(0);
    }
    else
    {
        printf("\nInvalid command\n");
    }
}
