#include <iostream>
using namespace std;

int main(){
    long numero_binario, numero_finale=0;
    int contatore=0;

    cout<<"Inserisci il numero binario: ";
    cin>>numero_binario;

//Ciclo per ogni cifra tranne che per la piu' grande
    while((numero_binario/10)>=1){

        //elevo 10 per capire la posizione della cifra
        long num10_elevato=1;
        for(int g=1;g<=contatore;g++){
            num10_elevato*=10;
        }
        
        //cambio gli 0 in 1
        if((numero_binario%10)==0){
            numero_finale+=(1)*num10_elevato;
        }
        numero_binario-=(numero_binario%10);
        numero_binario/=10;
        contatore++;
    }
/*Il programma stampa dal secondo numero in poi in quanto il primo e' forzatamente un 1*/
    cout<<"L'opposto del numero richiesto e': "<<numero_finale<<endl;
    return 0;
}