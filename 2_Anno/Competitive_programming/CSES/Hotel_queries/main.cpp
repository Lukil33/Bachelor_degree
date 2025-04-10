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

node* create_tree(int min, int max){
    //cout<<"palle"<<endl;
    node* res = new node{0,0,nullptr,nullptr};
    int mid = min + (max-min)/2;     
    if(min == max){
        res->pos = min;
        if(min < (int)vec.size()){
            res->val = vec[min];
        }
    }else{
        res->left = create_tree(min, mid);
        res->right = create_tree(mid+1, max);
        res->val = res->left->val >= res->right->val ? res->left->val:res->right->val ;
    }
    return res;
}

int search_tree(node* nodo, int group){
    if(nodo->left == nullptr && nodo->right == nullptr){
        return nodo->pos;
    }else if(nodo->val < group){
        return -1;
    }else{
        if(nodo->left->val >= group){
            return search_tree(nodo->left, group);
        }else{
            return search_tree(nodo->right, group);
        }
    }
}

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    int N,M;
    in>>N>>M;

    vec.resize(N);

    int l = 1;
    while(l < N){
        l*=2;
    }

    rep(i,0,N){
        in>>vec[i];
    }

    node* tree = create_tree(0, l);

    rep(i,0,M){
        int a;
        in>>a;
        int modify = search_tree(tree, a);
        if(modify != -1){
            vec[modify] -= a;
            tree = create_tree(0, l);
        }
        out<<modify+1<<" ";
    }

    return 0;
}