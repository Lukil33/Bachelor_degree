#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a; i<b; i++)

struct node{
    int val;
    int pos;
    node* left;
    node* right;
};

vector<int> vec;
set<int> pay;
map<int,vector<int>> nodeToPay;

node* create_tree(int min, int max){
    node* res = new node{0,0,nullptr,nullptr};
    int mid = min + (max-min)/2;
    if(min == max){
        res->pos = min;
        if(min < (int)vec.size()){
            res->val = 1;
        }
    }else{
        res->left = create_tree(min, mid);
        res->right = create_tree(mid+1, max);
        res->val = res->left->val + res->right->val;
    }
    return res;
}

int search_tree(node* nodo, int group){
    int res;
    if(nodo->left == nullptr && nodo->right == nullptr){
        res = vec[nodo->pos];
	    nodo->val -= 1;
    }else if(nodo->val < group){
        res = -1;
    }else{
        if(nodo->left->val >= group){
            res = search_tree(nodo->left, group);
            nodo->val -= 1;
	    }else{
            res = search_tree(nodo->right, group-nodo->left->val);
	        nodo->val -= 1;
        }
    }
    return res;
}

int main(){
    ifstream cin("input.txt");

    int numNodi, numQueries;
    cin>>numNodi>>numQueries;

    vec.resize(numNodi);

    rep(i,0,numNodi){
        cin>>vec[i];
        pay.insert(vec[i]);
        nodeToPay[vec[i]].push_back(i);
    }

    

    rep(i,0,numQueries){
        int a;
        cin>>a;
    }
    cout<<endl;

    return 0;
}