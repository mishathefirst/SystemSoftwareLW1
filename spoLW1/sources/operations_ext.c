#include "../headers/operations_ext.h"

char* get_path(char* target){
    char* final_path = malloc(strlen(target));
    strcpy(final_path, target);
    long size = strlen(target);
    while (final_path[size] != '/') {
        size --;
    }
    final_path[size] = '\0';
    return final_path;
}


void execute_ext_ls(struct state* fs_state){
    struct ext_inode inode;
    struct ext_dir *entry;
    struct ext_dir *entry1;
    void* ptr;
    unsigned int num_inode = fs_state->current_inode;

    read_inode(fs_state, num_inode, &inode);
    entry = read_block(fs_state, &inode);
    ptr = entry;

    unsigned int size;
    size = 0;
    while (entry->name_len){
        char file_name[FILENAME_MAX];
        memcpy(file_name, entry->name, entry->name_len);
        file_name[entry->name_len] = 0;

        num_inode = fs_state->current_inode;
        read_inode(fs_state, entry->inode, &inode);
        //entry1 = read_block(fs_state, &inode);

        printf("%10u %s %10u\n", entry->inode, file_name, inode.i_size);
        entry = (void *) entry + entry->rec_len;
        size += entry->rec_len;
    }
    free(ptr);

}

void execute_ext_cd_back(struct state* fs_state) {
    struct ext_inode inode;
    struct ext_dir *entry;
    void* ptr;
    read_inode(fs_state, fs_state->current_inode, &inode);

    entry = read_block(fs_state, &inode);
    ptr = entry;
    entry = (void *) entry + entry->rec_len;

    if (fs_state->current_inode != entry->inode){
        fs_state->current_inode = entry->inode;
        char* final_path = get_path(fs_state->current_path);
        memset(fs_state->current_path, 0, strlen(fs_state->current_path));
        strcat(fs_state->current_path, final_path);
    }

    free(ptr);
}

void execute_cd(struct state* fs_state, char* target) {

    if (strcmp("..", target) == 0) execute_ext_cd_back(fs_state);
    else {
        unsigned int size;
        void *ptr;
        struct ext_dir *entry;
        char symbol[1] = {'/'};
        int flag = 0;

        struct ext_inode inode;
        read_inode(fs_state, fs_state->current_inode, &inode);

        entry = read_block(fs_state, &inode);
        ptr = entry;
        size = 0;
        while (entry->name_len != 0) {
            char file_name[FILENAME_MAX];
            memcpy(file_name, entry->name, entry->name_len);
            file_name[entry->name_len] = 0;
            if (strcmp(file_name, target) == 0) {
                fs_state->current_inode = entry->inode;
                strcat(fs_state->current_path, symbol);
                flag = 1;
                break;
            }
            entry = (void *) entry + entry->rec_len;
            size += entry->rec_len;
        }
        if (flag == 0) printf("Couldn't find directory %s\n", target);
        free(ptr);
    }
}






void execute_ext_cd(struct state* fs_state, char* target) {
    if (strcmp(".", target) != 0 && strcmp("./", target) != 0){
        char* copy_target = strdup(target);
        copy_target = strtok(copy_target, "/");
        while (copy_target != NULL) {
            execute_cd(fs_state, copy_target);
            copy_target = strtok(NULL, "/");
        }
    }

}

void copy_file(struct state* fs_state, struct ext_inode* inode, char* target){
    char* block;
    int fd = open(target, O_RDWR | O_APPEND | O_CREAT, file_mode);
    int i = 0;
    int index = 0;
    while (i < inode->i_size) {
        block = read_block_data(fs_state, inode, index);
        write(fd, block, fs_state->block_size);
        i += fs_state->block_size;
        index ++;
        free(block);
    }
}

void copy_dir(struct state* fs_state, struct ext_inode* inode, char* target){
    struct ext_dir* dir;
    struct ext_inode tmp_inode;
    char* path;
    void* ptr;


    dir = read_block(fs_state, inode);
    ptr = dir;
    struct stat directory = {0};
    if (stat(target, &directory) == -1){
        mkdir(target, file_mode);
    }

    unsigned int size;
    size = 0;
    while (dir->name_len != 0){
        char file_name[FILENAME_MAX];
        memcpy(file_name, dir->name, dir->name_len);
        file_name[dir->name_len] = 0;
        if (strcmp(file_name, ".") != 0 && strcmp(file_name, "..") != 0){
            read_inode(fs_state, dir->inode, &tmp_inode);
            path = malloc(PATH_MAX);
            memset(path, 0, sizeof (char ) * PATH_MAX);
            strcat(path, target);
            append_path_part(path, file_name);
            if (S_ISDIR(tmp_inode.i_mode)){
                copy_dir(fs_state, &tmp_inode, path);
            }else if (S_ISREG(tmp_inode.i_mode)){
                copy_file(fs_state, &tmp_inode, path);
            }
        }
        dir = (void *) dir + dir->rec_len;
        size += dir->rec_len;
    }
    free(ptr);
}

char* change_path(char* target) {
    setenv("SPO", home_path, 1);
    char* home = getenv("SPO");
    char* copy_path = strdup(target);
    char* result_path = malloc(strlen(target));
    memset(result_path, 0, strlen(result_path));
    copy_path = strtok(copy_path, "/");
    while (copy_path != NULL){
        if (strcmp("~", copy_path) == 0) {
            strcat(result_path, home);
        }else{
            append_path_part(result_path, copy_path);
        }
        copy_path = strtok(NULL, "/");
    }
    return result_path;
}

void execute_ext_cp(struct state* fs_state, char* src, char* target) {
    unsigned int inode_num;
    struct ext_inode inode;

    char* path;
    char* abs_path = change_path(target);
    inode_num = read_inode_filename(fs_state, src);
    if (inode_num != -1 && abs_path != NULL){
        read_inode(fs_state, inode_num, &inode);
        path = malloc(PATH_MAX*sizeof (char));
        memset(path, 0, PATH_MAX * sizeof (char));
        strcat(path, abs_path);
        append_path_part(path, src);
        if (S_ISDIR(inode.i_mode)){
            copy_dir(fs_state, &inode, path);
        }else if (S_ISREG(inode.i_mode)){
            copy_file(fs_state, &inode, path);
        }
    }
    free(abs_path);
}



void execute_ext_pwd(struct state* fs_state){
    printf("%s\n", fs_state->current_path);
}

void execute_help(){
    printf("ls - shows the content of the directory;\n");
    printf("cp <filename> <destination path> - copy the file according to the path;\n");
    printf("pwd  - write path to current file/directory;\n");
    printf("cd <directory path> - change directory;\n");
    printf("quit - leave the interaction mode and stop the app.\n");
}