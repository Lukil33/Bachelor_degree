#include <iostream>
using namespace std;

struct block{
    int number;
    block* next;
};

void add_element(block*& code);
void remove_element(block*& code);
void print_code(block* code);
void delete_code(block*& code);

int main(){
    block* code=nullptr;
    char letter;
    do{
        cout<<"<a> Add an element"<<endl
            <<"<r> Remove an element"<<endl
            <<"<p> Print the code"<<endl
            <<"<q> Quit"<<endl;
        cin>>letter;

        if(letter == 'a'){
            add_element(code);
        }
        if(letter == 'r'){
            if(code == nullptr){
                cout<<"Coda vuota"<<endl;
            }else{
                remove_element(code);
            }
        }
        if(letter == 'p'){
            print_code(code);
        }
    }while(letter != 'q');
    delete_code(code);
    return 0;
}

void add_element(block*& code){
    int number;
    cout<<"Inserisci un numero: ";
    cin>>number;

    block* created=new block{number, nullptr};
    if(code == nullptr){
        code=created;
    }else{
        block* pointer=code;
        while(pointer->next != nullptr){
            pointer=pointer->next;
        }
        pointer->next=created;
    }
}

void remove_element(block*& code){
    block* pointer=code;
    code=code->next;
    delete[] pointer;
}

void print_code(block* code){
    cout<<"Coda-> ";
    while(code != nullptr){
        cout<<code->number<<" ";
        code=code->next;
    }
    cout<<endl;
}

void delete_code(block*& code){
    while(code != nullptr){
        block* pointer= code;
        code=code->next;
        delete[] pointer;
    }
    delete[] code;
}