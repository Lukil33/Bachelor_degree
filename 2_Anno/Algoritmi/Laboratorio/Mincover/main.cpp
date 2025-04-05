#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<vector<int>> figli;
vector<int> numPadri;
vector<int> DP;

int mincover(int pos,bool taken){
    int N = pos*2;
    if(!taken) N += 1;
    if(DP[N] == -1){
        int r=0;

        if(taken) r++;

        for(int f : figli[pos]){
            if(taken){
                r+=min(mincover(f,false),mincover(f,true));
            }else{
                r+=mincover(f,true);
            }
        }
        
        DP[N] = r;
    }

    return DP[N];
}

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    int N;
    in >> N;
    figli.resize(N);
    numPadri.resize(N,0);
    DP.resize(N*2,-1);

    for(int i=1; i<N; i++){
        int a,b;
        in>>a>>b;

        figli[a].push_back(b);
        numPadri[b] += 1;
    }

    for(int i=0; i<N; i++){
        if(numPadri[i] == 0){
            out<<min(mincover(i,true),mincover(i,false));
        }
    }

    return 0;
}