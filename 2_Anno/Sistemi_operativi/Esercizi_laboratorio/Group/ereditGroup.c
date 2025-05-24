#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> //setpgid.c

int main(void){
    int isChild = !fork(); //new child
    printf("PID %d PPID: %d GID %d\n",getpid(),getppid(),getpgid(0));
    if(isChild){
        printf("PID %d setting my own pid\n",getpid());
        setpgid(0,0); // Become group leader
        printf("PID %d creating child\n",getpid());
        isChild = !fork();
        if(isChild) printf("PID %d inherited group %d\n",getpgid(0));
    };
    while(wait(NULL)>0);
}