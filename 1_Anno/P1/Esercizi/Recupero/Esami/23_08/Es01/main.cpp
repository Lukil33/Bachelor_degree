#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

int main(int argc, char* argv[]){
    if(argc != 2){
        cerr<<"Error: ./a.out <input_fle>"<<endl;
        return -1;
    }

    fstream input;
    input.open(argv[1], ios::in);
    if(input.fail()){
        cerr<<"Error during file opening"<<endl;
        return -2;
    }

    char key[256];
    cout<<"Si inserisca una sequenza di caratteri da ricercare: ";
    cin>>noskipws>>key;

    char carattere[256];
    while(input>>carattere){
        for(int j=0; j<int(strlen(carattere)); j++){
        
            for(int i=0; i<int(strlen(key)); i++){
                if(key[i] >= 'a' && key[i] <= 'z'){
                    if(key[i] == carattere[j] || key[i]-'a'+'A' == carattere[j]){
                        cout<<carattere[j];
                    }
                }else if(key[i] >= 'A' && key[i] <= 'Z'){
                    if(key[i] == carattere[j] || key[i]-'A'+'a' == carattere[j]){
                        cout<<carattere[j];
                    }
                }else{
                    if(key[i] == carattere[j]){
                        cout<<carattere[j];
                    }
                }
            }
        
        }
        cout<<" ";
    }
    cout<<endl;

    input.close();
    return 0;
}