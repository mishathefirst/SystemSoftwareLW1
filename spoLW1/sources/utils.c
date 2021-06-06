#include "../headers/utils.h"

char* new_string(size_t size){
    char* string = malloc(size);
    memset(string, 0, size);
    return string;
}

int start_with(char* src, char* substr) {
    if (strncmp(src, substr, strlen(substr)) == 0) return 1;
    return 0;
}