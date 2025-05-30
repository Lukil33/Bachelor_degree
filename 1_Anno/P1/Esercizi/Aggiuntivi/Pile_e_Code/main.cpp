#include <iostream>
using namespace std;

struct Block{
    int val;
    Block* next;
};

void insert_a_num(Block*&);
void remove_a_num(Block*&);
void print_array(Block*);
void dealloc(Block*&);

int main(){
    Block* pila;
    int op;
    bool exit = false;

    while(!exit){
        cout<<"Inserire il numero dell operazione che si vuole eseguire:"<<endl<<
            "1 -> inserisci un numero"<<endl<<
            "2 -> rimuovi un numero"<<endl<<
            "3 -> stampa la Coda"<<endl<<
            "4 -> quit"<<endl;
        cin>>op;

        switch(op){
            case 1: insert_a_num(pila); break;
            case 2: remove_a_num(pila); break;
            case 3: print_array(pila); break;
            case 4: exit = true; dealloc(pila); break;
            default: cerr<<"Numero inserito erratamente"<<endl;
        }
    }
}

void insert_a_num(Block*& p){
    int num;
    cout<<"Inserire un numero: ";
    cin>>num;

    Block* pointer = new Block{num, nullptr};

    if(p == nullptr){
        p = pointer;
    }else{
        Block* temp = p;
        while(temp -> next != nullptr){
            temp = temp->next;
        }
        temp->next = pointer;
    }
}

void remove_a_num(Block*& p){
    if(p != nullptr){
        Block* temp = p;
        p = p->next;
        delete temp;
    }else{
        cerr<<"Coda senza elementi"<<endl;
    }
}

void print_array(Block* p){
    cout<<"Coda -> ";
    while(p != nullptr){
        cout<<p->val<<" ";
        p = p->next;
    }
    cout<<endl;
}

void dealloc(Block*& p){
    while(p != nullptr){
        Block* temp = p;
        p = p->next;
        delete temp;
    }
}