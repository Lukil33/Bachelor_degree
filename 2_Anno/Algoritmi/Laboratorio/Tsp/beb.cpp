#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>
#include "tsp.h"
#define rep(i,a,b) for(int i=a; i<b; i++)
using namespace std;

vector<vector<pair<int,int>>> listaAdiacenza; // si compone di: parte_da -> <peso,nodo_arrivo>, <peso,nodo_arrivo>,<peso,nodo_arrivo>
vector<vector<int>> matrice;
vector<int> minusLowBound;
int numNodi;

int upperBound;
ofstream out ("output.txt");

void branchAndBound(int, int);
void branchandbound_aux(vector<bool>&, vector<int>&, int, int);
int greedysearch();
int lwBound();

int main(){
    ifstream in ("input.txt");

    in >> numNodi;

    matrice.resize(numNodi, vector<int>(numNodi));
    listaAdiacenza.resize(numNodi);

    rep(i,1,numNodi){
        rep(j,0,i){
            int a;
            in >> a;
            listaAdiacenza[j].push_back(make_pair(a,i));
            listaAdiacenza[i].push_back(make_pair(a,j));
            matrice[i][j] = a;
            matrice[j][i] = a;
        }
    }

    rep(i,0,numNodi){
        sort(listaAdiacenza[i].begin(), listaAdiacenza[i].end());
    }

    upperBound = greedysearch();
    int lowerBound = lwBound();

    branchAndBound(upperBound, lowerBound);

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

    costo += matrice[pos][0];

    out<<" "<<0<<"#"<<endl;

    return costo;
}

int lwBound(){
    // Versione semplice, si può poi ottimizzare
    minusLowBound.resize(numNodi,0);
    int res = 0;
    
    unordered_map<int,set<int>> mappa;

    rep(i,0,numNodi){
        rep(j,0,numNodi-1){
            if(mappa.find(listaAdiacenza[i][j].first) == mappa.end()){
                mappa[listaAdiacenza[i][j].first] = {listaAdiacenza[i][j].second};
                res += listaAdiacenza[i][j].first;
                minusLowBound[i] = listaAdiacenza[i][j].first;
                break;
            }else if(mappa[listaAdiacenza[i][j].first].find(listaAdiacenza[i][j].second) == mappa[listaAdiacenza[i][j].first].end()){
                mappa[listaAdiacenza[i][j].first].insert(listaAdiacenza[i][j].second);
                res += listaAdiacenza[i][j].first;
                minusLowBound[i] = listaAdiacenza[i][j].first;
                break;
            }else{
                mappa[listaAdiacenza[i][j].first].erase(listaAdiacenza[i][j].second);
            }
        }
    }

    return res;
}

void branchAndBound(int uppBound, int lowBound){
    vector<bool> visited;
    vector<int> stack;

    visited.resize(numNodi, false);

    //per convenzione iniziamo sempre da 0 perche tanto è un ciclo e non cambia niente
    visited[0]=true;
    stack.push_back(0);
    branchandbound_aux(visited, stack, 0, lowBound);
}

void branchandbound_aux(vector<bool>& visited, vector<int>& stack, int costo, int lowBound){
    if(costo+lowBound < upperBound){
        if(stack.size() == numNodi){

            costo += matrice[stack.back()][0];
            if(costo < upperBound){
                rep(i,0,numNodi){
                    out<<stack[i]<<" ";
                }
                out<<stack[0]<<"#"<<endl;

                upperBound=costo;
            }
        }else{
            rep(i,0,numNodi){
                int prec=stack.back();

                if(!visited[i]){
                    stack.push_back(i);
                    visited[i]=true;
                    branchandbound_aux(visited, stack, costo+matrice[prec][i], lowBound-minusLowBound[prec]);
                    visited[i]=false;
                    stack.pop_back();
                }
            }
        }
    }
}