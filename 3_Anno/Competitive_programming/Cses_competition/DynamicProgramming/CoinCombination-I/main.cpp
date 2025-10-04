#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,a,b) for(long long i=a; i<b; i++)

vector<ll> coin;
vector<ll> dp;

ll funct(ll n){
    if(dp[n] == -1){
        dp[n] = 0;
        for(ll elem:coin){
            if(n-elem == 0){
                dp[n] = (dp[n] + 1) % 1000000007;
            }else if(n-elem > 0){
                ll res = funct(n-elem);
                if(res != -1){
                    dp[n] = (dp[n] + res) % 1000000007;
                }
            }else{
                break;
            }
        }
        if(dp[n] == 0){
            dp[n] = -1;
        }
    }
    return dp[n];
}

int main(){
    ll num_coin, sum;
    cin>>num_coin>>sum;
    rep(i,0,num_coin){
        ll a;
        cin>>a;
        if(a<=sum){
            coin.push_back(a);
        }
    }
    if(coin.empty()){
        cout<<0;
    }else{
        sort(coin.begin(),coin.end());
        dp.resize(sum+1,-1);
        dp[0] = 0;
        ll res = funct(sum);
        if(res == -1){
            cout<<0;
        }else{
            cout<<res;
        }
    }
}