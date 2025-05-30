#include <iostream>
using namespace std;

int cerca_numero(int riga, int colonna);
int ausiliaria(int riga, int colonna, int numero);

int main(){
    int riga, colonna;

    cout<<"Inserire la riga del Triangolo di Pascal: ";
    cin>>riga;

    cout<<"Inserisci la colonna: ";
    cin>>colonna;
    if((colonna>riga)||(colonna<1)){
        cerr<<"Il valore della colonna inserito non e' valido"<<endl;
        exit(1);
    }

    cout<<"Il numero cercato e': "<<cerca_numero(riga, colonna)<<endl;
    return 0;
}

int cerca_numero(int riga, int colonna){
    int numero=0;
    numero = ausiliaria(riga, colonna, numero);
    return numero;
}

int ausiliaria(int riga, int colonna, int numero){
    if(colonna>=riga){
        numero=1;
        return numero;
    }
    if(colonna<=1){
        numero=1;
        return numero;
    }
    numero=ausiliaria(riga-1,colonna-1,numero)+ausiliaria(riga-1,colonna, numero);
    return numero;
}