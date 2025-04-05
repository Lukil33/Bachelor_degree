#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<vector<pair<int,int>>> graph;
vector<int> costoMigliore;
vector<bool> alreadyCleaned;
vector<bool> blocked;

//Funzione wrapper principale
int powards(int);
//Funzione che elimina tutti i passaggi ai nodi non ottimali
void deleteArch(int);
//Funzione che assegna ad ogni nodo il valore minimo
void assignValue(int);
//Funzione che elmina tutti gli archi non ottimali
void findBest(int);
//Funzione che calcola la città che blocca più nodi in assoluto
int assignNumUnderCity(int);

int calculateRes(int);

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    int numNodi, numArchi, partenza;
    in >> numNodi >> numArchi >> partenza;

    //Inizializzo la dimensione del grafo e dell'array dei costi
    graph.resize(numNodi);
    costoMigliore.resize(numNodi, -1);
    alreadyCleaned.resize(numNodi, false);
    blocked.resize(numNodi, false);

    //Inizializzo i dati all'interno del grafo
    for(int i=0; i<numArchi; i++){
        int first, second, cost;
        in >> first >> second >> cost;
        graph[first].push_back(make_pair(second,cost));
        graph[second].push_back(make_pair(first,cost));
    }

    //Chiamo la funzione
    int res = powards(partenza);
    
    //Calcolo il risultato
    int numCitta = calculateRes(res);

    out<<numCitta<<endl;
    for(int i=0; i<(int)blocked.size(); i++){
        if(blocked[i]){
            out<<i<<endl;
        }
    }

    return 0;
}

int powards(int partenza){
    //Elimino prima tutti gli archi inutili e successivamente calcolo la città migliore da assediare
    deleteArch(partenza);
    return 3;
}

void deleteArch(int partenza){
    //In questa funzione assegno un costo temporaneo ai nodi e successivamente elimino i nodi non ottimali
    assignValue(partenza);
    findBest(partenza);
}

void assignValue_aus(int element){
    for(pair<int,int> i:graph[element]){
        if(costoMigliore[i.first] == -1 || costoMigliore[i.first] > costoMigliore[element] + i.second){
            costoMigliore[i.first] = costoMigliore[element] + i.second;
            assignValue_aus(i.first);
        }
    }
}
void assignValue(int partenza){
    //Assegno ad ogni nodo il proprio valore minimo
    costoMigliore[partenza] = 0;
    assignValue_aus(partenza);
}

void findBest(int element){
    //In questa funzione segno per ottimizzare che sono già passato da questo nodo, successivamente elimino tutti gli archi con passaggi non ottimali e vado in ricorsione pre gli ottimali
    alreadyCleaned[element] = true;
    for(int i = graph[element].size()-1; i >= 0; i--){
        if(costoMigliore[graph[element][i].first] != costoMigliore[element] + graph[element][i].second){
            graph[element].erase(graph[element].cbegin() + i);
        }else if(!alreadyCleaned[graph[element][i].first]){
            findBest(graph[element][i].first);
        }
    }
}

int calculateRes(int element){
    int somma = 1; 
    for(int i=0; i<(int)graph[element].size(); i++){
        somma += calculateRes(graph[element][i].first);
    }
    blocked[element] = true;
    return somma;
}