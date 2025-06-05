#include <iostream>
#include <fstream>
#include <vector>
#include "conclave.h"
using namespace std;
#define freaky short
#define rep(i,a,b) for(freaky i=a; i<b; i++)

bool direction; // Gestisce la direzione nella quale ci stiamo muovendo rispetto alla stack, se dobbiamo aggiungere true, se dobbiamo eliminare false
bool running;
freaky N,M,maxNumRiunioni = 0,numRiunioniConsiderate=0, upperBound;
ofstream out("output.txt");

vector<freaky> nodoToNumRiunioni;
vector<vector<freaky>> nodoToRiunioni;
vector<vector<freaky>> riunioniToNodo;
vector<freaky> riunionePresa;
vector<freaky> stack;

void take(vector<bool>&, freaky, bool);
void freakyCover(vector<bool>, freaky);
void freakyin();
void freakyout();

int main(){
    freakyin();

    if(maxNumRiunioni == 2){
        vector<bool> visited;
        visited.resize(N,false);
        freakyCover(visited, 0);
    }
    
    return 0;
}

void take(vector<bool>& taken, freaky nodeID, bool prendi){
    taken[nodeID] = prendi;
    for(freaky riunione : nodoToRiunioni[nodeID]){
        if(!riunionePresa[riunione]){
            for(freaky node:riunioniToNodo[riunione]){
                if(!taken[node]){
                    take(taken,node,!prendi);
                }
            }
            riunionePresa[riunione] = true;
        }
    }
}

void freakyCover(vector<bool> visited, freaky start){
    // Prendi il primo nodo non nullo
    while(start < N && (nodoToNumRiunioni[start] == 0 || visited[start])){
        start += 1;
    }




    take(visited,start,true);
    take(visited,start,false);

    // Conta quale ha preso meno nodi
    int countPreso = 0, countNonPreso = 0;
    rep(i,0,N){
        countPreso += preso[i]*1;
        countNonPreso += nonPreso[i]*1;
    }

    if(countPreso > countNonPreso){
        rep(i,0,N){
            if(nonPreso[i]){
                visited[i] = true;
            }
        }
    }else{
        rep(i,0,N){
            if(preso[i]){
                visited[i] = true;
            }
        }
    }

    freakyCover(visited,start);
}

void freakyin(){
    ifstream in("input.txt");

    in>>N>>M;

    nodoToNumRiunioni.resize(N,0);
    riunionePresa.resize(M,0);
    nodoToRiunioni.resize(N);
    riunioniToNodo.resize(M);
    stack.resize(0);
    upperBound = N+1;

    // Gestione input
    rep(i,0,M){
        freaky numPartecipanti;
        in>>numPartecipanti;
        if(numPartecipanti>maxNumRiunioni){
            maxNumRiunioni = numPartecipanti;
        }
        rep(j,0,numPartecipanti){
            freaky nodo;
            in>>nodo;
            nodoToNumRiunioni[nodo] += 1;
            nodoToRiunioni[nodo].push_back(i);
            riunioniToNodo[i].push_back(nodo);
        }
    }
}

void freakyout(){
    // Gestione output
    upperBound = (freaky)stack.size();

    out<<stack.size()<<" ";
    rep(i,0,(freaky)stack.size()){
        out<<stack[i]<<" ";
    }
    out<<"#"<<endl;
}