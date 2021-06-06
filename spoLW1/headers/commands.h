#ifndef LAB1SPO_COMMANDS_H
#define LAB1SPO_COMMANDS_H
#include "string.h"
#include "limits.h"
enum command_type {
    LS = 0,
    PWD = 1,
    CD = 2,
    CP = 3,
    QUIT = 4,
    HELP = 5
};

struct commands {
    enum command_type type;
    char* first_argument;
    char* second_argument;
};

struct commands parse_command(char* input);

#endif //LAB1SPO_COMMANDS_H
