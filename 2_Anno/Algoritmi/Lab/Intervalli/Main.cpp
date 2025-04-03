#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

void palle(vector<pair<int,int>>);

int main(){
    ifstream in ("input.txt");

    int len;
    in >> len;

    vector<pair<int,int>> vec;

    int num1, num2;
    for(int i=0; i<len; i++){
        in >> num1;
        in >> num2;
        vec.push_back(make_pair(num1,num2));
    }

    palle(vec);
}

void palle(vector<pair<int,int>> vec){
    ofstream out ("output.txt");

    sort(vec.begin(), vec.end());

    pair<int,int> res = make_pair(0,0);
    int nextstart = 0;
    int actend = 0;
    int maxrange = 0;
    
    for(int i=0; i<vec.size()-1; i++){
        actend = max(vec[i].second, actend);

        nextstart = vec[i+1].first;
        if(nextstart > actend && nextstart-actend+1 > maxrange){
            res.first = nextstart;
            res.second = actend;
            maxrange = nextstart-actend+1;
        }
    }

    if(res.first == 0 && res.second == 0){
        out<<0;
    }else{
        out<<res.second<<" "<<res.first;
    }
}