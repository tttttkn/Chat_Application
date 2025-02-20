#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H
#include <stdbool.h>

typedef struct
{
    char* str;
} User_input;

void get_input_from_user(char* buff);
void command_handler();


User_input* get_command_from_user(char buff[]);
bool command_parser(User_input* command);

#endif