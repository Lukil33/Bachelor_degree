#include <iostream>
#include <fstream>
using namespace std;

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);
    int m,n;
    in>>m>>n;
    out<<m+n;
}