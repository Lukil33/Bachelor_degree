#include <iostream>
#include <fstream>
#include <vector>
#include <set>
using namespace std;

vector<vector<int>> graph;
vector<pair<bool,bool>> visited;

int batMan(int, int);
void removeAllCycle(int, int&);
int countPath(vector<int>&, int, int);

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    //Inizializzo le varie variabili
    int numNodi, numArchi, start, end;
    in >> numNodi >> numArchi >> start >> end;

    //Inizializzo le dimensioni dei grafi
    graph.resize(numNodi);
    visited.resize(numNodi);

    //Popolo il grafo
    for(int i=0; i<numArchi; i++){
        int pos, num;
        in>> pos >> num;
        graph[pos].push_back(num);
    }

    out << batMan(start, end);

    return 0;
}
 
int batMan(int start, int end){
    //L'obbiettivo della funzione è quello di pulire i grafi dai cicli e successivamente di contare il numero di percorsi diversi
    removeAllCycle(start, end);

    //Inizializzo il vettore del costo e setto tutti gli elementi a 0
    vector<int> costo = {};
    costo.resize(graph.size(), -1);

    return countPath(costo, start, end);
}

void fuseArch(set<int> ciclo, int element, int& end){
    //Nella seguente funzione ispeziono tutti gli archi, se questi puntano ad un'elemento

    //Controllo che l'elemento element non sia già nel ciclo
    if(ciclo.find(element) == ciclo.end()){
        //Inserisco l'ultimo elemento visitato del ciclo
        ciclo.insert(element);

        for(int i=0; i<(int)graph[element].size(); i++){
            if(visited[graph[element][i]].first){
                fuseArch(ciclo, graph[element][i], end);
            }else{
                graph[graph.size()-1].push_back(graph[element][i]);
            }
        }

        if(element == end){
            end = (int)graph.size()-1;
        }
        //Punto al nuovo elemento
        graph[element] = {(int)graph.size()-1};
    }
}
void removeAllCycle(int element, int& end){
    //In questa funzione controllo se il nodo visitato fa parte di un ciclo e successivamente vado in ricorsione in avanti o indietro in base ai casi
    if(!visited[element].second){
        if(visited[element].first){
            //Inserisco un nuovo nodo al fondo dell'array
            visited.resize(graph.size()+1);
            graph.resize(graph.size()+1);
            set<int> ciclo;

            //Chiamo la funzione per fondere i nodi
            fuseArch(ciclo, element, end);
        }
        //Nel caso in cui non avessi chiuso un ciclo setto lo status del nodo a true e controllo i nodi figli
        visited[element].first = true;
        for(int i=0; i<(int)graph[element].size(); i++){
            removeAllCycle(graph[element][i], end);
        }
        visited[element].first = false;
        visited[element].second = true;
    }
}

int countPath(vector<int>& costo, int element, int end){
    //Questa funzione ricorsiva ha lo scopo di contare il numero di passaggi diversi fino ad un nodo finale
    int summ = 0;
    if(costo[element] != -1){
        return costo[element];
    }else if(element == end){
        summ = 1;
    }else{
        for(int i=0; i<(int)graph[element].size(); i++){
            summ += countPath(costo, graph[element][i], end);
        }
    }
    costo[element] = summ;
    return summ;
}