#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(long long i=a; i<b; i++)

int main(){
    long long n;
    cin>>n;
    long long last_num = 0;
    long long res = 0;
    rep(i,0,n){
        long long new_num;
        cin>>new_num;
        if(last_num > new_num){
            res += last_num-new_num;
        }else{
            last_num = new_num;
        }
    }
    cout<<res;
}