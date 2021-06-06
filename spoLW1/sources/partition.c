#include "../headers/partition.h"


char* get_fs(char* path) {

    FILE* fd;
    int flag = 0;
    char* dev_path = strdup(path);
    size_t len = LINE_MAX * sizeof (char);
    size_t path_len = PATH_MAX * sizeof (char);
    char* fs_path = new_string(path_len);
    char* result = new_string(len);
    char* number = malloc(len);
    char* output = malloc(len);
    char* FS_TYPE_PROPERTY = "E:ID_FS_TYPE";

    strcat(fs_path, "/run/udev/data/b");
    strcat(dev_path, "/dev");


    fd = fopen(dev_path, "rb");
    getline(&number, &len, fd);
    fclose(fd);

    number[strlen(number) - 1] = '\0';

    strcat(fs_path, number);
    fd = fopen(fs_path, "rb");
    while (getline(&output, &len, fd) != -1){
        if (start_with(output, FS_TYPE_PROPERTY) == 1) {
            size_t result_len = strlen(FS_TYPE_PROPERTY) + 1;
            strcat(result, output);
            flag = 1;
            result += result_len;
        }
    }
    if (flag == 0) strcat(result, "\n");
    free(fs_path);
    free(output);
    free(number);
    fclose(fd);
    return result;
}

double get_size(char* path){
    unsigned long long result;
    int fd = open(path, O_RDONLY);
    ioctl(fd,  BLKGETSIZE64, &result);
    close(fd);
    return (double) result / (1024 * 1024 * 1024);
}

void get_partitions() {
    DIR* sys_dir = opendir("/sys/block/");
    struct dirent* sys_entry;
    char sub_dir_name[PATH_MAX] = {'\0'};
    if (sys_dir != NULL) {
        sys_entry = readdir(sys_dir);
        while (sys_entry != NULL) {
            if (start_with(sys_entry->d_name, "sd")) {
                strcpy(sub_dir_name, "/sys/block/");
                char* path = new_string(PATH_MAX);
                char* path_for_fs = new_string(PATH_MAX);

                strcat(path, "/dev/");
                strcat(path, sys_entry->d_name);

                strcat(path_for_fs, "/sys/block/");
                strcat(path_for_fs, sys_entry->d_name);
                strcat(path_for_fs, "/");

                strcat(sub_dir_name, sys_entry->d_name);

                printf("/dev/");
                printf("%s", sys_entry->d_name);
                printf("\t\tdisk");
                printf("\t\t\t%.3f GB\n", get_size(path));

                DIR* sys_sub_dir = opendir(sub_dir_name);
                if (sys_sub_dir != NULL) {
                    struct dirent* sys_sub_entry = readdir(sys_sub_dir);
                    while (sys_sub_entry != NULL) {
                        if (start_with(sys_sub_entry->d_name, "sd")) {

                            memset(path, 0, PATH_MAX);
                            strcat(path, "/dev/");
                            strcat(path, sys_sub_entry->d_name);

                            strcat(path_for_fs, sys_sub_entry->d_name);

                            printf("/dev/");
                            printf("%s", sys_sub_entry->d_name);
                            printf("\t\tpartition");
                            printf("\t\t\t%.3f GB", get_size(path));
                            printf("\t\t\t\t%s", get_fs(path_for_fs));

                            path_for_fs[strlen(path_for_fs) - strlen(sys_sub_entry->d_name)] = '\0';
                        }
                        sys_sub_entry = readdir(sys_sub_dir);
                    }
                } else {
                   printf("Couldn't read.\n");
                }
                free(path);
            }
            sys_entry = readdir(sys_dir);
        }
    } else {
        printf("Couldn't read.\n");
    }
}