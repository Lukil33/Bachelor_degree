#include <iostream>
using namespace std;

void scomponi_cifra(int numero, long& somma);
void sommaricorsiva(int numero, long& somma);

int main(){
    int numero;

    cout<<"Inserire il un numero intero: ";
    cin>>numero;

    long somma=0;
    scomponi_cifra(numero, somma);

    cout<<"La somma e': "<<somma<<endl;
    return 0;
}

void scomponi_cifra(int numero, long& somma){
    if((numero/10)<1){
        sommaricorsiva(numero, somma);
        
    }else{
        int cifra=(numero%10);
        numero=numero-cifra;
        numero/=10;
        sommaricorsiva(cifra, somma);
        scomponi_cifra(numero, somma);
    }
}

void sommaricorsiva(int numero, long& somma){
    if(numero==0){
    }else{
        somma+=1;
        numero-=1;
        sommaricorsiva(numero, somma);
    }
}