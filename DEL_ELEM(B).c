#include <stdio.h>
#include <stdlib.h>

typedef int Data;

struct Node {
    Data val;            
    struct Node * left;  
    struct Node * right; 
};

struct Node * tree_add(struct Node * tree, Data x) {
	if (tree == NULL) {
		tree = (struct Node*)malloc(sizeof(struct Node));
		tree->val = x;
		tree->left = NULL;
		tree->right = NULL;
		return tree;
	}
	if (x < tree->val) {
		tree->left = tree_add(tree->left, x);
		return tree;
	} 
	if (x > tree->val) {
		tree->right = tree_add(tree->right, x);
		return tree;
	}	
	return tree;	
}

void tree_print(struct Node * tree) {
	if (tree != NULL) {
		tree_print(tree->left);
		printf("%d ", (int)tree->val);
		tree_print(tree->right);
	}
}

void tree_destroy(struct Node * tree) {
	if (tree != NULL) {
		tree_destroy(tree->left);
		tree_destroy(tree->right);
		free(tree);
	}
}
int MAX;
void tree_findmax(struct Node * tree){
    if(tree->val > MAX) MAX = tree->val;
    if(tree->right != NULL){
        tree_findmax(tree->right);
    }
}

struct Node * max(struct Node * tree){
    if(tree->right != NULL){
        tree = max(tree->right);
    }
    return tree;
}
 
struct Node * search(struct Node * tree, Data x){
    if(tree->val == x) return tree;
    else{
        if(tree->val < x){
            tree = tree->right;
            search(tree, x);
        }
        else{
            tree = tree->left;
            search(tree, x);
        }
    }
}

struct Node * search_parents(struct Node * tree, struct Node * find){
    if((tree->right == find) || (tree->left == find)) return tree;
    else{
        if(tree->val < find->val){
            tree = tree->right;
            search_parents(tree, find);
        }
        else{
            tree = tree->left;
            search_parents(tree, find);
        }
    }
}


void delete(struct Node * tree, Data x){
    struct Node * del = search(tree, x);
    struct Node * par = search_parents(tree, del);
    if((del->right == NULL) && (del->left == NULL)){
        if (par == NULL){
            free(del);
            return;
        }
        if (par->val < x){
            par->right = NULL;
        } else {
            par->left = NULL;
        }
        free(del);
        return;
    }
    if(del->left == NULL){
        if(par->val > (del->right)->val){
            par->left = del->right;
            free(del);
            return;
        }
        else{
            par->right = del->right;
            free(del);
            return;
        }
    }
    if(del->right == NULL){
        if(par->val < (del->left)->val){
            par->right = del->left;
            free(del);
            return;
        }
        else{
            par->left = del->left;
            free(del);
            return;
        }
    }
    if((del->right != NULL) && (del->left != NULL)){
        struct Node * swap = del->right;
        struct Node * pswap = del;
        int i = 0;
        while(swap->left != NULL){
            if (i >= 1) {
                pswap = pswap->left;
            } else {
                pswap = pswap->right;
            }
            swap = swap->left;
            i++;
        }
        
        if(i != 0) swap->right = del->right;
        swap->left = del->left;
        
        if(par->val < del->val){
            par->right = swap;
        }
        else{
            par->left = swap;
        }
        
        pswap->left = NULL;
        free(del);
        return;
    }
}

int main() {
	struct Node * tree = NULL;
	int a = 0;
	scanf("%d", &a);
	while (a != 0) {
		tree = tree_add(tree, a);
		scanf("%d", &a);
	}
	tree_print(tree);
    tree_findmax(tree);
    Data a1;
    printf("\nenter Search elem, it delete from tree = ");
    scanf("%d", &a1);
    printf("Max = %d", max(tree)->val);
    printf("\nFound elem = %d", search(tree, a1)->val);
    struct Node * find = search(tree, a1);
    printf("\naddress Found elem = %p", find);
    printf("\nparents Found elem = %d and parents address = %p",
    search_parents(tree, find)->val, search_parents(tree, find));
    delete(tree, a1);
    printf("\nAfter delete = ");
    tree_print(tree);
    printf("\n");
	tree_destroy(tree);
	return 0;
}
