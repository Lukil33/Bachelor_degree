#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //bash.c

void myHandler(int sigNum){
    printf("[%d]ALARM!\n",getpid());
    exit(0);
}

int main(){
    signal(SIGALRM,myHandler);
    printf("I am %d\n",getpid());
    while(1);
}