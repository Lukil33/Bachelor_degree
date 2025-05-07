#include <iostream>
#include <fstream>
#include <vector>
#include "tsp.h"
#define rep(i,a,b) for(int i=a; i<b; i++)
using namespace std;

class UF{
    int *id, cnt, *sz;
    public:
    // Create an empty union find data structure with N isolated sets.
    UF(int N) {
        cnt = N; id = new int[N]; sz = new int[N];
        for (int i = 0; i<N; i++)  id[i] = i, sz[i] = 1; }
    ~UF() { delete[] id; delete[] sz; }

    // Return the id of component corresponding to object p.
    int find(int p) {
        int root = p;
        while (root != id[root])    root = id[root];
        while (p != root) { int newp = id[p]; id[p] = root; p = newp; }
        return root;
    }
    // Replace sets containing x and y with their union.
    void merge(int x, int y) {
        int i = find(x); int j = find(y); if (i == j) return;
        // make smaller root point to larger one
        if (sz[i] < sz[j]) { id[i] = j, sz[j] += sz[i]; }
        else { id[j] = i, sz[i] += sz[j]; }
        cnt--;
    }
    // Are objects x and y in the same set?
    bool connected(int x, int y) { return find(x) == find(y); }
    // Return the number of disjoint sets.
    int count() { return cnt; }
};

vector<int> nodiCollegati;
vector<vector<pair<int,int>>> pesoCollegamenti;
int numNodiCollegati, numNodi;

int main(){
    ifstream in ("input.txt");
    ofstream out ("output.txt");

    in >> numNodi;

    nodiCollegati.resize(numNodi,0);
    pesoCollegamenti.resize(1001);

    rep(i,1,numNodi){
        rep(j,0,i){
            int a;
            in >> a;
            pesoCollegamenti[a].push_back(make_pair(i,j));
        }
    }

    UF gino(numNodi);

    bool notEnded = true;
    int minimum = 0;
    while(notEnded){
        if(pesoCollegamenti[minimum].empty()){
            minimum += 1;
        }else{
            pair<int,int> arco = pesoCollegamenti[minimum].back();
            if((nodiCollegati[arco.first] < 2 && nodiCollegati[arco.second] < 2) || (gino.connected(arco.first, arco.second) && numNodiCollegati == numNodi-2)){
                gino.merge(arco.first,arco.second);
                nodiCollegati[arco.first] += 1;
                nodiCollegati[arco.second] += 1;
                numNodiCollegati += (nodiCollegati[arco.first]+1)%2 + (nodiCollegati[arco.second]+1)%2;
            }
            pesoCollegamenti[minimum].pop_back();
        }
    }

    return 0;
}