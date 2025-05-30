int strlen_iter(char *);

int strlen_iter(char * array){
    int i=0;
    while(array[i] != '\0'){
        i++;
    }
    return i;
}


int strlen_rec(char *);
int strlen_aus(char *, int);

int strlen_rec(char * array){
    return strlen_aus(array, 0);
}

int strlen_aus(char *array, int cont){
    if(array[cont] != '\0'){
        return strlen_aus(array, cont+1);
    }
    return cont;
}