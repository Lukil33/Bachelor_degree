#include <iostream>
#include <cstdlib>
using namespace std;

int * generate_numbers(int N);

int main(int argc, char *argv[]){
    srand(time(NULL));

    if(argc!=2){
        cerr<<"A fantastico sarebbe meglio inserire cio che ti chiedo"<<endl;
        return -1;
    }

    int N = atoi(argv[1]);

    int * array = generate_numbers(N);

    if(array==NULL){
        return -2;
    }else{
        for(int i=0; i<N; i++){
            cout<<array[i]<<" ";
        }
    }
    cout<<endl;

    delete[] array;

    return 0;
}

int * generate_numbers(int N){
    int *array= new (nothrow) int [N];
    if(array!=NULL){
        for(int i=0; i<N; i++){
            array[i]=rand()%100;
        }
    }
    return array;
}