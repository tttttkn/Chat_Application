#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H
#include <stdbool.h>

typedef struct
{
    char *str;
} User_input;

void get_input_from_user(char *buff);

void command_handler();

User_input *get_command_from_user(char buff[]);

bool command_parser(char *words[]);

void split_cmd_parser(char *buf, char *words[]);


#endif