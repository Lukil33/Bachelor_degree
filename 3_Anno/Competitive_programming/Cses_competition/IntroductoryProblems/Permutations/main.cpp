#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(long long i=a;i<b;i++)

int main(){
    long long n;
    cin>>n;
    switch(n){
        case 1: cout<<1; break;
        case 2: case 3: cout<<"NO SOLUTION"; break;
        default: {
            long long newN=n;
            if(!(n%2)){
                newN-=1;
            }
            for(long long i=newN; i>0; i-=2){
                cout<<i<<" ";
            }
            newN=n;
            if(n%2){
                newN-=1;
            }
            for(long long i=newN; i>0; i-=2){
                cout<<i<<" ";
            }
        }
    }
}