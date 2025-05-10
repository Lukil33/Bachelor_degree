#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* stringrev(char* str){
    char* res = malloc(strlen(str)*sizeof(char));
    for(int i=0; i<strlen(str); i++){
        res[i] = str[strlen(str)-1-i];
    }
    return res;
}

int stringpos(char* str, char c){
    int res = 0;
    for(int i=0; i<strlen(str); i++){
        if(str[i] == c){
            res += 1;
        }
    }
    return res;
}

int main(int argc, char** argv){
    
    if(argc != 3){
        printf("Usage: ./a.out <character> <string>\n");
        exit(0);
    }else{
        printf("La stringa: %s, reversata equivale a: %s\n", argv[2], stringrev(argv[2]));
        printf("Mentre il numero di ripetizioni del carattere %c in %s è di: %d\n",argv[1][0],argv[2],stringpos(argv[2], argv[1][0]));
    }
    return 0;
}