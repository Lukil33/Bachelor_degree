#include <iostream>
#include "PriorityQ.h"
using namespace std;

priorityQueue *init(int dim){
    priorityQueue * queue=new priorityQueue;
    queue->dim=dim;
    cout<<"."<<endl;
    queue->queue=new node*[dim];
    for(int i=0; i<(queue->dim); i++){
        queue->queue[i]=NULL;
    }

    return queue;
}

void enqueue(priorityQueue &pq, char * testo, int priority){
    priority--;
    if((priority>=(pq.dim))||(priority<0)){
        cerr<<"Wrong inserted Priority\n";
    }else{
        node * new_node=new node;
        node * pointer;
        node * left;
        
        pointer=pq.queue[priority];
        left= NULL;

        while(pointer != NULL){
            left=pointer;
            pointer=pointer->right;
        }

        for(int i=0; testo[i]!='\0'; i++){
            new_node->testo[i]=testo[i];
        }
        new_node->left=left;
        new_node->right=NULL;
        if(left!=NULL){
            left->right=new_node;
        }
    }
}

bool dequeue(priorityQueue &pq){
    int priority=0;
    bool found=false;
    while((found==false)&&(priority<pq.dim)){
        if(pq.queue[priority]!=NULL){
            found=true;
            node * pointer;
            node * right;

            pointer=pq.queue[priority];
            right=pointer->right;
            right->left=NULL;
            pq.queue[priority]=right;
        }
        priority++;
    }
    return found;
}

void print(priorityQueue &pq){
    for(int i=0; i<pq.dim; i++){
        cout<<pq.queue[i]<<endl;
    }
}

void dealloc(priorityQueue &pq){
    
}