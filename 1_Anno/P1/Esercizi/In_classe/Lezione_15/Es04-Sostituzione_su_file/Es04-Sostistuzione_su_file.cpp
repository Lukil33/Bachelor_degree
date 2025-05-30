#include <iostream>
#include <fstream>
#define DIM 100
using namespace std;

int lunghezza_parola(char word[DIM]);

int main(int argc, char* argv[]){
    if(argc!=3){
        cerr<<"Il numero di dati inseriti e' sbagliato"<<endl;
    }else{
        fstream input;
        input.open(argv[1], ios::in);
        char magic_letter = argv[2][0];

        if(!(input.is_open())){
            input.close();
            cerr<<"Il nome del file inserito e' sbagliato"<<endl;
        }else{
            char word[DIM];
            while(input.getline(word, DIM)){
                int lunghezza = lunghezza_parola(word);
                for(int i=0; i<lunghezza; i++){
                    if(word[i]==magic_letter){
                        cout<<"?";
                    }else{
                        cout<<word[i];
                    }
                }
                cout<<"\n";
            }
            input.close();
        }
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