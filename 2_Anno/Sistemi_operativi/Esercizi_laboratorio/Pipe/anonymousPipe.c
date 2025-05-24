#include <stdio.h> //pipe.c
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(){
    int fd[2], cnt = 0;
    while(pipe(fd) == 0){ //Create unnamed pipe using 2 file descriptors
        cnt++;
        printf("%d,%d,",fd[0],fd[1]);
    }
    printf("\n Opened %d pipes, then error\n",cnt);
    int op = open("/tmp/tmp.txt", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    printf("File opened with fd %d\n",op);
}