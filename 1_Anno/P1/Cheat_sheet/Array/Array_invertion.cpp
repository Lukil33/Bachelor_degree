void invertion(int array[], int dim_array);

void invertion(int array[], int dim_array){
    for(int i=0; i<dim_array/2; i++){
        int temp=array[i];
        array[i]=array[dim_array-1-i];
        array[dim_array-1-i]=temp;
    }
}


void recursive_invertion(int array[], int dim_array, int counter=0);

void recursive_invertion(int array[], int dim_array, int counter){
    if(counter<=dim_array/2){
        int temp=array[counter];
        array[counter]=array[dim_array-1-counter];
        array[dim_array-1-counter]=temp;
        recursive_invertion(array, dim_array, counter+1);
    }
}
