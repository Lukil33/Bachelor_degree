#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

long long int pillole(int);

int main(){
    ifstream in ("input.txt");
    ofstream out ("output.txt");

    int n;
    in >> n;

    out << pillole(n);

    return 0;
}

long long int pillole_rec(int i, int m, vector<vector<long long int>>& memo){
    if(memo[i][m] != -1){
        return memo[i][m];
    }else{
        if(i == 0){
            memo[i][m] = 1;
            return memo[i][m];
        }else{
            memo[i][m] = pillole_rec(i-1,m+1,memo);
            if(m > 0){
                memo[i][m] += pillole_rec(i,m-1,memo);
            }
            return memo[i][m];
        }
    }
}

long long int pillole(int n){
    vector<vector<long long int>> memoization;
    memoization.resize(n+1,vector<long long int>(n+1,-1));
    return pillole_rec(n,0,memoization);
}