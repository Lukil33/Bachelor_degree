#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <unordered_map>
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

void freakyBig();
void freakySmall();
void freakyin();
void freakyout();

int main(){
    freakyin();

    if(N < 20){
        freakySmall();
    }else{
        freakyBig();
    }

    return 0;
}

void freakyBig(){
    if(((stack.size() == upperBound-1) && (M != numRiunioniConsiderate)) || (stack.size() >= upperBound)) return;
    if(numRiunioniConsiderate == M){freakyout();return;}
    
    // Troviamo il nodo che partecipa a più riunioni
    freaky pos = 0;
    vector<freaky> max = {0};
    rep(i,1,N){
        if(nodoToNumRiunioni[i] > nodoToNumRiunioni[pos]){
            max.clear();
            pos = i;
            max.push_back(i);
            //max.insert(max.begin(),i);
        }else if(nodoToNumRiunioni[i] == nodoToNumRiunioni[pos]){
            max.push_back(i);
            //max.insert(max.begin(),i);
        }
    }

    // Per ogni nodo con il valore massimo di Riunioni
    for(freaky i:max){
        if((stack.size() != 0) && (upperBound-stack.size()-1)*nodoToNumRiunioni[pos] < M-numRiunioniConsiderate) return;
        
        // Aggiungiamo il nodo alla stack
        stack.push_back(i);

        // Per ogni riunione alla quale partecipava il nodo
        for(freaky riunione : nodoToRiunioni[i]){
            // Se la riunione non è ancora stata considerata
            if(riunionePresa[riunione] == 0){
                // Per ogni nodo all'interno della riunione
                for(freaky nodo : riunioniToNodo[riunione]){
                    // Diminuiamo di 1 il numero di riunioni alle quali fa parte
                    nodoToNumRiunioni[nodo] -= 1;
                }
                numRiunioniConsiderate += 1;
            }
            riunionePresa[riunione] += 1;
        }

        freakyBig();

        // Per ogni riunione alla quale il nodo partecipava
        for(freaky riunione : nodoToRiunioni[i]){
            riunionePresa[riunione] -= 1;
            // Se la riunione veniva considerata solo da lui
            if(riunionePresa[riunione] == 0){
                // Per ogni nodo all'interno della riunione
                for(freaky nodo : riunioniToNodo[riunione]){
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

void freakySmall(){
    if(((stack.size() == upperBound-1) && (M != numRiunioniConsiderate)) || (stack.size() >= upperBound)) return;
    if(numRiunioniConsiderate == M){freakyout();return;}

    // Per ogni nodo con il valore massimo di Riunioni
    rep(i,0,N){
        if(nodoToNumRiunioni[i] != 0){
            // Aggiungiamo il nodo alla stack
            stack.push_back(i);

            // Per ogni riunione alla quale partecipava il nodo
            for(freaky riunione : nodoToRiunioni[i]){
                // Se la riunione non è ancora stata considerata
                if(riunionePresa[riunione] == 0){
                    // Per ogni nodo all'interno della riunione
                    for(freaky nodo : riunioniToNodo[riunione]){
                        // Diminuiamo di 1 il numero di riunioni alle quali fa parte
                        nodoToNumRiunioni[nodo] -= 1;
                    }
                    numRiunioniConsiderate += 1;
                }
                riunionePresa[riunione] += 1;
            }

            freakySmall();

            // Per ogni riunione alla quale il nodo partecipava
            for(freaky riunione : nodoToRiunioni[i]){
                riunionePresa[riunione] -= 1;
                // Se la riunione veniva considerata solo da lui
                if(riunionePresa[riunione] == 0){
                    // Per ogni nodo all'interno della riunione
                    for(freaky nodo : riunioniToNodo[riunione]){
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