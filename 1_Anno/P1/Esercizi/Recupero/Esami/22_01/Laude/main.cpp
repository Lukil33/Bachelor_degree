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
				result = new tree;
				*result = {num, NULL, NULL};
				// result->value = num;
				// result->left=result->right= NULL;
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

// Inserire qui sotto definizione e dichiarazione di maxmin_value
int maxmin_value(tree* r, bool c){
    if(c){
        while(r->right != nullptr){
            r = r->right;
        }
        return r->value;
    }else{
        while(r->left != nullptr){
            r = r->left;
        }
        return r->value;
    }
}
// Inserire qui sopra definizione e dichiarazione di maxmin_value

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
		std::cout << "Il max e': " << maxmin_value(root, true) << std::endl;
		std::cout << "Il min e': " << maxmin_value(root, false) << std::endl;
		return 0;
}
