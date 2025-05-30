#include <iostream>
#include <cstdlib>
#include <ctime>

#define MAXVALUE 100
#define MAXSIZE 100

typedef struct tree {
		int value;
		struct tree * left;
		struct tree * right;
} tree;

void insert(tree * & result, const int num) {
		if (result == NULL) {
				result = new tree {num, NULL, NULL};
		} else if (result->value > num) {
				insert(result->left, num);
		} else {
				insert(result->right, num);
		}
}

tree * crea_tree(const int num) {
		tree * result = NULL;
		for(int i = 0; i < num; i++) {
				insert(result, rand()%MAXVALUE);
		}
		return result;
}

// void print_tree(tree * root, int spazio = 0);

void print_tree(tree * root, int spazio = 0){
		if (root != NULL) {
				spazio++;
				print_tree(root->right, spazio);

				for (int i = 1; i < spazio; i++) std::cout<<"  ";
				std::cout<<root->value<<"\n";
				print_tree(root->left, spazio);
		}
}

// Inserire qui sotto definizione e dichiarazione di insert_iter
void insert_iter(tree*& r, int n){
    if(r == nullptr){
        r = new tree{n, nullptr, nullptr};
    }else{
        if(r->value > n){
            if(r->right != nullptr){
                insert_iter(r->right, n);
            }else{
                r->right = new tree{n, nullptr, nullptr};
            }
        }else{
            if(r->left != nullptr){
                insert_iter(r->left, n);
            }else{
                r->left = new tree{n, nullptr, nullptr};
            }
        }
    }
}
// Inserire qui sopra definizione e dichiarazione di insert_iter

int main() {
		srand(unsigned(time(0)));
		//
		// Scommentare la linea seguente per avere comportamento
		// deterministico
		//
		srand(0);
		tree * root = crea_tree(rand()%MAXSIZE);

		std::cout << "Initial tree: " << std::endl;
		print_tree(root);
		std::cout << std::endl;
		std::cout << "Inserting -1" << std::endl;
		insert_iter(root, -1);
		std::cout << "Inserting "<< MAXSIZE << std::endl;
		insert_iter(root, MAXSIZE);
		std::cout << "Inserting "<< MAXSIZE/2 << std::endl;
		insert_iter(root, MAXSIZE/2);
		std::cout << "Final tree: " << std::endl;
		print_tree(root);
		std::cout << std::endl;
		return 0;
}
