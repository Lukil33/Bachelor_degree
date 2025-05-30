#include <iostream>
using namespace std;

/* Inserire qui sotto la dichiarazione della funzione extract */
char * extract(char * input_string);
char * ausiliary(char * input_string, char * string, int counter, int dim_array);
char * new_string(char * string, int dim_array);
/* Inserire qui sopra la dichiarazione della funzione extract */

/* Solo di esempio, non fate assunzioni su questo valore */
const int DIM = 255;

int main(int argc, char ** argv) {
  char input_string[DIM+1];
  char * extracted;
  char answer;

  do {
    std::cout << "Inserire la stringa da controllare: ";
    std::cin >> input_string;

    extracted = extract(input_string);
    std::cout << "La stringa estratta e': " << extracted << std::endl;

    delete [] extracted;
    std::cout << "Si vuole inserire un'altra stringa? [*/n]";
    std::cin >> answer;
  } while (answer != '\0' && answer != 'N' && answer != 'n');
  return 0;
}

/* Inserire qui sotto la definizione della funzione estract */
char * new_string(char * string, int dim_array){
    if(dim_array<=0){
        return string;
    }else{
        string[dim_array-1]='@';
        return new_string(string, dim_array-1);
    }
}

char * ausiliary(char * input_string, char * string, int counter, int dim_array){
    if(input_string[counter]=='\0'){
        return string;
    }else{
        if(input_string[counter]=='@'){
            dim_array++;
            delete[] string;
            char * pointer=new char[dim_array];
            pointer = new_string(pointer, dim_array);
            pointer[dim_array-1]='\0';
            return ausiliary(input_string, pointer, counter+1, dim_array);
        }else{
            return ausiliary(input_string, string, counter+1, dim_array);
        }
    }
}

char * extract(char * input_string){
    char * string = new char {'\0'};
    int counter=0, dim_array=1;
    string = ausiliary(input_string, string, counter, dim_array);
    return string;
}
/* Inserire qui sopra la definizione della funzione estract */