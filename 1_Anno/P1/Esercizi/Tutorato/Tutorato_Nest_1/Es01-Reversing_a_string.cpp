#include <iostream>
using namespace std;

const int DIM=100;

void stampa_iterativa(char* input);
void stampa_ricorsiva(char* input);
void stampa_ricorsiva_supporto(char* input, int contatore_rs);

int main(){
    char input[DIM];
        
    cout<<"Inserisci una stringa: ";
    cin>>input;
    
    cout<<"Stampa iterativa: ";
    stampa_iterativa(input);
    cout<<endl;
    cout<<"Stampa ricorsiva: ";
    stampa_ricorsiva(input);

    return 0;
}

void stampa_iterativa(char* input){
    int contatore=0;
    while(input[contatore]!='\0'){
        contatore++;
    }
    for(int i=contatore-1; i>=0; i--){
        cout<<input[i]<<" ";
    }
}

void stampa_ricorsiva(char* input){
    int contatore_rs=0;
    stampa_ricorsiva_supporto(input, contatore_rs);
    cout<<endl;
}

void stampa_ricorsiva_supporto(char* input, int contatore_rs){
    if(input[contatore_rs]!='\0'){
        contatore_rs++;
        stampa_ricorsiva_supporto(input, contatore_rs);
        contatore_rs--;
        cout<<input[contatore_rs]<<" ";
    }
}