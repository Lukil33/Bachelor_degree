#include <stdlib.h>
#include <stdio.h> //system.c
#include <sys/wait.h> /* For WEXITSTATUS */

void main(){
    int outcome = system("echo ciao ; echo $0");
    printf("Outcome = %d %d\n",outcome,WEXITSTATUS(outcome));
    outcome = system("notExistingCommand");
    printf("Outcome = %d %d\n",outcome,WEXITSTATUS(outcome));
    outcome = system("exit 23");
    printf("Outcome = %d %d\n",outcome,WEXITSTATUS(outcome));
}