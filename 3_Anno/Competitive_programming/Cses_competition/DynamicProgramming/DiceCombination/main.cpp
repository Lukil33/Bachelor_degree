#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,a,b) for(long long i=a; i<b; i++)

vector<int> vec;

ll funct(ll n){
    if(vec[n] == -1){
        vec[n] = 0;
        if(n <= 6){
            vec[n] += 1;
        }
        rep(i,1,7){
            if(n-i >= 0){
                vec[n] = (vec[n] + funct(n - i)) % 1000000007;
            }
        }
    }
    return vec[n];
}

int main(){
    ll n;
    cin >> n;
    vec.resize(n+1, -1);
    vec[0] = 0;
    cout<<funct(n);
}