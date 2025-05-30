#include <iostream>
using namespace std;

void spazi(int numero_spazi);
void asterischi(int numero_asterischi);

int main(){
    int numero;

    cout<<"Inserisci un numero intero: ";
    cin>>numero;
    int lunghezza=(numero*2)-1;

    //stampo la parte superiore del rombo
    for(int i=numero-1;i>0;i--){
        int numero_asterischi_alti=lunghezza-(i*2);
        spazi(i);
        asterischi(numero_asterischi_alti);
        cout<<endl;
    }

    //stampo la parte centrale del rombo
    asterischi(lunghezza);
    cout<<endl;

    //stampo la parte inferiore del rombo
    for(int g=1;g<lunghezza;g++){
        int numero_asterischi_bassi=lunghezza-(g*2);
        spazi(g);
        asterischi(numero_asterischi_bassi);
        cout<<endl;
    }
    return 0;
}

void spazi(int numero_spazi){
    for(int f=0;f<numero_spazi;f++){
        cout<<" ";
    }
}

void asterischi(int numero_asterischi){
    for(int q=0;q<numero_asterischi;q++){
        cout<<"*";
    }
}