#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv){
    if(argc == 1){
        fprintf(stderr, "Error: insufficient argument inserted");
    }

    for(int i=1; i<argc; i++){
        int figlio = fork();
        if(figlio == 0){
            execl(argv[i],NULL);
            exit(0);
        }
    }

    return 0;
}