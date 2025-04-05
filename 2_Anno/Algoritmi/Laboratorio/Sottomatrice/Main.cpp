#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    int Y, X;
    in >> Y >> X;

    vector<vector<int>> mat;

    mat.resize(Y);
    for(int y=0; y<mat.size(); y++){
        mat[y].resize(X);
        for(int x=0; x<mat[y].size(); x++){
            in >> mat[y][x];
        }
    }

    int somma_massima = 0;
    vector<int> temp_array;
    temp_array.resize(X);

    for(int y=0; y<Y; y++){
        for(int i=y; i<Y; i++){

            int res = 0;
            int somma_attuale = 0;

            for(int x=0; x<X; x++){
                temp_array[x] += mat[i][x];

                if(somma_attuale < 0){
                    somma_attuale = 0;
                }

                somma_attuale += temp_array[x];
                if(res < somma_attuale){
                    res = somma_attuale;
                }

                if(i+1 == Y){
                    temp_array[x] = 0;
                }
            }

            if(somma_massima < res){
                somma_massima = res;
            }
        }
    }

    out << somma_massima;

    return 0;
}