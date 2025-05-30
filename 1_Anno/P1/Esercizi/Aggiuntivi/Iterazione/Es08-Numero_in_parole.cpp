#include <iostream>
using namespace std;

void conta_cifre(int numero, int * numero_cifre);
int estrai_numero(int numero, int i);
void conversione_numero(int numero);

int main(){
    int numero, numero_cifre;

    cout<<"Inserisci un numero intero: ";
    cin>>numero;

    conta_cifre(numero, &numero_cifre);
    
    for(int i=numero_cifre;i>0;i--){
        //estraggo il singolo numero
        int numero_singolo = estrai_numero(numero, i);
        //trasformo il numero nelle cifre corrispondenti
        conversione_numero(numero_singolo);
    }
    
    cout<<endl;
    return 0;
}

void conta_cifre(int numero, int * numero_cifre){
    if((numero/10)>=1){
        (*numero_cifre)++;
        numero-=(numero%10);
        numero/=10;
        conta_cifre(numero, numero_cifre);
    }else{
        (*numero_cifre)++;
    }
}

int estrai_numero(int numero, int i){
    int num10_elevato=1;
    for(int g=1;g<i;g++){
        num10_elevato*=10;
    }
    numero-=(numero%num10_elevato);
    numero/=num10_elevato;
    int numero_singolo=numero%10;
    return numero_singolo;
}

void conversione_numero(int numero){
    switch(numero){
        case 0:
            cout<<"Zero ";
            break;
        case 1:
            cout<<"Uno ";
            break;
        case 2:
            cout<<"Due ";
            break;
        case 3:
            cout<<"Tre ";
            break;
        case 4:
            cout<<"Quattro ";
            break;
        case 5:
            cout<<"Cinque ";
            break;
        case 6:
            cout<<"Sei ";
            break;
        case 7:
            cout<<"Sette ";
            break;
        case 8:
            cout<<"Otto ";
            break;
        case 9:
            cout<<"Nove ";
            break;
    }
}