#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
using namespace std;

int zaino(vector<int>, vector<int>, int, int);

int main(){
    ifstream in ("input.txt");
    ofstream out ("output.txt");

    int maxPeso, n;
    in >> maxPeso >> n;

    vector<int> peso;
    vector<int> value;

    peso.resize(n);
    value.resize(n);

    for(int i=0; i<n; i++){
        int f,s;
        in >> f >> s;
        peso[i] = f;
        value[i] = s;
    }

    out << zaino(peso,value,n,maxPeso);

    return 0;
}

int zaino(vector<int> peso, vector<int> value, int n, int c){
    vector<int> vec;
    vec.resize(c+1,0);

    for(int elem=0; elem<n; elem++){
        for(int i=c+1; i>=0; i--){
            if(i < peso[elem]){
                vec[i] = vec[i];
            }else{
                if(vec[i] >= vec[i-peso[elem]]+value[elem]){
                    vec[i] = vec[i];
                }else{
                    vec[i] = vec[i-peso[elem]]+value[elem];
                }
            }
        }
    }
    
    return vec[c];
}