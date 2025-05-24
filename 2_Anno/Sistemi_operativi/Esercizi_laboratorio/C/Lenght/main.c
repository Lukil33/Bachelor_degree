#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv){
    if(argc != 2){
        printf("Usage: ./a.out <input_string> \n");
    }else{
        printf("Stringa in input: %s\nLunghezza: %d\n", argv[1], strlen(argv[1]));
    }
    return 0;
}