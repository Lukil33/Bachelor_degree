#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <stdint.h>
#include <pthread.h>
#include <sys/stat.h>
#include <errno.h>

int p1 = 0, p2 = 0;

void handler1(int, siginfo_t* info, void*){
    p1 += 1;
    printf("Segnale inviato dal processo con ID:%d\nPunteggio: %d-%d\n",info->si_pid,p1,p2);
    printf("Waiting for signal...\n");
}

void handler2(int, siginfo_t* info, void*){
    p2 += 1;
    printf("Segnale inviato dal processo con ID:%d\nPunteggio: %d-%d\n",info->si_pid,p1,p2);
    printf("Waiting for signal...\n");
}

void fine(int){
    printf("Punteggio finale: %d-%d\n",p1,p2);
    exit(0);
}

int main(){
    printf("prova ad uccidermi\nID: %d\nPunteggio iniziale: %d-%d\n",getpid(),p1,p2);
    
    struct sigaction s1;
    s1.sa_sigaction = handler1;
    s1.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1,&s1,NULL);

    struct sigaction s2;
    s2.sa_sigaction = handler2;
    s2.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR2,&s2,NULL);

    struct sigaction sfine;
    sfine.sa_handler = fine;
    sfine.sa_flags = SA_SIGINFO;
    sigaction(SIGINT,&sfine,NULL);
    sigaction(SIGTERM,&sfine,NULL);

    printf("Waiting for signal...\n");
    while(1){
        pause();
    }
}