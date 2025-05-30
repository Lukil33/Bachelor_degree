#include <iostream>
#include <fstream>
#define DIM 1000
using namespace std;

int lunghezza_parola(char word[DIM]);

int main(int argc, char* argv[]){
    if(argc!=3){
        cerr<<"Il numero di dati inseriti e' sbagliato"<<endl;
    }else{
        fstream input, output;
        output.open("output.txt", ios::out);

        char word[DIM];
        for(int g=1; g<argc; g++){
            input.open(argv[g], ios::in);
            while(input>>word){
                output<<word;
                output<<"\n";
            }
            input.close();
        }
        
        output.close();
    }
    return 0;
}

int lunghezza_parola(char word[DIM]){
    int lunghezza=0;
    while(word[lunghezza]!='\0'){
        lunghezza++;
    }
    return lunghezza;
}