int pow_iter(double base, double esponente);
int pow_rec(int base, int esponente);

int pow_iter(double base, double esponente){
    double ris=1;
    while(esponente>0){
        ris*=base;
        esponente--;
    }
    return ris;
}

int pow_rec(int base, int esponente){
    if(esponente>0){
        return base*pow_rec(base, esponente-1);
    }
    return 1;
}