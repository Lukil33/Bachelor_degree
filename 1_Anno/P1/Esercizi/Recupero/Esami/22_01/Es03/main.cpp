#include <iostream>
#include <fstream>

using namespace std;

struct nodo {
    int value;
    nodo* left;
    nodo* right;
};
typedef nodo* albero;

void order(int*, int&, int);
nodo* generatetree(int*, int min, int);
void stampaAlbero(albero radice, int spazio=0);

int main(int argc, char* argv[]){
    if(argc != 2){
        cerr<<"Error: ./a.out <input_file>"<<endl;
        return -1;
    }
    fstream input;
    input.open(argv[1], ios::in);
    if(input.fail()){
        cerr<<"Error during file opening"<<endl;
        return -2;
    }

    int array[100];
    int num;
    int counter = 0;
    while(input>>num){
        order(array, counter, num);
    }

    nodo* tree;
    tree = generatetree(array, 0, counter-1);

    stampaAlbero(tree);

    input.close();
    return 0;
}

void order(int* array, int& counter, int num){
    bool valid = true;
    int exit = 0;
    for(int i=0; i<counter && valid; i++){
        if(num <= array[i]){
            valid = false;
            exit = i;
        }
    }
    if(valid){
        array[counter] = num;
    }else{
        for(int i=counter+1; i>exit; i--){
            array[i] = array[i-1];
        }
        array[exit] = num;
    }
    counter+=1;
}

nodo* generatetree(int* a, int min, int max){
    int c = (max+min)/2;
    if(min == max){
        cout<<"palle"<<endl;
        return new nodo{a[c], nullptr, nullptr};
    }else if(c == min){
        return new nodo{a[c], nullptr, generatetree(a, c+1, max)};
    }else{
        return new nodo{a[c], generatetree(a, min, c-1), generatetree(a, c+1, max)};
    }
}

/** Stampa dell'albero */
void stampaAlbero(albero radice, int spazio){
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