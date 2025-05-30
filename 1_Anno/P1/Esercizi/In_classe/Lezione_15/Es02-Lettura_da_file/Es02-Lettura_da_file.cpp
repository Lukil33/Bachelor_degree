#include <iostream>
#include <fstream>
#define DIM 100
using namespace std;

int main(int argc, char* argv[]){
    if(argc!=2){
        cerr<<"Il numero di dati inseriti e' sbagliato"<<endl;
    }else{
        fstream input;
        input.open(argv[1], ios::in);

        if(!(input.is_open())){
            input.close();
            cerr<<"Il nome del file inserito e' sbagliato"<<endl;
        }else{
            char word[DIM];
            while(input.getline(word, DIM)){
                cout<<word<<"\n";
            }
            input.close();
        }
    }
    return 0;
}