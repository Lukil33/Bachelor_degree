#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

int max_dist(vector<vector<int>>);
int bfs(vector<vector<int>>, queue<int>);

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    int num_nodi, num_archi;
    in >> num_nodi >> num_archi;

    //Popoliamo il vettore e setto la dimensione al numero di elementi
    vector<vector<int>> archi;
    archi.resize(num_nodi);

    //Popoliamo il vettore con come primo elemento 0 (falso) e successivamente gli elementi ai quali si collega
    for(int i=0; i<num_nodi; i++){
        archi[i].push_back(0);
    }
    for(int i=0; i<num_archi; i++){
        int pos1, pos2;
        in >> pos1 >> pos2;
        archi[pos1].push_back(pos2);
        archi[pos2].push_back(pos1);
    }

    out << max_dist(archi);

    return 0;
}

int max_dist(vector<vector<int>> vec){
    //Nella seguente funzione calcolo la distanza del nodo massimo di ogni nodo e prendo soltanto quella maggiore 
    int max_dist = 0;
    for(int i=0; i<(int)vec.size(); i++){
        //Creo la coda di supporto e vi pusho l'elemento dal quale bisogna partire
        queue<int> random_shit;
        random_shit.push(i);
        int val = bfs(vec, random_shit);
        if(val > max_dist){
            max_dist = val;
        }
    }
    return max_dist;
}

int bfs(vector<vector<int>> vec, queue<int> coda){
    //Nella seguente funzione calcolo la distanza del nodo massimo
    int elemento_finale = coda.back();
    vec[elemento_finale][0] = 1;
    int res = -1;

    while(!coda.empty()){
        int element = coda.front();
        coda.pop();
        for(int i=1; i<(int)vec[element].size(); i++){
            if(!vec[vec[element][i]][0]){
                coda.push(vec[element][i]);
                vec[vec[element][i]][0] = 1;
            }
        }
        if(element == elemento_finale){
            res += 1;
            elemento_finale = coda.back();
        }
    }
    return res;
}