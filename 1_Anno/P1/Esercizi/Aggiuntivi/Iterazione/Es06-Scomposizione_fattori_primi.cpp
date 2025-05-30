#include <iostream>
using namespace std;

int main(){
    int numero, divisori=0;

    cout<<"Inserici un numero da scomporre in fattori primi: ";
    cin>>numero;

    for(int i=2;i<numero;i++){
        if((numero%i)==0){
            cout<<i<<" ";
            divisori++;
        }
    }
    if(divisori==0){
        cout<<"1 "<<numero;
    }
    cout<<endl;
    return 0;
}