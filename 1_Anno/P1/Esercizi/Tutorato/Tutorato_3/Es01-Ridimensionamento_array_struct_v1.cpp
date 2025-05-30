#include <iostream>
#include <cstdlib>
using namespace std;

struct dataStruct{
    int *data;
    int size, numData;
};

dataStruct * generate_Array(int size);
int rand_num(int size);
void resizeArray(dataStruct * orig, int size);
void destroy_Array(dataStruct * orig);

int main(){
    srand(time(NULL));
    int size;

    cout<<"Inserire la dimensione limite dell' array: ";
    cin>>size;

    dataStruct * orig=generate_Array(size);
    cout<<"L'array creato ha "<<orig->numData<<" celle occupate su "<<orig->size<<endl;

    resizeArray(orig, size);
    cout<<"L'array creato ha "<<orig->numData<<" celle occupate su "<<orig->size<<endl;

    destroy_Array(orig);
    return 0;
}

dataStruct * generate_Array(int size){
    dataStruct * orig = new dataStruct;

    orig->size=size;
    orig->numData=rand_num(size);
    orig->data=new int [size];
    for(int i=0; i<(orig->numData); i++){
        orig->data[i]=i;
    }
    return orig;
}

int rand_num(int size){
    int number=rand()%size;
    return number;
}

void resizeArray(dataStruct * orig, int size){
    int array[orig->size];
    for(int j=0; j<(orig->size); j++){
        array[j]=orig->data[j];
    }
    delete[] orig->data;

    cout<<"Inserisci nuovamente la dimensione limite dell' array: ";
    cin>>size;

    orig->data=new int [size];
    for(int g=0; g<(orig->size); g++){
        if(size>g){
            orig->data[g]=array[g];
        }
    }
    orig->size=size;
    if((orig->size)<(orig->numData)){
        orig->numData=orig->size;
    }
}

void destroy_Array(dataStruct * orig){
    delete[] orig->data;
    delete[] orig;
}