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
freaky N,M,numRiunioniConsiderate=0, upperBound, restart = -1;
ofstream out("output.txt");

vector<freaky> nodoToNumRiunioni;
vector<vector<freaky>> nodoToRiunioni;
vector<vector<freaky>> riunioniToNodo;
vector<freaky> riunionePresa;
vector<freaky> stack;

void frakyin();
void frakyout();
freaky findFreakyest();

int main(){
    frakyin();

    bool running = true, direction = true;

    while(running){
        if(direction){
            if(((stack.size() == upperBound-1) && (M != numRiunioniConsiderate)) || (stack.size() >= upperBound)){
                // Se il numero di nodi è già troppo elevato
                direction = false;
            }else if(numRiunioniConsiderate == M){
                // Se siamo già arrivati alla soluzione
                frakyout();
                direction = false;
            }else{
                freaky pos = findFreakyest();
                if(pos == -1){
                    // Se non ci sono più elementi dello stesso valore del max
                    direction = false;
                }else if((upperBound-stack.size()-1)*nodoToNumRiunioni[pos] < M-numRiunioniConsiderate){
                    // Se in qualsiasi caso non possiamo arrivare a comprire tutte le soluzioni nei casi minimi
                    direction = false;
                }else{
                    // Aggiungiamo il nodo alla stack
                    stack.push_back(pos);

                    // Per ogni riunione alla quale partecipava il nodo
                    for(freaky riunione : nodoToRiunioni[pos]){
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
                }
            }
        }else{
            if(stack.empty()){
                // Se la pila è vuota ed abbiamo dunque analizzato tutto
                running = false;
            }else{
                freaky pos = stack[stack.size()-1];

                // Per ogni riunione alla quale il nodo partecipava
                for(freaky riunione : nodoToRiunioni[pos]){
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

                // Se modificando l'upperBound i successivi calcoli sono inutili facciamo che rimuovere anche il penultimo elemento
                if(((stack.size() == upperBound-1) && (M != numRiunioniConsiderate)) || (stack.size() >= upperBound)){
                    direction = false;
                }else{
                    restart = pos;
                    direction = true;
                }
            }
        }
    }

    return 0;
}

freaky findFreakyest(){
    freaky pos = 0;
    if(restart == -1){
        // Troviamo il nodo che partecipa a più riunioni
        rep(i,pos+1,N){
            if(nodoToNumRiunioni[i] > nodoToNumRiunioni[pos]){
                pos = i;
            }
        }
    }else{
        pos = restart+1;
        while(pos < (freaky)nodoToNumRiunioni.size() && nodoToNumRiunioni[pos] != nodoToNumRiunioni[restart]){
            pos += 1;
        }
        restart = -1;
    }
    if(pos >= (freaky)nodoToNumRiunioni.size()) return -1;
    return pos;
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
        freaky numPartecipanti;
        in>>numPartecipanti;
        rep(j,0,numPartecipanti){
            freaky nodo;
            in>>nodo;
            nodoToNumRiunioni[nodo] += 1;
            nodoToRiunioni[nodo].push_back(i);
            riunioniToNodo[i].push_back(nodo);
        }
    }
}

void frakyout(){
    // Gestione output
    upperBound = (freaky)stack.size();

    out<<stack.size()<<" ";
    rep(i,0,(freaky)stack.size()){
        out<<stack[i]<<" ";
    }
    out<<"#"<<endl;
}