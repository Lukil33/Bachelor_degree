#include<iostream>
#include<cstdlib>
#include<fstream>
using namespace std;

// La funzione non va modificata, pena l'annullamento dell'esercizio
void sort_array(int * array, int len_array) {
  for (int i=0; i<len_array; i++) {
    for (int j=i+1; j<len_array; j++) {
      if (array[i] > array[j]) {
        int tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
      }
    }
  }
}

int main(int argc, char * argv []) {
    if(argc != 4){
        cerr<<"Error: ./a.out <input_file> <DIM> <N>"<<endl;
        return -1;
    }

    fstream input, output;
    input.open(argv[1], ios::in);
    if(input.fail()){
        cerr<<"Error during file opening"<<endl;
        return -2;
    }
    output.open("output.txt", ios::out);
    if(output.fail()){
        cerr<<"Error during file opening"<<endl;
        input.close();
        return -2;
    }

    int dim = atoi(argv[2]), num = atoi(argv[3]);
    int* array = new int[dim];

    for(int i=0; i<dim; i++){
        input>>array[i];
    }

    sort_array(array, dim);

    for(int i=0,j=dim-1; i<num; i++,j--){
        output<<array[j]<<endl;
    }

    delete[] array;
    input.close();
    output.close();
    return 0;
}
