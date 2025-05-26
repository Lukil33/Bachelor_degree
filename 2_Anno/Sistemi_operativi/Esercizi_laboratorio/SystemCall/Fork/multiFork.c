#include <stdio.h> //fork1.c
#include <unistd.h>

int main() {
    int a = fork();
    int b;
    if(a != 0){
        b = fork();
    }
    printf("Process: %d - Parent: %d\n",getpid(),getppid());
    return 0;
}