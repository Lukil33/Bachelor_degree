#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int isChild = !fork();
    if(isChild){
        sleep(3);
        return 5;
    }else{
        printf("Non il figlio\n");
    }
    int childStatus;
    wait(&childStatus);
    printf("Children terminated? %d\nReturn code: %d\n",
    WIFEXITED(childStatus),WEXITSTATUS(childStatus));
    return 0;
}