cmake_minimum_required(VERSION 3.17)
project(LW1 C)

set(CMAKE_C_STANDARD 99)

add_executable(LW1 sources/main.c sources/user_interface.c headers/user_interface.h  headers/commands.h headers/structures.h headers/operations_ext.h sources/filesystem_utils.c headers/filesystem_utils.h sources/commands.c sources/operations_ext.c sources/mode.c headers/mode.h sources/partition.c headers/partition.h headers/state.h sources/main.c headers/constants.h sources/utils.c headers/utils.h)