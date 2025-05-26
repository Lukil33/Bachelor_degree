#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
//ipcRcv.c

struct msg_buffer{
    long mtype;
    char mtext[100]; //Same size!
} msgp;

int main(){
    key_t queue1Key = ftok("/tmp/unique", 1);
    int queueId = msgget(queue1Key , 0); //permission 0!
    msgrcv(queueId , &msgp, sizeof(msgp.mtext),20,0);
    printf("Received %s\n",msgp.mtext);
}