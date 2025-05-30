#include <iostream>
#include <climits>
using namespace std;

void max(int a,int b =INT_MIN,int c =INT_MIN,int d =INT_MIN,int e =INT_MIN);

int main(){
    int x[5], num_variabili;

    do{
        cout<<"Inserisci il numero di variabili che vuoi inserire: ";
        cin>>num_variabili;
    }while(num_variabili<=0||num_variabili>5);
    

    for(int i=0; i<num_variabili;i++){
        cout<<"inserisci la "<<i+1<<"° variabile: ";
        cin>>x[i];
    }
    int a=x[0], b=x[1], c=x[2], d=x[3], e=x[4];
    max(a,b,c,d,e);

    return 0;
}

void max(int a,int b,int c,int d,int e){
    int Max=a;
    if(Max<b||Max<c||Max<d||Max<e){
        Max=b;
        if(Max<c||Max<d||Max<e){
            Max=c;
            if(Max<d||Max<e){
                Max=d;
                if(Max<e){
                    Max=e;
                }
            }
        }
    }
    cout<<"Il numero piu' alto e': "<<Max<<endl;
}