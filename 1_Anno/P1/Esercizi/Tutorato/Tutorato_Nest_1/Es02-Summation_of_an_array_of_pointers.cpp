#include<iostream>
#include<cstdlib>
using namespace std;

const int DIM = 6;

float sum(float* p[], int n, bool* errorFlag);

int main(){
    float a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;
    float* p[DIM];
    bool errorFlag = false;
    p[0] = &a;
    p[1] = &b;
    p[2] = &c;
    p[3] = &d;
    p[4] = &e;
    p[5] = &f;
    int n = 0;
    cout << "Inserisci il numero di elementi da sommare: " << endl;
    cin >> n;
    float result = sum(p, n, &errorFlag);
    if(!errorFlag){
        cout << "result = " << result << endl;
    } else{
        cout << "Errore: out of bound" << endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

float sum(float* p[], int n, bool* errorFlag){
    float somma=0;
    
    for(int i=n-1;i>=0;i--){
        somma+=(*p[i]);
    }
    return somma;
}