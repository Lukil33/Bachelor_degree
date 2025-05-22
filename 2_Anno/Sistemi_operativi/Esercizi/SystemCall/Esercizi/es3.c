#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv){
    if(argc != 3){
        fprintf(stderr,"Error: you have to insert 2 arguments\n");
        return 1;
    }

    int son = fork();
    char* intermediario = "temp.txt";
    if(son == 0){
        int intermediateFile = open(intermediario, O_WRONLY | O_CREAT);
        if(intermediateFile == -1){
            fprintf(stderr,"Error: intermediate file not created\n");
        }

        dup2(intermediateFile, STDOUT_FILENO);
        system(argv[1]);

        close(intermediateFile);
    }else{
        wait(NULL);
        int intermediateFile = open(intermediario, O_RDONLY);
        if(intermediateFile == -1){
            fprintf(stderr,"Error: intermediate file not found\n");
        }

        dup2(intermediateFile, STDIN_FILENO);
        system(argv[2]);

        close(intermediateFile);
    }
    
}