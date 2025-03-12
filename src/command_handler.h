#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H
#include <stdbool.h>

#define MAX_INPUT_SIZE 1024

void get_input_from_user(char *buff);

void command_handler();


void command_parser(char *command_input);


#endif