#include <stdio.h> //fork1.c
#include <unistd.h>

int main() {
    int res = fork();
    int palle;
    if(res == 0){
        palle = fork();
    }
    printf("Process: %d - Parent: %d\n",getpid(),getppid());
    printf("hello\n");
    return 0;
}