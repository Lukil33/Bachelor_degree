#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(long long i=a; i<b; i++)

int main(){
    long long n;
    cin>>n;
    rep(i,0,n){
        long long y,x,res=0;
        cin>>y>>x;
        if(x>y){
            if(x%2){
                res+=(x*x)-(y-1);
            }else{
                res+=((x-1)*(x-1))+(y);
            }
        }else{
            if(y%2){
                res+=((y-1)*(y-1))+(x);
            }else{
                res+=(y*y)-(x-1);
            }
        }
        cout<<res<<endl;
    }
}