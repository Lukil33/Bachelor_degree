#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char** argv){
    if(argc == 1){
        fprintf(stderr, "Error: insufficient argument inserted");
    }

    int out = open("output.txt", O_WRONLY | O_CREAT,0600);
    for(int i=1; i<argc; i++){
        int figlio = fork();
        if(figlio == 0){
            dup2(out, STDOUT_FILENO);
            execl(argv[i],NULL);
            exit(0);
        }
    }

    return 0;
}