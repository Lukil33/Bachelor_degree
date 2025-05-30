#include <iostream>
#include <cstdlib>
#include <cassert>

struct node {
		char info;
		node * next;
};

void dealloca(node *& s) {
		while(s != NULL) {
				node * t = s;
				s = s->next;
				delete t;
		}
}

void stampa_lista(const char * testo, node * s) {
		std::cout << testo;
		for( ; s!= NULL; s=s->next) {
				std::cout << " " << s->info;
		}
		std::cout << std::endl;
}

// Scrivere qui sotto la dichiarazione della funzione compute_lists ed
// eventuali funzioni accessorie
void compute_lists(char*, node*&, node*&);
void ausiliary(char*, node*&, node*&, int);
// Scrivere qui sopra la dichiarazione della funzione compute_lists ed
// eventuali funzioni accessorie

int main(int argc, char **argv) {
		if (argc != 2) {
				std::cout << "Usage: " << argv[0]
														<< " \"stringa di caratteri\"" << std::endl;
				exit(1);
		}
		node * s1, * s2;
		std::cout << "La stringa da analizzare e': " << argv[1] << std::endl;

		compute_lists(argv[1], s1, s2);

		stampa_lista("Lista s1:", s1);
		stampa_lista("Lista s2:", s2);
		dealloca(s1);
		dealloca(s2);
}

// Scrivere qui sotto la definizione della funzione compute_lists ed
// eventuali funzioni accessorie
void compute_lists(char* s, node*& l1, node*& l2){
    ausiliary(s, l1, l2, 0);
}

void ausiliary(char* s, node*& l1, node*& l2, int n){
    if(s[n] != '\0'){
        ausiliary(s, l1, l2, n+1);
        if(s[n] >= 'A' && s[n] <= 'M'){
            char c = -s[n] + 'A' + 'm';
            l1 = new node{c, l1};
        }else if(s[n] >= 'N' && s[n] <= 'Z'){
            char c = -s[n] + 'N' + 'z';
            l2 = new node{c, l2};
        }
    }
}
// Scrivere qui sopra la definizione della funzione compute_lists ed
// eventuali funzioni accessorie
