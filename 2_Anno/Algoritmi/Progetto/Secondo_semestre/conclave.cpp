#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <unordered_map>
#include "conclave.h"
using namespace std;
#define rep(i,a,b) for(short i=a; i<b; i++)

bool direction; // Gestisce la direzione nella quale ci stiamo muovendo rispetto alla stack, se dobbiamo aggiungere true, se dobbiamo eliminare false
bool running;
short N,M,numRiunioniConsiderate=0, upperBound;
ofstream out("output.txt");

vector<short> nodoToNumRiunioni;
vector<vector<short>> nodoToRiunioni;
vector<vector<short>> riunioniToNodo;
vector<short> riunionePresa;
vector<short> stack;

void freaky();
void frakyin();
void frakyout();

int main(){
    frakyin();

    freaky();

    return 0;
}

void freaky(){
    if(((stack.size() == upperBound-1) && (M != numRiunioniConsiderate)) || (stack.size() >= upperBound)) return;
    if(numRiunioniConsiderate == M){frakyout();return;}
    
    // Troviamo il nodo che partecipa a più riunioni
    short pos = 0, sec = -1;
    vector<short> max = {0};
    rep(i,1,N){
        if(nodoToNumRiunioni[i] > nodoToNumRiunioni[pos]){
            sec = pos;
            max.clear();
            pos = i;
            max.push_back(i);
            //max.insert(max.begin(),i);
        }else if(nodoToNumRiunioni[i] == nodoToNumRiunioni[pos]){
            max.push_back(i);
            //max.insert(max.begin(),i);
        }else if(nodoToNumRiunioni[i] > nodoToNumRiunioni[sec]){
            sec = i;
        }
    }

    // Per ogni nodo con il valore massimo di Riunioni
    for(short i:max){
        if(upperBound-stack.size()-1 > max.size()){
            if(max.size()*nodoToNumRiunioni[pos]+(upperBound-stack.size()-1-max.size())*nodoToNumRiunioni[sec] < M-numRiunioniConsiderate) return;
        }else{
            if((upperBound-stack.size()-1)*nodoToNumRiunioni[pos] < M-numRiunioniConsiderate) return;
        }
        
        // Aggiungiamo il nodo alla stack
        stack.push_back(i);

        // Per ogni riunione alla quale partecipava il nodo
        for(short riunione : nodoToRiunioni[i]){
            // Se la riunione non è ancora stata considerata
            if(riunionePresa[riunione] == 0){
                // Per ogni nodo all'interno della riunione
                for(short nodo : riunioniToNodo[riunione]){
                    // Diminuiamo di 1 il numero di riunioni alle quali fa parte
                    nodoToNumRiunioni[nodo] -= 1;
                }
                numRiunioniConsiderate += 1;
            }
            riunionePresa[riunione] += 1;
        }

        freaky();

        // Per ogni riunione alla quale il nodo partecipava
        for(short riunione : nodoToRiunioni[i]){
            riunionePresa[riunione] -= 1;
            // Se la riunione veniva considerata solo da lui
            if(riunionePresa[riunione] == 0){
                // Per ogni nodo all'interno della riunione
                for(short nodo : riunioniToNodo[riunione]){
                    // Aumentiamo di 1 il numero di riunioni alle quali fa parte
                    nodoToNumRiunioni[nodo] += 1;
                }
                numRiunioniConsiderate -= 1;
            }
        }

        // Rimuoviamo il nodo dalla stack
        stack.pop_back();
        if(((stack.size() == upperBound-1) && (M != numRiunioniConsiderate)) || (stack.size() >= upperBound)) return;
    }
}

void frakyin(){
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
        short numPartecipanti;
        in>>numPartecipanti;
        rep(j,0,numPartecipanti){
            short nodo;
            in>>nodo;
            nodoToNumRiunioni[nodo] += 1;
            nodoToRiunioni[nodo].push_back(i);
            riunioniToNodo[i].push_back(nodo);
        }
    }
}

void frakyout(){
    // Gestione output
    upperBound = (short)stack.size();

    out<<stack.size()<<" ";
    rep(i,0,(short)stack.size()){
        out<<stack[i]<<" ";
    }
    out<<"#"<<endl;
}