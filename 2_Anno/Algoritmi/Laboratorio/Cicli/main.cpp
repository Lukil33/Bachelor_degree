#include <bits/stdc++.h>
using namespace std;

int numNodi;
vector<vector<int>> collegamenti;
vector<vector<int>> res;
vector<int> exist;

vector<int> search(int);

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");
    
    int M, Q;
    in>>numNodi>>M>>Q;

    collegamenti.resize(numNodi);
    res.resize(numNodi);
    exist.resize(numNodi, false);

    for(int i=0; i<M; i++){
        int a, b;
        in>>a>>b;
        collegamenti[a].push_back(b);
        collegamenti[b].push_back(a);
    }

    for(int i=0; i<Q; i++){
        int a,b;
        in>>a>>b;
        res[a] = search(a);
        out<<res[a][b]<<endl;
    }

    return 0;
}

void aus(vector<int>& distance, int Node, int counter){
    distance[Node] = counter;
    for(int figlio:collegamenti[Node]){
        if(distance[figlio] == -1){
            aus(distance, figlio, counter+1);
        }
    }
}

vector<int> search(int Node){
    if(!exist[Node]){
        exist[Node] = true;
        vector<int> distance;
        distance.resize(numNodi, -1);
        aus(distance, Node, 0);
        return distance; 
    }else{
        return res[Node];
    }
}