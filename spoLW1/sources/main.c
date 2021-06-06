#include "../headers/user_interface.h"
#include "../headers/mode.h"
#include "../headers/partition.h"

int main(int argc, char* argv[]) {

    struct program args = get_args(argc, argv);
    if (args.mode == UNDEFINED){
        printf("Wrong program arguments!\n");
        printf("\t-m - mode of the program: 1 - show partitions, 2 - interact with EXT3 filesystem.\n");
    }else if (args.mode == PARTITIONS) {
        get_partitions();
    }else if (args.mode == EXT3){
        if (entrance(args.path) == 1) printf("An error occurred!\n");
    }
    return 0;
}
