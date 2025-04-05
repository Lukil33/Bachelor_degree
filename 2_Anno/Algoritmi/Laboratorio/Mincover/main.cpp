#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<vector<int>> figli;
vector<int> numPadri;

int mincover(int pos,bool taken){
    int r=0;

    if(taken) r++;

    for(int f : figli[pos]){
        if(taken){
            r+=min(mincover(f,false),mincover(f,true));
        }else{
            r+=mincover(f,true);
        }
    }

    return r;
}

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    int N;
    in >> N;
    figli.resize(N);
    numPadri.resize(N,0);

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