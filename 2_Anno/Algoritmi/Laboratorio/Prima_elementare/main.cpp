#include <iostream>
#include <vector>
using namespace std;

string palle;
vector<vector<int>> dp;

int res(int n, int m){
    if(dp[n][m] != 0){
        return dp[n][m];
    }else{
        if(n == 0){
            dp[n][m] = 1;
            return 1;
        }else if(m == 0){
            dp[n][m] = 1;
            return 1;
        }else{
            dp[n][m] = res(n-1,m) + res(n,m-1);
            return dp[n][m];
        }
    }
}

int conta_numeri(int n, int m){
    dp.resize(n+1, vector<int>(m+1, 0));
    return res(n,m);
}

void stampa_caratteri(int n,int m){
    if(n != 0 || m != 0){
        if(n != 0){
            palle.push_back('n');
            stampa_caratteri(n-1,m);
            palle.pop_back();
        }
        if(m != 0){
            palle.push_back(' ');
            stampa_caratteri(n,m-1);
            palle.pop_back();
        }
    }else{
        cout<<palle<<endl;
    }
}

int main(){
    int n,m;
    cout<<"Inserire il numero di R e di G: ";
    cin>>n>>m;

    cout<<"Il numero di stringhe è: "<<conta_numeri(n,m)<<endl;
    stampa_caratteri(n,m);
}