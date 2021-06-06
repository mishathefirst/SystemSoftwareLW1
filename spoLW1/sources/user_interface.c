#include "../headers/user_interface.h"
#include "../headers/operations_ext.h"
#include "limits.h"

void execute_operation(struct commands command, struct state* fs_state){
    switch (command.type) {
        case LS:
            execute_ext_ls(fs_state);
            break;
        case PWD:
            execute_ext_pwd(fs_state);
            break;
        case CD:
            execute_ext_cd(fs_state, command.first_argument);
            break;
        case CP:
            execute_ext_cp(fs_state, command.first_argument, command.second_argument);
            break;
        default:
            execute_help();
    }
}

int entrance(char* path){
    struct state* fs_state = setup(path);
    if (fs_state != NULL){
        printf("Enter a command:\n");
        char input[LINE_MAX];
        fgets_wrapper(input, LINE_MAX, stdin);
        struct commands command = parse_command(input);
        while (command.type != QUIT){
            execute_operation(command, fs_state);
            printf("Enter a command:\n");
            fgets_wrapper(input, LINE_MAX, stdin);
            command = parse_command(input);
        }
        printf("Stopping the app.\n");
        return 0;
    }
    return 1;
}

