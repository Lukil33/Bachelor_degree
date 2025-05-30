#include <iostream>
#include <cmath>
using namespace std;

double std_deviation(double x[10], int n);
double std_deviation_ausiliary(double x[10], int n, double media, double deviazione);

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
    std_deviation_ausiliary(x, n, media, deviazione);
    for(int i=0; i<n; i++){
        deviazione+=(x[i]-media)*(x[i]-media);
    }
    deviazione/=(n-1);
    return deviazione;
}

double std_deviation_ausiliary(double x[10], int n, double media, double deviazione){
    if(n<0){
        return deviazione;
    }else{
        deviazione+=(x[n]-media)*(x[n]-media);
        std_deviation_ausiliary(x, n-1, media, deviazione);
    }
}