#include <iostream>
#include "PriorityQ.h"
using namespace std;

priorityQueue *init(int dim){
    priorityQueue * queue=new priorityQueue;
    queue->dim=dim;
    queue->queue=new node*[dim];
    for(int i=0; i<(queue->dim); i++){
        queue->queue[i]=NULL;
    }

    return queue;
}

void enqueue(priorityQueue &pq, int value, int priority){
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

        new_node->value=value;
        new_node->left=left;
        new_node->right=NULL;
        if(left!=NULL){
            left->right=new_node;
        }else{
            pq.queue[priority]=new_node;
        }
    }
}

int dequeue(priorityQueue &pq){
    int value, priority=0;
    bool found=false;
    while((found==false)&&(priority<pq.dim)){
        if(pq.queue[priority]!=NULL){
            found=true;
            node * pointer;
            node * right;

            pointer=pq.queue[priority];
            if(pointer->right!=NULL){
                right=pointer->right;
                right->left=NULL;
                pq.queue[priority]=right;
            }else{
                pq.queue[priority]=NULL;
            }
            
            value=pointer->value;
        }
        priority++;
    }
    if(found==false){
        value=-1;
    }
    return value;
}

void print(priorityQueue &pq){
    for(int i=0; i<pq.dim; i++){
        cout<<i<<": ";
        node * puntatore;
        puntatore=pq.queue[i];
        while(puntatore!=NULL){
            cout<<puntatore->value<<" ";
            puntatore=puntatore->right;
        }
        cout<<endl;
    }
}

void dealloc(priorityQueue &pq){
   
    for(int priority=0; priority<pq.dim; priority++){
        while(pq.queue[priority]!=NULL){
            node * pointer;
            node * right;

            pointer=pq.queue[priority];
            if(pointer->right!=NULL){
                right=pointer->right;
                right->left=NULL;
                pq.queue[priority]=right;
            }else{
                pq.queue[priority]=NULL;
            }
            delete pointer;
        }
        delete[] pq.queue[priority];
    }
    delete[] pq.queue;
    delete[] &pq;
}