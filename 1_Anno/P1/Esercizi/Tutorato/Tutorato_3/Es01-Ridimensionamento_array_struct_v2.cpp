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

void insert_in_bucket(dataStruct * orig, int newItem);
int remove_from_bucket(dataStruct * orig, int index);

void print_array(dataStruct * orig);
void destroy_Array(dataStruct * orig);

int main(){
    srand(time(NULL));
    int size;

    cout<<"Inserire la dimensione limite dell' array: ";
    cin>>size;

    dataStruct * orig=generate_Array(size);
    cout<<"L'array creato ha "<<orig->numData<<" celle occupate su "<<orig->size<<endl;
    print_array(orig);

    resizeArray(orig, size);
    cout<<"L'array creato ha "<<orig->numData<<" celle occupate su "<<orig->size<<endl;
    print_array(orig);

    int newItem;
    cout<<"Inserire il nuovo elemento: ";
    cin>>newItem;
    insert_in_bucket(orig, newItem);
    print_array(orig);

    int index;
    cout<<"Inserire la posizione dell'elemento da eliminare: ";
    cin>>index;
    cout<<"Il valore eliminato e': "<<remove_from_bucket(orig, index)<<endl;
    print_array(orig);

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


void insert_in_bucket(dataStruct * orig, int newItem){
    orig->numData++;
    if(orig->size<orig->numData){
        int array[orig->size];
        for(int j=0; j<(orig->size); j++){
            array[j]=orig->data[j];
        }
        delete[] orig->data;

        orig->data=new int [(orig->size+1)];
        for(int g=0; g<(orig->size); g++){
            orig->data[g]=array[g];
        }
        orig->size++;
    }
    orig->data[(orig->numData)-1]=newItem;
}

int remove_from_bucket(dataStruct * orig, int index){
    while(index<=0||index>orig->numData){
        cout<<"Valore inserito errato"<<endl;
        cout<<"Reinserire la posizione dell'elemento da eliminare: ";
        cin>>index;
    }

    index--;
    int removed_data=orig->data[index];
    orig->data[index]=orig->data[(orig->numData)-1];
    orig->data[(orig->numData)-1]=0;
    orig->numData--;
    return removed_data;
}


void print_array(dataStruct * orig){
    for(int i=0; i<(orig->size); i++){
        cout<<orig->data[i]<<" ";
    }
    cout<<endl;
}

void destroy_Array(dataStruct * orig){
    delete[] orig->data;
    delete[] orig;
}