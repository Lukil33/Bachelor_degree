#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

double sottocres_ric(vector<int> vec, vector<int>& value, int elem);

int main(){
    vector<int> vec = {20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    vector<int> value = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

    cout<< sottocres_ric(vec, value, vec.size()-1)<<endl;

    return 0;
}

int findBigger(vector<int> vec, vector<int>& value, int elem, int count, int max_res){
    if(count >= (int)vec.size()){
        return max_res;
    }else if(vec[elem] < vec[count] && max_res < value[count]){
        max_res = value[count];
    }
    cout<<elem<<" - "<<count<<endl;
    return findBigger(vec,value,elem,count+1,max_res);
}

double sottocres_ric(vector<int> vec, vector<int>& value, int elem){
    if(elem < 0){
        
        /*cout<<"Val: ";
        for(int i=0; i<(int)value.size(); i++){
            cout<<value[i]<<" ";
        }
        cout<<endl;*/

        return *max_element(value.begin(), value.end());
    }else{
        value[elem] = vec[elem] + findBigger(vec,value,elem,elem+1,0);

        /*cout<<"Value element "<<elem<<": ";
        for(int i=0; i<(int)value.size(); i++){
            cout<<value[i]<<" ";
        }
        cout<<endl;*/

        return sottocres_ric(vec,value,elem-1);
    }
}