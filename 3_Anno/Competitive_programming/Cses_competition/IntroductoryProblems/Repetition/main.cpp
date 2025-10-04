#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(long long i=a; i<b; i++)

int main(){
    string input;
    cin>>input;
    int max=0;
    int val=0;
    char lastchar;
    rep(i,0,input.size()){
        if(lastchar == input[i]){
            val += 1;
        }else{
            val = 1;
            lastchar = input[i];
        }
        if(val > max){
            max = val;
        }
    }
    cout<<max;
}