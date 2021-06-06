#include "../headers/commands.h"

enum command_type get_type(char* input){
    if (strcmp(input, "ls") == 0) {
        return LS;
    }else if (strcmp(input, "pwd") == 0){
        return PWD;
    }else if (strcmp(input, "cd") == 0){
        return CD;
    }else if (strcmp(input, "cp") == 0){
        return CP;
    }else if (strcmp(input, "quit") == 0){
        return QUIT;
    }else return HELP;
}
struct commands parse_command(char* input) {
    struct commands command;
    char* copy_input = strdup(input);
    copy_input = strtok(copy_input, " ");
    int i = 0;
    while (copy_input != NULL){
        if (i == 0) {
            command.type = get_type(copy_input);
        }else if (i == 1) {
            command.first_argument = copy_input;
        }else if (i == 2) {
            command.second_argument = copy_input;
        }
        i ++;
        copy_input = strtok(NULL, " ");
    }
    return command;
}

