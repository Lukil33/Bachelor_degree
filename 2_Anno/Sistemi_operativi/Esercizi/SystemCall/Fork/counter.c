#include <stdio.h> //fork1.c
#include <unistd.h>

int main(void){
    int counter = 0;
    if(fork()==0){
        counter++;
        printf("Counter in child = %d\n",counter);
    }else{
        counter = 10;
        printf("Counter in parent = %d\n",counter);
    }
    printf("Counter for both = %d\n",counter); //Both will print their value
}