#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#define ll long long
#define rep(i,a,b) for(int i=a; i<b; i++)

struct node{
    ll val;
    int pos;
    node* left;
    node* right;
};

vector<ll> vec;

node* create_tree(int min, int max){
    node* res = new node{0,0,nullptr,nullptr};
    int mid = min + (max-min)/2;
    if(min == max){
        res->pos = min;
        if(min == 0){
            res->val = vec[min];
        }else if(min < (int)vec.size()){
            res->val = vec[min]-vec[min-1];
        }
    }else{
        res->left = create_tree(min, mid);
        res->right = create_tree(mid+1, max);
        res->pos = res->left->pos;
        res->val = res->left->val + res->right->val;
    }
    return res;
}

ll search_tree(node* nodo, int num){
    ll res;
    if(nodo->left == nullptr && nodo->right == nullptr){
        res = nodo->val;
    }else if(num < nodo->right->pos){
        res = search_tree(nodo->left, num);
    }else{
        res = nodo->left->val + search_tree(nodo->right, num);
    }
    return res;
}

ll modify_tree(node* nodo, int num, int var){
    if(nodo->left == nullptr && nodo->right == nullptr){
        nodo->val += var;
    }else if(num < nodo->right->pos){
        nodo->val = nodo->right->val + modify_tree(nodo->left, num, var);
    }else{
        nodo->val = nodo->left->val + modify_tree(nodo->right, num, var);
    }
    return nodo->val;
}

int main(){
    ifstream cin("input.txt");
    ofstream cout("output.txt");

    int N, M;
    cin>>N>>M;

    vec.resize(N);

    int l = 1;
    while(l < N){
        l*=2;
    }

    rep(i,0,N){
        cin>>vec[i];
    }

    node* tree = create_tree(0, l);

    rep(i,0,M){
        ll a,b;
        cin>>a>>b;
        if(a == 2){
            cout<<search_tree(tree, b-1)<<endl;
        }else{
            ll c,d;
            cin>>c>>d;
            modify_tree(tree, b-1, d);
            if(c < N){
                modify_tree(tree, c, -d);
            }
        }
    }

    return 0;
}