#include <iostream>
#include <fstream>
using namespace std;
#include "Pila.h"

int main(int argc, char * argv[]){
    if(argc != 2){
        cerr<<"Input: ./a.out <file_input>"<<endl;
        return -1;
    }

    fstream input, output;
    input.open(argv[1], ios::in);
    if(input.fail()){
        cerr<<"Error in file opening"<<endl;
        return -2;
    }

    void pila_init();

    char character;
    while(input>>character){
        pila_push(character);
    }

    pila_print();

    int counter=0;

    while(pila_top(character)){
        if(character=='('){
            counter--;
        }else if(character==')'){
            counter++;
        }else{
            cerr<<"Error in input file"<<endl;
            return -3;
        }
        if(counter<0){
            cout<<"NO"<<endl;
            break;
        }
        pila_pop();
    }
    if(counter>0){
        cout<<"NO"<<endl;
    }else if(counter==0){
        cout<<"SI"<<endl;
    }
    pila_deinit();
    return 0;
}