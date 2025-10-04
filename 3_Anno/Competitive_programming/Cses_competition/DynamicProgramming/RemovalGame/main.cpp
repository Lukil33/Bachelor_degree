#include <bits/stdc++.h>
#include <vector>
using namespace std;
#define rep(i,a,b) for(long long i=a;i<b;i++)
#define INF 26e11

vector<vector<long long>> mat;
vector<long long> elem;

long long player1(long long i, long long j);

long long player2(long long i, long long j){
    if(i==j){
        mat[i][j] = 0;
    }else{
        if(mat[i][j] == INF){
            mat[i][j] = min(player1(i+1,j),player1(i,j-1));
        }
    }
    return mat[i][j];
}

long long player1(long long i, long long j){
    if(i==j){
        mat[i][j] = elem[i];
    }else{
        if(mat[i][j] == INF){
            mat[i][j] = max(player2(i+1,j)+elem[i],player2(i,j-1)+elem[j]);
        }
    }
    return mat[i][j];
}

int main(){
    long long n;
    cin>>n;
    mat.resize(n, vector<long long>(n,INF));
    elem.resize(n);
    rep(i,0,n){
        cin>>elem[i];
    }
    cout<<player1(0,n-1);
}