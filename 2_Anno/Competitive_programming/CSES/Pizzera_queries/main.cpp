#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#define ll long long
#define rep(i,a,b) for(long long i=a; i<b; i++)

struct node{
    ll val;
    ll pos;
    node* left;
    node* right;
};

int numNodi;
vector<ll> vecL,vecR;

node* create_tree(vector<ll> vec, ll min, ll max){
    node* res = new node{-1,0,nullptr,nullptr};
    ll mid = min + (max-min)/2;
    if(min == max){
        res->pos = min;
        if(min < (ll)vec.size()){
            res->val = vec[min] + min;
        }
    }else{
        res->left = create_tree(vec, min, mid);
        res->right = create_tree(vec, mid+1, max);
        res->pos = res->left->pos;
        if((res->left->val > res->right->val) && (res->right->val > 0)){
            res->val = res->right->val;
        }else{
            res->val = res->left->val;
        }
    }
    return res;
}

void modify_tree(node* tree, ll pos, ll val){
    if(tree->left == nullptr && tree->right == nullptr){
        tree->val = val+tree->pos;
    }else{
        if(tree->right->pos <= pos){
            modify_tree(tree->right, pos, val);
        }else{
            modify_tree(tree->left, pos, val);
        }
        if((tree->left->val > tree->right->val) && (tree->right->val > 0)){
            tree->val = tree->right->val;
        }else{
            tree->val = tree->left->val;
        }
    }
}

ll search_tree(node* tree, ll pos){
    if(tree->pos >= pos){
        return tree->val;
    }else{
        if(tree->right->pos >= numNodi){
            return search_tree(tree->left, pos);
        }else if(tree->right->pos <= pos){
            return search_tree(tree->right, pos);
        }else{
            return min(search_tree(tree->left, pos), search_tree(tree->right, pos));
        }
    }
}

int main(){
    ifstream cin("input.txt");

    int numQueries;
    cin>>numNodi>>numQueries;

    vecL.resize(numNodi);
    vecR.resize(numNodi);

    ll l = 1;
    while(l < numNodi){
        l*=2;
    }

    rep(i,0,numNodi){
        int a;
        cin>>a;
        vecR[i] = a;
        vecL[numNodi-1-i] = a;
    }

    node* treeToRight = create_tree(vecR, 0, l);
    cout<<"Palle"<<endl;
    node* treeToLeft = create_tree(vecL, 0, l);

    cout<<"Palle"<<endl;

    rep(i,0,numQueries){
        int a,b;
        cin>>a>>b;
        b = b-1;
        if(a == 1){
            int c;
            cin>>c;
            modify_tree(treeToRight, b, c);
            modify_tree(treeToLeft, numNodi-1-b, c);
        }else{
            cout<<min(search_tree(treeToRight, b)-b, search_tree(treeToLeft, numNodi-1-b)-(numNodi-1-b))<<endl;
        }
    }

    return 0;
}