#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h> //pipeWriteError.c

void handler(int signo){
    printf("SIGPIPE received\n"); perror("Error in handler");
}

int main(void){
    signal(SIGPIPE,handler);
    int fd[2]; char buf[50];
    int esito = pipe(fd); //Create unnamed pipe
    close(fd[0]); //Close read side
    printf("Attempting write\n");
    int numOfWritten = write(fd[1],"writing",8);
    printf("I've written %d bytes\n",numOfWritten);
    perror("Error after write");
}