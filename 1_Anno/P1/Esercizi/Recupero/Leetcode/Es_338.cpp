#include <iostream>
using namespace std;

void up_to_num(int*, int);
int count_1(int);
void print(int*, int);

int main(){
    int num;

    cout<<"Inserisci un numero: ";
    cin>>num;

    int* res = new int[num];

    up_to_num(res, num);

    print(res, num);
    cout<<endl;

    return 0;
}

void up_to_num(int* l, int n){
    if(n >= 0){
        up_to_num(l, n-1);
        l[n] =  count_1(n);
    }
}

int count_1(int n){
    if(n == 0){
        return 0;
    }else if(n % 2){
        return 1 + count_1(n/2);
    }else{
        return count_1(n/2);
    }
}

void print(int* l, int len){
    if(len >= 0){
        print(l, len-1);
        cout<<l[len]<<" ";
    }
}