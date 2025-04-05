#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int funzione(vector<vector<int>>&, int);

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    int num_nodi, len, pos_partenza;
    in >> num_nodi >> len >> pos_partenza;

    vector<vector<int>> collegamenti;
    collegamenti.resize(num_nodi);

    for(int i=0; i<num_nodi; i++){
        collegamenti[i].push_back(0);
    }
    for(int i=0; i<len; i++){
        int pos, visita;
        in >> pos >> visita;
        collegamenti[pos].push_back(visita);
    }

    out << funzione(collegamenti, pos_partenza);

    return 0;
}

int funzione(vector<vector<int>>& colleg, int pos_iniziale){
    colleg[pos_iniziale][0] = 1;
    int res = 1;
    for(int i=1; i<(int)colleg.at(pos_iniziale).size(); i++){
        if(!colleg.at(colleg.at(pos_iniziale).at(i)).at(0)){
            res += funzione(colleg,colleg.at(pos_iniziale).at(i));
        }
    }
    return res;
}