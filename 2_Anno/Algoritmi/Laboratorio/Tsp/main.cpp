#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
//#include "tsp.h"
#define rep(i,a,b) for(int i=a; i<b; i++)
using namespace std;

vector<int> nodiCollegati;
vector<vector<pair<int,int>>> listaAdiacenza; // si compone di: parte_da -> <peso,nodo_arrivo>, <peso,nodo_arrivo>,<peso,nodo_arrivo>
int numNodiCollegati, numNodi;

ofstream out ("output.txt");

int greedysearch();

int main(){
    ifstream in ("input.txt");

    in >> numNodi;

    nodiCollegati.resize(numNodi,0);
    listaAdiacenza.resize(numNodi);

    rep(i,1,numNodi){
        rep(j,0,i){
            int a;
            in >> a;
            listaAdiacenza[j].push_back(make_pair(a,i));
            listaAdiacenza[i].push_back(make_pair(a,j));
        }
    }

    rep(i,0,numNodi){
        sort(listaAdiacenza[i].begin(), listaAdiacenza[i].end());
    }

    greedysearch();

    return 0;
}

int greedysearch(){
    int costo=0;
    vector<bool> visited;

    visited.resize(numNodi, false);

    out<<0;
    visited[0]=true;
    int pos=0;

    rep(i,0,numNodi-1){
        int min = 0;
        while(min < numNodi-1 && visited[listaAdiacenza[pos][min].second]){
            min += 1;
        }
        visited[listaAdiacenza[pos][min].second] = true;
        costo += listaAdiacenza[pos][min].first;
        out<<" "<<listaAdiacenza[pos][min].second;
        pos = listaAdiacenza[pos][min].second;
    }

    rep(i,0,numNodi-1){
        if(listaAdiacenza[pos][i].second == 0){
            costo += listaAdiacenza[pos][i].first;
        }
    }

    out<<" "<<0<<"#"<<endl;

    return costo;
}