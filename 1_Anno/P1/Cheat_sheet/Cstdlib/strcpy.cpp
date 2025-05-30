void strcpy_iter(char *, char *);

void strcpy_iter(char * pieno, char * vuoto){
    int i=0;
    for(; pieno[i] != '\0'; i++){
        vuoto[i]=pieno[i];
    }
    vuoto[i]='\0';
}


void strcpy_rec(char *, char *);
void strcpy_aus(char *, char *, int);

void strcpy_rec(char * pieno, char * vuoto){
    int cont=0;
    strcpy_aus(pieno, vuoto, cont);
}

void strcpy_aus(char * pieno, char * vuoto, int cont){
    if(pieno[cont] != '\0'){
        vuoto[cont]=pieno[cont];
        strcpy_aus(pieno, vuoto, cont+1);
    }
}
