#include <iostream>
using namespace std;

long converti_numero(short numero);
void scambio_numeri(long & primo_numero, long & secondo_numero);
void riconversione_numero(long numero);

int main(){
    short primo_numero, secondo_numero;
    long primo_num_conv, secondo_num_conv;

    cout<<"Inserisci il primo numero: ";
    cin>>primo_numero;
    while(primo_numero>65535||primo_numero<-65535){
        cout<<"Il numero inserito non e' accetabile"<<endl<<"Inserisci il primo numero: ";
        cin>>primo_numero;
    }
    cout<<"Inserisci il secondo numero: ";
    cin>>secondo_numero;
    while(secondo_numero>65535||secondo_numero<-65535){
        cout<<"Il numero inserito non e' accetabile"<<endl<<"Inserisci il secondo numero: ";
        cin>>secondo_numero;
    }

    cout<<endl<<"Cifre convertite"<<endl;
    primo_num_conv=converti_numero(primo_numero);
    cout<<primo_num_conv<<endl;
    secondo_num_conv=converti_numero(secondo_numero);
    cout<<secondo_num_conv<<endl;

    scambio_numeri(primo_num_conv, secondo_num_conv);
    cout<<endl<<"Cifre dopo lo scambio"<<endl<<primo_num_conv<<endl<<secondo_num_conv<<endl;
    
    cout<<endl<<"Cifre finali"<<endl;
    riconversione_numero(primo_num_conv);
    riconversione_numero(secondo_num_conv);
    return 0;
}

long converti_numero(short numero){
    long somma=0;
    for(int i=16; i>0; i--){
        int num_elevato=1;
        for(int g=1;g<i;g++){
            num_elevato*=2;
        }
        if((numero/num_elevato)>=1){
            somma*=10;
            somma+=1;
            numero-=num_elevato;
        }else{
            somma*=10;
        }
    }
    return somma;
}

void scambio_numeri(long & primo_numero, long & secondo_numero){
    long prime_cifre=(primo_numero)%100000000, seconde_cifre=(secondo_numero)%100000000;
    primo_numero/=100000000;
    primo_numero*=100000000;
    primo_numero+=seconde_cifre;
    secondo_numero/=100000000;
    secondo_numero*=100000000;
    secondo_numero+=prime_cifre;
}

void riconversione_numero(long numero){
    short somma=0;
    for(int j=16;j>0;j--){
        long num10_elevato=1, num2_elevato=1;
        for(int g=1;g<j;g++){
            num10_elevato*=10;
        }
        for(int i=1;i<j;i++){
            num2_elevato*=2;
        }
        if((numero/num10_elevato)>=1){
            somma+=num2_elevato;
            numero-=num10_elevato;
        }
    }
    cout<<somma<<endl;
}