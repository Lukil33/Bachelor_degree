#include <bits/stdc++.h>
#include <vector>
using namespace std;
#define ll long long
#define rep(i,a,b) for(long long i=a; i<b; i++)

vector<ll> monete;
vector<ll> vec;

ll funct(ll n){
    if(vec[n] == -1){
        vec[n] = -2;
        for(ll coin : monete){
            if(n-coin >= 0){
                ll res = funct(n - coin);
                if(res >= 0){
                    if(vec[n] < 0){
                        vec[n] = res + 1;
                    }else{
                        vec[n] = min(vec[n], res + 1);
                    }
                }
                
            }
        }
    }
    return vec[n];
}

int main(){
    ll num_monete, sum, smaller_coins = 0;
    cin >>num_monete>>sum;
    monete.resize(0);
    rep(i,0,num_monete){
        ll a;
        cin>>a;
        if(a <= sum){
            smaller_coins +=1;
        }
        monete.push_back(a);
    }
    if(smaller_coins == 0){
        cout<<-1;
    }else{
        vec.resize(sum+1, -1);
        vec[0] = 0;
        ll res = funct(sum);
        if (res == -2){
            cout << -1;
        }else{
            cout<< res;
        }
    }
}