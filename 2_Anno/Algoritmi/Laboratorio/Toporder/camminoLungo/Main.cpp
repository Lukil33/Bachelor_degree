#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<vector<int>> graph;
vector<int> numPadri;
vector<int> costo;

void maxDimCammino();
int dimCammino(int);

int main(){
    ifstream in("input.txt");

    //Inizializzo le varie variabili
    int numNodi, numArchi;
    in >> numNodi >> numArchi;

    //Inizializzo le dimensioni dei grafi
    graph.resize(numNodi);
    numPadri.resize(numNodi,0);
    costo.resize(numNodi,-1);

    //Popolo il grafo
    for(int i=0; i<numArchi; i++){
        int pos, num;
        in>> pos >> num;
        graph[pos].push_back(num);
        numPadri[num] += 1;
    }
    
    maxDimCammino();

    return 0;
}

void maxDimCammino(){
    ofstream out("output.txt");

    int maxDim = 0;
    
    for(int i=0; i<(int)numPadri.size(); i++){
        if(numPadri[i] == 0){
            int val = dimCammino(i);
            if(val > maxDim){
                maxDim = val;
            }
        }
    }
    
    out << maxDim-1;
}

int dimCammino(int start){
    int maxNumSotto = 0;
    if(costo[start] != -1){
        return costo[start]+1;
    }else{
        for(int i=0; i<(int)graph[start].size(); i++){
            int val = dimCammino(graph[start][i]);
            if(maxNumSotto < val){
                maxNumSotto = val;
            }
        }
        costo[start] = maxNumSotto;
    }
    return maxNumSotto+1;
}