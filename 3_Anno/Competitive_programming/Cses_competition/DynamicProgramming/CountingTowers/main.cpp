#include <bits/stdc++.h>
#include <vector>
using namespace std;
#define rep(i,a,b) for(long long i=a;i<b;i++)
#define INF 26e11

vector<vector<long long>> mat;

long long fun(long long h1, long long h2){
    if(h1==0 && h2==0){
        mat[h1][h2] = 1;
    }else{
        if(mat[h1][h2] == INF){
            mat[h1][h2] = 0;
            if(h1 == h2){
                rep(i,1,h1){
                    mat[h1][h2] += fun(h1-i,h2)+fun(h1-i,h2-i)+fun(h1,h2-i);
                }
            }else if(h1 > h2){
                rep(i,1,h1){
                    mat[h1][h2] += fun(h1-i,h2);
                }
            }else{
                rep(i,1,h2){
                    mat[h1][h2] += fun(h1,h2-i);
                }
            }
        }
    }
    return mat[h1][h2]%1000000007; 
}

int main(){
    long long n;
    cin>>n;
    rep(i,0,n){
        long long num;
        cin>>num;
        mat.resize(num+1,vector<long long>(num+1,INF));
        cout<<fun(num,num)<<endl;
    }
}