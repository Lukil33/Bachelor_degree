#include <iostream>
using namespace std;

struct block{
    int number;
    block* next;
};

void add_element(block*& pila);
void rotation(block*& inizio, block*& fine);
block* ultimo_elemento(block*& pila);
void remove_element(block*& pila);
void print_code(block* pila);
void delete_code(block* pila);

int main(){
    block* prima_pila;
    block* seconda_pila;
    char letter;
    do{
        cout<<"<a> Add an element"<<endl
            <<"<r> Remove an element"<<endl
            <<"<p> Print the code"<<endl
            <<"<q> Quit"<<endl;
        cin>>letter;

        if(letter == 'a'){
            add_element(prima_pila);
        }
        if(letter == 'r'){
            if(prima_pila == nullptr){
                cout<<"Coda vuota"<<endl;
            }else{
                rotation(prima_pila, seconda_pila);
                remove_element(seconda_pila);
                rotation(seconda_pila, prima_pila);
            }
        }
        if(letter == 'p'){
            print_code(prima_pila);
        }
    }while(letter != 'q');
    delete_code(prima_pila);
    delete_code(seconda_pila);
    return 0;
}

void add_element(block*& pila){
    int number;
    cout<<"Quale numero vuoi inserire?: ";
    cin>>number;

    block* created=new block{number, nullptr};
    if(pila == nullptr){
        pila=created;
    }else{
        block* pointer=pila;
        while(pointer->next != nullptr){
            pointer=pointer->next;
        }
        pointer->next=created;
    }
}

void rotation(block*& inizio, block*& fine){
    while(inizio != nullptr){
        block* created=ultimo_elemento(inizio);
        if(fine == nullptr){
            fine=created;
        }else{
            block* pointer=fine;
            while(pointer->next != nullptr){
                pointer=pointer->next;
            }
            pointer->next=created;
        }
    }
}

block* ultimo_elemento(block*& pila){
    block* back_pointer=nullptr;
    block* pointer=pila;
    while(pointer->next != nullptr){
        back_pointer=pointer;
        pointer=pointer->next;
    }
    if(back_pointer == nullptr){
        pila=nullptr;
    }else{
        back_pointer->next=nullptr;
    }
    return pointer;
}

void remove_element(block*& pila){
    delete[] ultimo_elemento(pila);
}

void print_code(block* pila){
    cout<<"Code-> ";
    while(pila != nullptr){
        cout<<pila->number<<" ";
        pila=pila->next;
    }
    cout<<endl;
}

void delete_code(block* pila){
    while(pila != nullptr){
        block* pointer=pila;
        pila=pila->next;
        delete[] pointer;
    }
    delete[] pila;
}