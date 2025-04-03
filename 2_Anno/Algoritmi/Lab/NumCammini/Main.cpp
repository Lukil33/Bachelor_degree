#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

pair<int,int> minimum_path(vector<vector<int>>, int, int);
pair<int,int> min_path_aus(vector<vector<int>>, queue<pair<int,bool>>, int);
void printqueue(queue<pair<int,bool>> coda);

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    int num_nodi, num_archi, nodo_iniziale, nodo_finale;
    in >> num_nodi >> num_archi >> nodo_iniziale >> nodo_finale;

    //Creo il vettore e setto la dimensione al numero di elementi
    vector<vector<int>> archi;
    archi.resize(num_nodi);

    //Inserisco ad ogni nodo i nodi ai quali punta
    for(int i=0; i<num_archi; i++){
        int pos1, pos2;
        in >> pos1 >> pos2;
        archi[pos1].push_back(pos2);
    }

    pair<int,int> res = minimum_path(archi, nodo_iniziale, nodo_finale);

    out << res.first << " " << res.second;

    return 0;
}

pair<int,int> minimum_path(vector<vector<int>> vec, int n_iniz, int n_final){
    //Nella seguente funzione calcolo la distanza minima dal nodo iniziale al nodo finale e conto il numero di volte che questa accade
    
    //Creo la coda di supporto e vi pusho l'elemento dal quale bisogna partire
    queue<pair<int,bool>> random_shit;
    random_shit.push(make_pair(n_iniz,true));

    return min_path_aus(vec, random_shit, n_final);
}

pair<int,int> min_path_aus(vector<vector<int>> vec, queue<pair<int,bool>> coda, int n_final){
    //Nella seguente funzione calcolo la distanza del nodo massimo

    //Setto le variabili iniziali
    bool end_cicle = false;
    int distanza = 0;
    int num_elementi = 0;

    //Faccio partire il ciclo che terminerà solamente se avrà trovato l'elemento cercato o se la coda sarà vuota
    while(!coda.empty() && !end_cicle){
        int element = coda.front().first;
        for(int i=0; i<(int)vec[element].size(); i++){
            if(vec[element][i] == n_final){
                num_elementi += 1;
            }
            coda.push(make_pair(vec[element][i],false));
        }

        //Quando si è arrivati alla fine di una profondità e 
        if(coda.front().second){
            distanza += 1;
            coda.back().second = true;
            if(num_elementi != 0){
                end_cicle = true;
            }
        }
        coda.pop();
    }

    return make_pair(distanza,num_elementi);
}

void printqueue(queue<pair<int,bool>> coda){
    if(!coda.empty()){
        cout<< coda.front().first << " ";
        coda.pop();
        printqueue(coda);
    }
}