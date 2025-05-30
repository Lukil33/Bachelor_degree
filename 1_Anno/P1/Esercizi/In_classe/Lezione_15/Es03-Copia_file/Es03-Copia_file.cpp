#include <iostream>
#include <fstream>
#define DIM 100
using namespace std;

int main(int argc, char* argv[]){
    if(argc!=3){
        cerr<<"Il numero di dati inseriti e' sbagliato"<<endl;
    }else{
        fstream input, output;
        input.open(argv[1], ios::in);
        output.open(argv[2], ios::out);

        if(!(input.is_open())||!(output.is_open())){
            input.close();
            output.close();
            cerr<<"Il nome dei file inseriti e' sbagliato"<<endl;
        }else{
            char word[DIM];
            while(input.getline(word, DIM)){
                output<<word;
                output<<"\n";
            }
            input.close();
            output.close();
        }
    }
    return 0;
}