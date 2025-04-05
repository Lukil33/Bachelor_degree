#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

void insert_in_order(vector<pair<int,int>>& DP, pair<int,int> elem);

int main(){
    vector<pair<int,int>> DP = {{9,14},{5,10},{3,4},{1,1}};
    pair<int,int> elem = {7,11};

    insert_in_order(DP, elem);

    cout<<"Vec: ";
    for(pair<int,int> p: DP){
        cout<<" - "<<p.first<<"."<<p.second;
    }
    cout<<endl;

    return 0;
}

void insert_in_order(vector<pair<int,int>>& DP, pair<int,int> elem){
    if(DP.empty()){
        //Se DP è vuoto semplicemente inserire elem
        DP.push_back(elem);
    }else{
        //Se DP ha degli elementi inserisco elem in modo ordinato
        int low = 0, high = DP.size()-1;

        while(low <= high){
            int mid = low + (high - low) / 2;

            if (DP[mid].second >= elem.second){
                low = mid + 1;
            }else{
                high = mid - 1;
            }
        }
    
        if(DP[low].second < elem.second){
            DP.insert(DP.begin()+low, elem);
        }else{
            DP.insert(DP.begin()+low+1, elem);
        }
    }
}