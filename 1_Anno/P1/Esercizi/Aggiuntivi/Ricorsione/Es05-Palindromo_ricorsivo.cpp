#include <iostream>
using namespace std;

void numero_palindromo(int numero);
int lunghezza_numero(int numero, int lunghezza);
bool ausiliaria(int& numero, int lunghezza, bool palindromo);
long pow_10(int lunghezza);
long ausiliaria_potenza( int lunghezza, long potenza);

int main(){
    int numero;

    cout<<"Inserisci un numero intero: ";
    cin>>numero;

    numero_palindromo(numero);

    return 0;
}

void numero_palindromo(int numero){
    bool palindromo=true;
    int lunghezza=0;

    lunghezza=lunghezza_numero(numero, lunghezza);
    palindromo=ausiliaria(numero, lunghezza, palindromo);

    if(palindromo==true){
        cout<<"Il numero e' palindromo"<<endl;
    }else{
        cout<<"Il numero non e' palindromo"<<endl;
    }
}

int lunghezza_numero(int numero, int lunghezza){
    if(numero==0){
        return lunghezza;
    }else{
        numero-=numero%10;
        numero/=10;
        lunghezza_numero(numero, lunghezza+1);
    }
}

bool ausiliaria(int& numero, int lunghezza, bool palindromo){
    if((palindromo==false)||(numero<=0)){
        return palindromo;
    }else{
        int cifra=numero%pow_10(lunghezza);
        cifra=(numero-cifra)/pow_10(lunghezza);
        if((numero%10)==(cifra)){
            numero=(numero%(pow_10(lunghezza)));
            numero-=(numero%10);
            numero/=10;
            ausiliaria(numero, lunghezza-2, palindromo);
        }else{
            palindromo=false;
            ausiliaria(numero, lunghezza, palindromo);
        }
    }
}

long pow_10(int lunghezza){
    long potenza=1;
    potenza=ausiliaria_potenza(lunghezza-1, potenza);
    return potenza;
}

long ausiliaria_potenza( int lunghezza, long potenza){
    if(lunghezza<=0){
        return potenza;
    }else{
        potenza*=10;
        lunghezza--;
        ausiliaria_potenza(lunghezza, potenza);
    }
}