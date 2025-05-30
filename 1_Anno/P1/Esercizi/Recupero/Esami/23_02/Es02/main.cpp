#include <iostream>
#include <cstdlib>
#include <ctime>

#define MAXVALUE 100
#define MAXSIZE 100

// NON MODIFICARE IL CODICE SOTTO FINO A "NON MODIFICARE IL CODICE SOPRA"
struct list {
  int info;
  list * next;
};

struct tree {
  int info;
  tree * left;
  tree * right;
};

void insert(tree * & result, const int num) {
		if (result == NULL) {
				result = new tree;
				*result = {num, NULL, NULL};
		} else if (result->info > num) {
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

void print_tree(const tree * root){
		if (root != NULL) {
				print_tree(root->right);
				std::cout << " " << root->info;
				print_tree(root->left);
  }
}

void delete_tree(tree * & root) {
  if (root != NULL) {
    delete_tree(root->left);
    delete_tree(root->right);
    delete root;
    root = NULL;
  }
}

void print_array(const int l[], const int l_size) {
  for(int i = 0; i < l_size; i++)
    std::cout << " " << l[i];
  std::cout << std::endl;
}

// NON MODIFICARE IL CODICE SOPRA

// Add hereafter the declaration of estrai
void estrai(tree*, int*&, int&, int*&, int&);
void dimensioni(tree*, int&, int&);
void allocate(tree*, int*, int&, int*, int&);
// Add here above the declaration of estrai

// NON MODIFICARE IL MAIN
int main(int argc, char ** argv) {
  srand(unsigned(time(0)));
		//
		// Commentare la linea seguente per avere comportamento
		// non-deterministico
		//
		srand(0);
		tree * root = crea_tree(rand()%MAXSIZE);
		std::cout << "Initial tree content: ";
		print_tree(root); std::cout << std::endl;
  int * l1;
  int l1_size;
  int * l2;
  int l2_size;
  estrai(root, l1, l1_size, l2, l2_size);
  delete_tree(root);
		std::cout << "L1 =";
  print_array(l1, l1_size);
		std::cout << "L2 =";
  print_array(l2, l2_size);
  delete [] l1;
  delete [] l2;
}
// NON MODIFICARE IL MAIN

// Add hereafter the definition of estrai
void estrai(tree* t, int*& l1, int& dim_l1, int*& l2, int& dim_l2){
    dim_l1 = 0;
    dim_l2 = 0;
    dimensioni(t, dim_l1, dim_l2);

    l1 = new int[dim_l1];
    l2 = new int[dim_l2];
    int counter1=0, counter2=0;
    allocate(t,l1,counter1,l2,counter2);
}

void dimensioni(tree* t, int& dim_l1, int& dim_l2){
    if(t != nullptr){
        if(t->info%2){
            dim_l2+=1;
        }else{
            dim_l1+=1;
        }
        dimensioni(t->left, dim_l1, dim_l2);
        dimensioni(t->right, dim_l1, dim_l2);
    }
}

void allocate(tree* t, int* l1, int& counter_l1, int* l2, int& counter_l2){
    if(t != nullptr){
        allocate(t->left, l1, counter_l1, l2, counter_l2);

            if(t->info%2){
                l2[counter_l2] = t->info;
                counter_l2+=1;
            }else{
                l1[counter_l1] = t->info;
                counter_l1+=1;
            }

        allocate(t->right, l1, counter_l1, l2, counter_l2);
    }
}
// Add here above the definition of estrai
