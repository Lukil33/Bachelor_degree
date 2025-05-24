#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int word = 6;
int max_size = 100;

void generate_arguments(char*** arguments){
    (*arguments) = malloc(word*sizeof(char*));
    for(int i=0; i<word; i++){
        (*arguments)[i] = malloc(max_size*sizeof(char));
    }
    strcpy((*arguments)[0], "--man");
    strcpy((*arguments)[1], "-m");
    strcpy((*arguments)[2], "-h");
    strcpy((*arguments)[3], "--help");
    strcpy((*arguments)[4], "-v");
    strcpy((*arguments)[5], "-version");
}

void release_arguments(char*** arguments){
    for(int i=0; i<word; i++){
        free((*arguments)[i]);
    }
    free((*arguments));
}

int main(int argc, char** argv){
    
    if(argc == 1){
        printf("Usage: ./a.out <series of arguments> \n");
        exit(0);
    }else{
        char** arguments, valid;
        generate_arguments(&arguments);

        int size = 0;
        for(int x=1; x<argc; x++){
            int chk = 0;
            for(int y=0; y<word; y++){
                if(strcmp(argv[x], arguments[y]) == 0){
                    chk += 1;
                }
            }
            if(chk == 0){
                printf("Argument: %s not found\n", argv[x]);
            }else{
                printf("Argument: %s found\n", argv[x]);
            }
        }

        release_arguments(&arguments);
    }
    return 0;
}