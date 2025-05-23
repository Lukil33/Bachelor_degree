#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> //setpgid.c

int main(void){
    int isChild = !fork(); //new child
    printf("PID %d PPID: %d GID %d\n",getpid(),getppid(),getpgid(0));
    if(isChild){
        setpgid(0,0); // Become group leader
        printf("PID %d PPID: %d GID %d\n",getpid(),getppid(),getpgid(0));
    };
    while(wait(NULL)>0);
}