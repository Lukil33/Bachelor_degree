#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    string first, second;
    vector<vector<int>> DP;
    in>>first>>second;
    
    DP.resize(first.size()+1, vector<int>(second.size()+1, 0));

    for(int x=1; x<=(int)first.size(); x++){
        for(int y=1; y<=(int)second.size(); y++){
            if(first[x-1] == second[y-1]){
                DP[x][y] = DP[x-1][y-1]+1;
            }else{
                DP[x][y] = max(DP[x-1][y], DP[x][y-1]);
            }
        }
    }

    out<<DP[first.size()][second.size()];
    return 0;
}