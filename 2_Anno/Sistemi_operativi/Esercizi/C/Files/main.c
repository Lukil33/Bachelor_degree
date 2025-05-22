#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
    FILE* in = fopen("input.txt", "r+");
    int out = open("output.txt", O_WRONLY | O_CREAT);
    if(in == NULL || out == -1){
        fprintf(stderr,"Error: errore nell'apertura dei file %d\n", out);
        exit(1);
    }
    int max_dim = 255;
    char* testo = malloc(max_dim * sizeof(char));
    while(feof(in) != 1){
        fgets(testo, max_dim, in);
        write(out, testo, strlen(testo));
    }
    fclose(in);
    close(out);
    return 0;
}