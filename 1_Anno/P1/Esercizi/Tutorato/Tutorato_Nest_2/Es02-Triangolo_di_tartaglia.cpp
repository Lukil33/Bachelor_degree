#include <iostream>
using namespace std;
#define DIM 100

void tartaglia(int T[DIM][DIM], int n);

int main(){
    int n, T[DIM][DIM];

    cout<<"Inserire la dimensione del triangolo: ";
    cin>>n;
    

    tartaglia(T, n);

    return 0;
}

void tartaglia(int T[DIM][DIM], int n){
    for(int d=0;d<n;d++){
        if(d==0){
            T[d][0]=1;
        }else{
            T[d][0]=0;
        }
        cout<<T[d][0]<<" ";
    }
    cout<<endl;
    for(int i=1;i<n;i++){
        for(int g=0;g<n;g++){
            if(g==0){
                T[g][i]=1;
            }else{
                T[g][i]=(T[g-1][i-1])+(T[g][i-1]);
            }
            cout<<T[g][i]<<" ";
        }
        cout<<endl;
    }
}