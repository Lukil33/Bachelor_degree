#include <iostream>
#include "Albero.h"
using namespace std;

static node * tree;

void albero_init(){
    tree=NULL;
}

void albero_insert(node* & tree, int number){
    if(tree==NULL){
        tree=new node{number, NULL, NULL};
    }else if(number<=(tree->value)){
        albero_insert(tree->left, number);
    }else{
        albero_insert(tree->right, number);
    }
}

void albero_deinit(){
    while(tree!=NULL){
        node * pointer=tree;
        while((pointer->left!=NULL)||(pointer->right!=NULL)){
            if((pointer->left!=NULL)&&((pointer->left->left==NULL)&&(pointer->left->right==NULL))){
                node * preblock=pointer; 
                pointer=pointer->left;
                delete pointer;
                preblock->left=NULL;
                break;
            }else if((pointer->right!=NULL)&&((pointer->right->left==NULL)&&(pointer->right->right==NULL))){
                node * preblock=pointer;
                pointer=pointer->right;
                delete pointer;
                preblock->right=NULL;
                break;
            }
            if(pointer->left!=NULL){
                pointer=pointer->left;
            }else if(pointer->right!=NULL){
                pointer=pointer->right;
            }
        }
    }
    delete tree;
}

void stampaAlbero(node * radice, int spazio){
    if (radice != NULL) {
        spazio ++;
        
        stampaAlbero(radice->right, spazio);
    
        for (int i = 1; i < spazio; i++) {
            cout<<"\t";
        }
        cout<<radice->value<<"\n";
        
        stampaAlbero(radice->left, spazio);
   }
}