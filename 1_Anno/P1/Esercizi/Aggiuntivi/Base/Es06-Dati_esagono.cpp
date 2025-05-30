#include <iostream>
using namespace std;

int main(){
    float lato_esagono;

    cout<<"Inserire il valore del lato dell'esagono: ";
    cin>>lato_esagono;

    float perimetro_esagono=lato_esagono*6;
    float area_esagono=3*((lato_esagono*lato_esagono)/2)*1.73205;

    cout<<"Il preimetro dell'esagono vale: "<<perimetro_esagono<<endl;
    cout<<"L'area dell'esagono vale: "<<area_esagono<<endl;
    return 0;
}