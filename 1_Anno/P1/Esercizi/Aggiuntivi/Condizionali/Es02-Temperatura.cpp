#include <iostream>
using namespace std;

int main(){
    float temperatura;

    cout<<"Inserire il valore della temperatura: ";
    cin>>temperatura;

    
    if(temperatura<-273.15){
        cout<<"Temperatura impossibile"<<endl;
    }else if(temperatura>=-273.15&&temperatura<=0.0){
        cout<<"Fa freddo!"<<endl;
    }else if(temperatura>0.0&&temperatura<=18.00){
        cout<<"Temperatura cosi' cosi'"<<endl;
    }else if(temperatura>18.00&&temperatura<=30.00){
        cout<<"Temperatura accettabile"<<endl;
    }else if(temperatura>30.00){
        cout<<"Fa caldo!"<<endl;
    }
    return 0;
}