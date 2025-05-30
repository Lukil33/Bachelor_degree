#include <iostream>
#include "pila.h"

struct Block{
    int val;
    Block* left;
    Block* right;
};

static Block* P1;
static Block* P2;
static int m_dim;
static int dim_P1;
static int dim_P2;

// inizializza P1 e P2 con un'array o una lista 
// doppiamente concatenata con dimensione massima 
// 'dim'. Di conseguenza, la somma del numero di 
// elementi in P1 e P2 può essere al massimo uguale 
// a 'dim';
void init(int dim){
    P1 = nullptr;
    P2 = nullptr;
    dim_P1 = 0;
    dim_P2 = 0;
    m_dim = dim;
}

Block* lastpointer(Block* P){
    if(P != nullptr){
        if(P->left == nullptr){
            while(P->right != nullptr){
                P = P->right;
            }
        }else{
            while(P->left != nullptr){
                P = P->left;
            }
        }
        return P;
    }
    return nullptr;
}

// inserisci l'elemento 'valore' in P1
bool pushP1(int valore){
    if(dim_P1+dim_P2 <= m_dim){
        if(dim_P1 == 0){
            P1 = new Block{valore, nullptr, lastpointer(P2)};
            if(P2 == nullptr){
                P2 = P1;
            }
        }else{
            P1 = new Block{valore, nullptr, P1};
        }
        dim_P1+=1;
        return true;
    }else{
        return false;
    }
}

// inserisci l'elemento 'valore' in P2
bool pushP2(int valore){
    if(dim_P1+dim_P2 <= m_dim){
        if(dim_P2 == 0){
            P2 = new Block{valore, lastpointer(P1), nullptr};
            if(P1 == nullptr){
                P1 = P2;
            }
        }else{
            P2 = new Block{valore, P2, nullptr};
        }
        dim_P2+=1;
        return true;
    }else{
        return false;
    }
}

// assegna al parametro il valore del primo 
// elemento di P1, se presente
bool topP1(int& num){
    if(dim_P1 > 0){
        num = P1->val;
        return true;
    }else{
        return false;
    }
}

// assegna al parametro il valore del primo 
// elemento di P2, se presente
bool topP2(int& num){
    if(dim_P2 > 0){
        num = P2->val;
        return true;
    }else{
        return false;
    }
}

// rimuovi il primo elemento di P1, se presente
bool popP1(){
    if(dim_P1 > 0){
        Block* pointer = P1;
        P1 = P1->right;
        dim_P1-=1;
        delete pointer;
        return true;
    }else{
        return false;
    }
}

// rimuovi il primo elemento di P2, se presente
bool popP2(){
    if(dim_P2 > 0){
        Block* pointer = P2;
        P2 = P2->left;
        dim_P2-=1;
        delete pointer;
        return true;
    }else{
        return false;
    }
}

// de-inizializza la pila e dealloca la memoria dinamica
void deinit(){
    dim_P1 = 0;
    dim_P2 = 0;
    while(P1 != nullptr){
        Block* pointer = P1;
        P1 = P1->right;
        delete pointer;
    }
}

// stampa a video gli elementi di P1 e P2
void print(){
    std::cout<<"P1 -> ";
    Block* pointer = P1;
    for(int i=0; i<dim_P1; i++){
        std::cout<<pointer->val<<" ";
    }
    std::cout<<std::endl;
    std::cout<<"P2 -> ";
    pointer = P2;
    for(int i=0; i<dim_P2; i++){
        std::cout<<pointer->val<<" ";
    }
    std::cout<<std::endl;
}