#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void main(){
    // ATTENZIONE, QUESTO PROGRAMMA NON SI PUÒ BLOCCARE CON I SEMPLICI CTRL+C, CTRL+K

    signal(SIGINT,SIG_IGN); //Ignore signal
    signal(SIGTSTP,SIG_IGN); //Use default handler
    signal(SIGSTOP,SIG_IGN);
    signal(SIGKILL,SIG_IGN);
    signal(SIGTERM,SIG_IGN);
    while(1){
        printf("%d\n",getpid());
    }
}