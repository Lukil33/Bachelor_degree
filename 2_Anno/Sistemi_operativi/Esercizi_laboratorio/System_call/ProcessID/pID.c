#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> //ppid.c

int main(){
    printf("Subshell $$ = ");
    fflush(stdout); // Forza l’output di printf
    system("echo $$"); // subshell
    printf("PID: %d PPID: %d\n",getpid(),getppid());
}