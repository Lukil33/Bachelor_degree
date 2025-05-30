#include <iostream>
#include <cmath>
using namespace std;

double std_deviation(double x[10], int n);

int main(){
    double x[10]={1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int n;

    cout<<"Inserisci la lunghezza dell' array: ";
    cin>>n;

    cout<<"La deviazione standard e': "<<sqrt(std_deviation(x, n))<<endl;
    return 0;
}

double std_deviation(double x[10], int n){
    double media=0.00, deviazione=0.00;
    for(int g=0; g<n; g++){
        media+=x[g];
    }
    media/=n;
    for(int i=0; i<n; i++){
        deviazione+=(x[i]-media)*(x[i]-media);
    }
    deviazione/=(n-1);
    return deviazione;
}