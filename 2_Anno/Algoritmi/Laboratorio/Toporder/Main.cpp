#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

vector<vector<int>> graph;
vector<int> numPadri;
vector<int> res;
queue<int> coda;

void createvector();
void printvector();

int main(){
    ifstream in("input.txt");

    //Inizializzo le varie variabili
    int numNodi, numArchi;
    in >> numNodi >> numArchi;

    //Inizializzo le dimensioni dei grafi
    graph.resize(numNodi);
    numPadri.resize(numNodi,0);

    //Popolo il grafo
    for(int i=0; i<numArchi; i++){
        int pos, num;
        in>> pos >> num;
        graph[pos].push_back(num);
        numPadri[num] += 1;
    }

    //Butto tutto dentro alla coda
    for(int i=0; i<(int)numPadri.size(); i++){
        if(numPadri[i] == 0){
            coda.push(i);
        }
    }
    
    createvector();
    printvector();

    return 0;
}

void createvector(){
    while(!coda.empty()){
        int felement = coda.front();
        res.push_back(felement);
        for(int i=0; i<(int)graph[felement].size(); i++){
            numPadri[graph[felement][i]] -= 1;
            if(numPadri[graph[felement][i]] == 0){
                coda.push(graph[felement][i]);
            }
        }
        coda.pop();
    }
}

void printvector(){
    ofstream out("output.txt");

    for(int i=0; i<(int)res.size(); i++){
        out << res[i] << " ";
    }
}