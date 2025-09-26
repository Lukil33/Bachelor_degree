#include <bits/stdc++.h>
using namespace std;

int main(){
    long long n;
    cin >> n;
    long long res = 1;
    for(int i = 0; i < n; ++i){
        res = (res * 2) % 1000000007;
    }
    cout << res << endl;
}