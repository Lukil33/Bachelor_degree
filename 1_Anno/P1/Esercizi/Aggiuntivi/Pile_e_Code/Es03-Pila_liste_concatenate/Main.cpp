#include <iostream>
using namespace std;

struct block{
    int number;
    block* next;
};

void add_element(block*& pile);
void remove_element(block*& pile);
void print_pile(block* pile);
void delete_pile(block*& pile);

int main(){
    block* pile=nullptr;
    char letter;
    do{
        cout<<"<a> Add an element"<<endl
            <<"<r> Remove an element"<<endl
            <<"<p> Print the pile"<<endl
            <<"<q> Quit"<<endl;
        cin>>letter;

        if(letter == 'a'){
            add_element(pile);
        }
        if(letter == 'r'){
            if(pile == nullptr){
                cout<<"Pila vuota"<<endl;
            }else{
                remove_element(pile);
            }
        }
        if(letter == 'p'){
            print_pile(pile);
        }
    }while(letter != 'q');
    delete_pile(pile);
    return 0;
}

void add_element(block*& pile){
    int number;
    cout<<"Inserisci un numero: ";
    cin>>number;

    block* created=new block{number, nullptr};
    if(pile == nullptr){
        pile=created;
    }else{
        block* pointer=pile;
        while(pointer->next != nullptr){
            pointer=pointer->next;
        }
        pointer->next=created;
    }
}

void remove_element(block*& pile){
    block* pointer=pile;
    block* back_pointer=nullptr;
    while(pointer->next != nullptr){
        back_pointer=pointer;
        pointer=pointer->next;
    }
    if(back_pointer == nullptr){
        pile=nullptr;
    }else{
        back_pointer->next=nullptr;
    }
    delete[] pointer;
}

void print_pile(block* pile){
    cout<<"Pile-> ";
    while(pile != nullptr){
        cout<<pile->number<<" ";
        pile=pile->next;
    }
    cout<<endl;
}

void delete_pile(block*& pile){
    while(pile != nullptr){
        block* pointer= pile;
        pile=pile->next;
        delete[] pointer;
    }
    delete[] pile;
}