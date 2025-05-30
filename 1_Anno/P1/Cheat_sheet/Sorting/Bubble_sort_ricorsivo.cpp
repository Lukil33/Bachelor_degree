void bubblesort_ricorsivo(int array[], int dim, bool ordinato);
int* bubblesort_ricorsivo_ciclo(int* array, int dim ,int& x, int j);

void bubblesort_ricorsivo(int array[], int dim, bool ordinato){
    if(!ordinato&&dim>0){
        int x=0;
        array=bubblesort_ricorsivo_ciclo(array, dim, x, 0);
        if(x == 0){
            ordinato=true;
        }
        else bubblesort_ricorsivo(array, dim-1, ordinato);
    }
}

int* bubblesort_ricorsivo_ciclo(int* array, int dim ,int& x, int j){
    if(j<dim-1){
        if(array[j]>array[j+1]){
            int t=array[j];
            array[j]=array[j+1];
            array[j+1]=t;
            x++;
        }
        return bubblesort_ricorsivo_ciclo(array, dim, x,j+1);
    }
    return array;
}