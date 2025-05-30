#include <iostream>
#include <iomanip>
#include <cstdlib>

void copy_array(char *src, char *dst, int n) {
    for (int i = 0; i < n; i++) {
        dst[i+1] = src[i];
    }
}

// Inserire qui la dichiarazione della funzione codici
char** codici(int, int&);
// Inserire qui sopra la dichiarazione della funzione codici_aux

// NON MODIFICARE IL MAIN
int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " #num" << std::endl;
        exit(1);
    }
    int nb = atoi(argv[1]);

    int max;
    char** res = codici(nb, max);

    std::cout << "Grey codes for " << nb << " bits:" << std::endl;
    for (int i = 0; i < max; i++) {
        std::cout << std::setw(3) << i << ": ";
        for (int j = 0; j < nb; j++) {
            std::cout << res[i][j];
        }
        delete [] res[i];
        std::cout << std::endl;
    }
    delete [] res;
    return 0;
}
// NON MODIFICARE IL MAIN

// Inserire qui sotto eventuali definizioni di funzioni ausiliarie
void creatematrix(char** mat, int max, int dim){
    if(max >= 0){
        mat[max] = new char[dim];
        creatematrix(mat, max-1, dim);
    }
}

void duplicate(char** mat, char** vecchia, int dim_larghezza, int dim_altezza, int counter){
    if(dim_altezza != counter){
        if(counter < dim_altezza/2){
            copy_array(vecchia[counter], mat[counter], dim_larghezza);
            duplicate(mat, vecchia, dim_larghezza, dim_altezza, counter+1);
        }else{
            copy_array(vecchia[dim_altezza-counter-1], mat[counter], dim_larghezza);
            duplicate(mat, vecchia, dim_larghezza, dim_altezza, counter+1);
        }
    }
}

void populatefirst(char** mat, int max, int counter){
    if(max != counter){
        if(max/2 <= counter){
            mat[counter][0] = '1';
        }else{
            mat[counter][0] = '0';
        }
        populatefirst(mat, max, counter+1);
    }
}

void remove(char** mat, int max){
    if(max >= 0){
        delete[] mat[max];
        remove(mat, max-1);
    }
}
// Inserire qui sopra eventuali definizioni di funzioni ausiliarie

// Inserire qui sotto la definizione della funzione codici
char** codici(int num, int& max){
    char** res = nullptr;
    if(num == 1){
        max = 2;
        res = new char*[max];
        creatematrix(res, max-1, num);
        populatefirst(res, max, 0);
    }else{
        char** temp = codici(num-1, max);
        max *= 2;
        res = new char*[max];
        creatematrix(res, max-1, num);
        duplicate(res, temp, num-1, max, 0);
        populatefirst(res, max, 0);
        
        remove(temp, (max/2)-1);
        delete[] temp;
    }
    return res;
}
// Inserire qui sopra la definizione della funzione codici