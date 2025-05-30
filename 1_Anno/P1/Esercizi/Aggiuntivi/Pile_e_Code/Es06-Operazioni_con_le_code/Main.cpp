#include <iostream>
#include <fstream>
using namespace std;

struct number{
    int num;
    number* next;
};
struct sign{
    char letter;
    sign* next;
};

void create_code(number*& n_code, sign*& s_code, char* argv);
void add_number(number*& code, int N);
void add_sign(sign*& code, char character);
int solution(number*& n_code, sign*& s_code);
int summ(number*& n_code);
void moltiplication(number*& n_code);

int main(int argc, char* argv[]){
    if(argc != 2){
        cerr<<"Error: ./a.out <input_file>"<<endl;
        return -1;
    }
    number* n_code;
    sign* s_code;
    create_code(n_code, s_code, argv[1]);
    cout<<"Result-> "<<solution(n_code, s_code)<<endl;
    delete[] n_code;
    delete[] s_code;
    return 0;
}

void create_code(number*& n_code, sign*& s_code, char* argv){
    fstream input;
    input.open(argv, ios::in);

    char character[255];
    int i=0;
    while(input>>character){
        if(i%2 == 0){
            int number=atoi(character);
            add_number(n_code, number);
        }else{
            add_sign(s_code, character[0]);
        }
        i++;
    }
    input.close();
}
void add_number(number*& code, int N){
    number* created=new number{N, nullptr};
    if(code == nullptr){
        code=created;
    }else{
        number* pointer=code;
        while(pointer->next != nullptr){
            pointer=pointer->next;
        }
        pointer->next=created;
    }
}
void add_sign(sign*& code, char character){
    sign* created=new sign{character, nullptr};
    if(code == nullptr){
        code=created;
    }else{
        sign* pointer=code;
        while(pointer->next != nullptr){
            pointer=pointer->next;
        }
        pointer->next=created;
    }
}

int solution(number*& n_code, sign*& s_code){
    int solution = 0;
    while(n_code != nullptr){
        if(s_code == nullptr){
            solution+=summ(n_code);
        }else if(s_code->letter == '+'){
            solution+=summ(n_code);
            sign* pointer=s_code;
            s_code=s_code->next;
            delete[] pointer;
        }else if(s_code->letter == '*'){
            moltiplication(n_code);
            sign* pointer=s_code;
            s_code=s_code->next;
            delete[] pointer;
        }else{
            cerr<<"Sign error"<<endl;
            return -1;
        }
    }
    return solution;
}

int summ(number*& n_code){
    number* pointer=n_code;
    n_code=n_code->next;
    int number=pointer->num;
    delete[] pointer;
    return number;
}

void moltiplication(number*& code){
    code->num*=code->next->num;
    number* pointer=code->next;
    code->next=code->next->next;
    delete[] pointer;
}