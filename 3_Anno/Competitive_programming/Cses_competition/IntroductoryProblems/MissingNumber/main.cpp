#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(long long i=a;i<b;i++)

int main(){
    long long n;
    cin>>n;
    vector<long long> vec;
    vec.resize(n+1,true);
    rep(i,1,n){
        long long a;
        cin>>a;
        vec[a] = false;
    }
    rep(i,1,n+1){
        if(vec[i]){
            cout<<i;
        }
    }
    return 0;
}