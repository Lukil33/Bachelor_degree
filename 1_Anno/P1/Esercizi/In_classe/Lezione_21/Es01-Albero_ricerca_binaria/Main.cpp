#include <iostream>
#include <fstream>
#include "Albero.h"
using namespace std;

int main(int argc, char * argv[]){
    if(argc != 2){
        cerr<<"Input: ./a.out <file_input>"<<endl;
        return -1;
    }

    fstream input;
    input.open(argv[1], ios::in);
    if(input.fail()){
        cerr<<"Error in file opening"<<endl;
        return -2;
    }

    node *tree;
    albero_init();

    int number;
    while(input>>number){
        albero_insert(tree, number);
    }

    stampaAlbero(tree);

    albero_deinit();
    return 0;
}