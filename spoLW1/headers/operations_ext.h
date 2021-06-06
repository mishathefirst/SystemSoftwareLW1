#ifndef LABSPO1_OPERATIONS_EXT_H
#define LABSPO1_OPERATIONS_EXT_H

#include <ftw.h>
#include <stdio.h>
#include "utils.h"
#include "../headers/constants.h"
#include "structures.h"
#include "filesystem_utils.h"
void execute_ext_cp(struct state* fs_state, char* src, char* target);
void execute_ext_ls(struct state* fs_state);
void execute_ext_pwd(struct state* fs_state);
void execute_ext_cd(struct state* fs_state, char* target);
void execute_help();
#endif //LABSPO1_OPERATIONS_EXT_H
