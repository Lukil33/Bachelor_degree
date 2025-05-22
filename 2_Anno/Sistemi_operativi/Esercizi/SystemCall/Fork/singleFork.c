#include <stdio.h> 
#include <unistd.h>

int main(void) {
    int result = fork();
    if(result == 0){
        printf("I'm the child\n");
        return 0;
    }else{
        printf("I'm the parent\n");
    }
    return 0;
}