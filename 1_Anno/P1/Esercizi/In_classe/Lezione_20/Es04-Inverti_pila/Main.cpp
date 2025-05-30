#include <iostream>
#include <fstream>
using namespace std;
#include "Pila.h"
#include "Coda.h"

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
    coda_init();

    int number;
    while(input>>number){
        pila_push(number);
    }

    pila_print();

    while(pila_top(number)){
        coda_enqueue(number);
        pila_pop();
    }

    coda_print();

    while(coda_first(number)){
        pila_push(number);
        coda_dequeue();
    }

    while(pila_top(number)){
        output<<number<<endl;
        pila_pop();
    }

    coda_deinit();
    pila_deinit();
    return 0;
}