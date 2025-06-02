#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h> //sigaction2.c

void handler(int signo){
    printf("signal received %d\n",signo);
}

int main(){
    struct sigaction sa; //Define sigaction struct
    sa.sa_handler = handler; //Assign handler to struct field
    sa.sa_flags = 0; //Initialise flags
    sigemptyset(&sa.sa_mask); //Define an empty mask
    sigaction(SIGUSR1,&sa,NULL);
    kill(getpid(),SIGUSR1);
}