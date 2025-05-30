void bubble_sort(int* a, int dim_array);

void bubble_sort(int* a, int dim){
    int k=0;
    do{
        k=0;
        for(int i=0; i<dim-1; i++){
            if(a[i]>a[i+1]){
                int temp=a[i];
                a[i]=a[i+1];
                a[i+1]=temp;
                k=1;
            }
        }
    }while(k==1);
}