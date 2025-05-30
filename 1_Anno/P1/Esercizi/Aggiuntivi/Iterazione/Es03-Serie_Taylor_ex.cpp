#include <iostream>
using namespace std;

int main(){
    float numero, somma=0, x;

    cout<<"Inserire un numero di interazioni: ";
    cin>>numero;
    cout<<"Inserire un numero intero: ";
    cin>>x;

    for(int i=1;i<=numero;i++){
        float x_elevato=1, num_fattoriale=1;
        for(int g=1;g<i;g++){
            x_elevato*=x;
        }
        for(int d=1;d<i;d++){
            num_fattoriale*=d;
        }
        somma+=x_elevato/num_fattoriale;
        cout<<somma<<endl;
    }
    return 0;
}