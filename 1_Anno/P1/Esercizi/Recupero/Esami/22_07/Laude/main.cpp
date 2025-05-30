#include <iostream>
#include <cstdlib>
#include <ctime>

#define MAXVALUE 100
#define MAXSIZE 100

typedef struct tree {
  int data;
  struct tree * left;
  struct tree * right;
} tree;

void insert(tree * & result, const int num) {
		if (result == NULL) {
				result = new tree;
				*result = {num, NULL, NULL};
		} else if (result->data > num) {
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

void print_tree(tree * root, int spazio = 0){
		if (root != NULL) {
				spazio++;
				print_tree(root->right, spazio);

				for (int i = 1; i < spazio; i++) std::cout<<"  ";
				std::cout<<root->data<<"\n";
				print_tree(root->left, spazio);
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

typedef struct _list {
  const tree * node;
  struct _list * next;
} list;

typedef struct _queue {
  int size;
  list * head;
  list * tail;
} queue;

queue * init() {
  return new queue{0, NULL, NULL};
}


void enqueue(queue * & q, const tree * t) {
  list * n = new list{t, NULL};
  q->size += 1;
  if (q->head == NULL) {
    q->head = n;
  } else {
    if (NULL != q->tail) q->tail->next = n;
  }
  q->tail = n;
}

const tree * first(queue * & q) {
  if (q->head == NULL) return NULL;
  else return q->head->node;
}

int size(queue * & q) {
  return q->size;
}

void dequeue(queue * & q) {
  if (q->head != NULL) {
    q->size += -1;
    list * first = q->head;
    q->head = q->head->next;
    delete first;
  }
}

bool empty(queue * & q) {
  return q->head == NULL;
}

void deinit(queue * & Q) {
  while(!empty(Q)) {
    dequeue(Q);
  }
  delete Q;
  Q = NULL;
}

int altezza_ric(const tree * root);

int altezza_ric(const tree * root) {
  if (NULL == root) return 0;
  else return 1 + std::max(altezza_ric(root->left),
                           altezza_ric(root->right));
}

// Add hereafter the declaration of altezza_iter
int altezza_iter(tree*);
// Add here above the declaration of altezza_iter

int main() {
		srand(unsigned(time(0)));
		//
		// Commentare la linea seguente per avere comportamento
		// non-deterministico
		//
		srand(0);
		tree * root = crea_tree(rand()%MAXSIZE);

		std::cout << "Initial tree: " << std::endl;
		print_tree(root);
		std::cout << std::endl;
  std::cout << "Altezza ricorsiva = " << altezza_ric(root) << std::endl;
  std::cout << "Altezza iterativa = " << altezza_iter(root) << std::endl;
  delete_tree(root);
		return 0;
}


// Add hereafter the definition of altezza_iter
int altezza_iter(tree* r){
    int res = 0;
    if(r != nullptr){
        queue* coda = init();
        enqueue(coda, r);
        const tree* pointer = r;
        while(!empty(coda)){
            if(first(coda) == pointer){
                if(first(coda)->right != nullptr || first(coda)->left != nullptr){
                    res+=1;
                    if(first(coda)->left != nullptr){
                        pointer = first(coda)->left;
                    }else{
                        pointer = first(coda)->right;
                    }
                    if(first(coda)->right != nullptr){
                        enqueue(coda, first(coda)->right);
                    }
                    if(first(coda)->left != nullptr){
                        enqueue(coda, first(coda)->left);
                    }
                    dequeue(coda);
                }else{
                    dequeue(coda);
                    if(size(coda) != 0){
                        pointer = first(coda);
                    }else{
                        res+=1;
                    }                  
                }
            }else{
                if(first(coda)->left != nullptr){
                    enqueue(coda, first(coda)->left);
                }
                if(first(coda)->right != nullptr){
                    enqueue(coda, first(coda)->right);
                }
                dequeue(coda);
            }
        }
        deinit(coda);
        res+=1;
    }
    return res;
}
// Add here above the definition of altezza_iter
