#include <iostream>
#include <fstream>
using namespace std;
#include "Pila.h"

int main(int argc, char * argv[]){
    if(argc != 3){
        cerr<<"Input: ./a.out <file_input> <file_output>"<<endl;
        return -1;
    }

    fstream input, output;
    input.open(argv[1], ios::in);
    output.open(argv[2], ios::out);
    if(input.fail()||output.fail()){
        cerr<<"Error in file opening"<<endl;
        return -2;
    }

    pila_init();

    int number;
    while(input>>number){
        pila_push(number);
    }

    pila_print();

    while(pila_top(number)){
        output<<number<<endl;
        pila_pop();
    }

    pila_deinit();
    return 0;
}