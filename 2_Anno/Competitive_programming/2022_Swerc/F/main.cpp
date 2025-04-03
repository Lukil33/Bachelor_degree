#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int funct(vector<int>, vector<int>);

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    int rep;
    in>>rep;

    for(int i=0; i<rep; i++){
        int len, num;
        in>>len;
        vector<int> vec1;
        vector<int> vec2;

        for(int j=0; j<len; j++){
            in>>num;
            vec1.push_back(num);
        }
        for(int j=0; j<len; j++){
            in>>num;
            vec2.push_back(num);
        }

        out<<funct(vec1, vec2)<<endl;
    }
}

int funct(vector<int> a, vector<int> b){
    while(!a.empty()){
        if(b.back() != a.back()){
            a.pop_back();
        }else{
            b.pop_back();
            a.pop_back();
        }
    }
    return b.size();
}