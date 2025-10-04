#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,a,b) for(long long i=a; i<b; i++)

int main(){
    ll n, res = 0;
    cin>>n;
    rep(i,0,n){
        string str;
        cin>>str;
        if(str.length() <= 13 && str.length() >= 12){
            if(str[0] == '+' && str[1] == '3' && str[2] == '9'){
                res += 1;
            }
        }
    }
    cout<<res;
}