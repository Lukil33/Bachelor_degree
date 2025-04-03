#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void quickSort(vector<int>&, int, int);
int partition(vector<int>&, int, int);

int main(){
    ifstream in ("input.txt");
    ofstream out ("output.txt");

    int len;
    in >> len;

    vector<int> vec;
    vec.resize(len);

    for(int i=0; i<len; i++){
        int num;
        in >> num;
        vec[i] = num;
    }

    quickSort(vec,0,len-1);

    for(int i=0; i<len; i++){
        out << vec[i] << " " ;
    }
}

int partition(vector<int> &vec, int low, int high){

    int pivot = vec[high];

    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (vec[j] <= pivot) {
            i++;
            swap(vec[i], vec[j]);
        }
    }

    swap(vec[i + 1], vec[high]);

    return (i + 1);
}

void quickSort(vector<int> &vec, int low, int high){

    if (low < high) {

        int pi = partition(vec, low, high);

        quickSort(vec, low, pi - 1);
        quickSort(vec, pi + 1, high);
    }
}