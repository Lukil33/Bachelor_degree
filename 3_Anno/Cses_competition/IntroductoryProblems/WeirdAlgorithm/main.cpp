#include <iostream>
using namespace std;
#define rep(i,a,b) for(int i=a; i<b; i++)

int main(){
    long long n;
    cin>>n;
    while(n > 1){
        cout<<n<<" ";
        if(n%2){
            n*=3;
            n+=1;
        }else{
            n/=2;
        }
    }
    cout<<n;
}