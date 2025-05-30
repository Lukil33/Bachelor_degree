#include <iostream>
using namespace std;

void sequenza(int numero);

int main(){
    int numero;

    cout<<"Inserisci un numero intero: ";
    cin>>numero;

    if(numero<1){
        cerr<<"Numero inserito non valido"<<endl;
        exit(1);
    }

    sequenza(numero);
    return 0;
}

void sequenza(int numero){
    if(numero==1){
        cout<<numero<<endl;
    }else{
        cout<<numero<<" ";
        if((numero%2)==0){
            numero/=2;
        }else{
            numero*=3;
            numero+=1;
        }
        sequenza(numero);
    }
}