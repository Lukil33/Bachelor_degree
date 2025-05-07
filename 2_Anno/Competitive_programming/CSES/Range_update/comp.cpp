#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#define rep(i,a,b) for(int i=a; i<b; i++)

int main(){
    ifstream output("output.txt");
    ifstream chk("check.txt");

    int a,b;
    bool controllo = true;
    while(output>>a){
        chk>>b;
        if(a != b){
            controllo = false;
        }
    }
    cout<<controllo<<endl;

    return 0;
}