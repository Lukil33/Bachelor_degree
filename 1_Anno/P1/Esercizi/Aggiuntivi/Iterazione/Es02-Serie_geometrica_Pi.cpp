#include <iostream>
using namespace std;

int main(){
    float numero, somma=0;

    cout<<"Inserire un numero intero: ";
    cin>>numero;

    for(int i=1;i<=numero;i++){
        if(i%2){
            somma+=4.00/((2.00*i)-1.00);
            cout<<somma<<endl;
        }else{
            somma+=(-4.00)/((2.00*i)-1.00);
            cout<<somma<<endl;
        }
    }
    return 0;
}