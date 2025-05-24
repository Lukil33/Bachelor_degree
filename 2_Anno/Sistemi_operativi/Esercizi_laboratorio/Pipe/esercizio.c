#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char** argv){
    if(argc != 2){
        fprintf(stderr, "Error: ./<file_name> <number_of_different-pipes>\n");
        exit(1);
    }

    int n = atoi(argv[1]);
    int fd[2];
    int res = 0;
    for(int i=0; i<n; i++){
        int pip = pipe(fd);
        int son = !fork();
        if(son){
            srand(time(0) ^ getpid());
            int num = rand()%20;
            write(fd[1],&num,sizeof(num));
            printf("Numero da sommare: %d\n",num);
            close(fd[1]);
            exit(0);
        }else{
            int sommaParz;
            read(fd[0],&sommaParz,sizeof(sommaParz));
            close(fd[0]);
            res += sommaParz;
        }
    }
    printf("Somma Finale: %d\n",res);
}