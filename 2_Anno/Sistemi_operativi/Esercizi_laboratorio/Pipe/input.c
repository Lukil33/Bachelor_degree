// input.out
#include <stdio.h>
#include <unistd.h>

int main() {
    char msg[50]; int n=3;
    while((n--)>0){
        int c = read(0,msg,49);
        if (c>0) {
            msg[c]=0;
            fprintf(stdout,
            "Read: '%s' (%d)\n",msg,c);
        };
    };
};