#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

double sottocres(vector<int>, int);

int main(){
    ifstream in ("input.txt");
    ofstream out ("output.txt");

    int n;
    in >> n;

    vector<int> vec;

    for(int i=0; i<n; i++){
        int val;
        in >> val;
        vec.push_back(val);
    }

    out << sottocres(vec,n);

    return 0;
}

int findBigger(vector<int> vec, vector<int>& value, int elem, int count, int max_res){
    if(count >= (int)vec.size()){
        return max_res;
    }else if(vec[elem] < vec[count] && max_res < value[count]){
        max_res = value[count];
    }
    return findBigger(vec,value,elem,count+1,max_res);
}

double sottocres_ric(vector<int> vec, vector<int>& value, int elem){
    if(elem < 0){
        return *max_element(value.begin(), value.end());
    }else{
        value[elem] = vec[elem] + findBigger(vec,value,elem,elem+1,0);
        return sottocres_ric(vec,value,elem-1);
    }
}

double sottocres(vector<int> vec, int num){
    vector<int> value;
    value.resize(num);

    return sottocres_ric(vec,value,num-1);
}