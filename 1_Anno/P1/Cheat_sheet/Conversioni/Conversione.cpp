int binary_conversion(long);
long decimal_conversion(int);

long pow(int, int);

int binary_conversion(long binario){
    int number=0, esponente=0;
    while(binario != 0){
        int ausiliario=(binario%2);

        binario-=ausiliario;
        binario/=10;

        number+=ausiliario*pow(esponente, 2);
        esponente++;
    }
    return number;
}

long decimal_conversion(int decimale){
    long number=0;
    while(decimale > 0){
        int esponente=0;
        while((decimale-pow(esponente+1, 2))>0){
            esponente++;
        }
        decimale-=pow(esponente, 2);
        number+=1*pow(esponente, 10);
    }
    return number;
}


int pow(int esponente, int base){
    int risultato=1;
    while(esponente>0){
        risultato*=base;
        esponente--;
    }
    return risultato;
}