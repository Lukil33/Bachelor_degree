#include <iostream>
#include <cstdlib>
using namespace std;

int ** generate_matrix(int R, int C);

int main(int argc, char *argv[]){
    srand(time(NULL));

    if(argc!=3){
        cerr<<"A fantastico sarebbe meglio inserire cio che ti chiedo"<<endl;
        return -1;
    }

    int R = atoi(argv[1]);
    int C = atoi(argv[2]);

    int ** array = generate_matrix(R, C);

    if(array==NULL){
        return -2;
    }else{
        for(int i=0; i<R; i++){
            for(int j=0; j<C; j++){
                cout<<array[i][j]<<" ";
            }
            cout<<endl;
        }
    }

    for(int g=0; g<C; g++){
        delete[] array[R];
    }
    delete[] array;

    return 0;
}

int ** generate_matrix(int R, int C){
    int ** array = new (nothrow) int *[R];
    for(int g=0; g<R; g++){
        array[g]= new (nothrow) int [C];
    }

    if(array!=NULL){
        for(int i=0; i<R; i++){
            for(int j=0; j<C; j++){
                array[i][j]=rand()%100;
            }
        }
    }
    return array;
}