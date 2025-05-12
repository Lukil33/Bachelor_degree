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

int upperBound = -1;
ofstream out ("output.txt");

void branchAndBound(int, int);
void branchandbound_aux(vector<bool>&, vector<int>&, int, int);
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

    int lowerBound = lwBound();

    branchAndBound(upperBound, lowerBound);

    return 0;
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
    if(upperBound == -1 || costo+lowBound < upperBound){
        if((int)stack.size() == numNodi){
            costo += matrice[stack.back()][0];
            if(upperBound == -1 || costo < upperBound){
                rep(i,0,numNodi){
                    out<<stack[i]<<" ";
                }
                out<<stack[0]<<"#"<<endl;

                upperBound=costo;
            }
        }else{
            rep(i,0,(int)listaAdiacenza[stack.back()].size()){
                int prec=stack.back();
                int nextElem = listaAdiacenza[prec][i].second;
                if(!visited[nextElem]){
                    stack.push_back(nextElem);
                    visited[nextElem]=true;
                    branchandbound_aux(visited, stack, costo+matrice[prec][nextElem], lowBound-minusLowBound[prec]);
                    visited[nextElem]=false;
                    stack.pop_back();
                }
            }
        }
    }
}