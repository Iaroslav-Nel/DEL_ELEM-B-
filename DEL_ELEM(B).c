#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int Data;                                                          // создаем тип данных Data

struct Node                                                                // структуры
{
    Data val;
    struct Node* left;
    struct Node* right;
};

struct Node* tree_add(struct Node* tree, Data x)                           // добавить элемент в дерево 
{
    if (tree == NULL)
    {
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

void tree_print(struct Node* tree)                                      // напечатать дерево 
{
    if (tree != NULL) {
        tree_print(tree->left);
        printf("%d ", (int)tree->val);
        tree_print(tree->right);
    }
}

void tree_destroy(struct Node* tree)                                    // очищение памяти
{
    if (tree != NULL) 
    {
        tree_destroy(tree->left);
        tree_destroy(tree->right);
        free(tree);
    }
}
int MAX;          //

void tree_findmax(struct Node* tree)                                    // поиск максимума
{
    if (tree->val > MAX) 
        MAX = tree->val;
    if (tree->right != NULL) 
    {
        tree_findmax(tree->right);
    }
}

struct Node* maxim(struct Node* tree)                                   // поиск максимума
{
    if (tree->right != NULL)
    {
        tree = maxim(tree->right);
    }
    return tree;
}

struct Node* search(struct Node* tree, Data x)                          // поиск элемента в дереве
{
    if (tree->val == x)
        return tree;
    else
    {
        if (tree->val < x)
        {
            tree = tree->right;
            search(tree, x);
        }
        else
        {
            tree = tree->left;
            search(tree, x);
        }
    }
}

struct Node* search_parents(struct Node* tree, struct Node* find)           // поиск предыдущего значения от искаимого в дереве
{
    if ((tree->right == find) || (tree->left == find))
        return tree;
    else 
    {
        if (tree->val < find->val) {
            tree = tree->right;
            search_parents(tree, find);
        }
        else {
            tree = tree->left;
            search_parents(tree, find);
        }
    }
}


void deleting(struct Node* tree, Data x)                        // в этой функции происходит удаление элемента из дерева
{
    struct Node* del = search(tree, x);                 // поиск удаляемого элемента
    struct Node* par = search_parents(tree, del);       // элемент который находится перед удаляемым элементом
    if ((del->right == NULL) && (del->left == NULL)) 
    {
        if (par == NULL) 
        {
            free(del);
            return;
        }
        if (par->val < x) 
        {
            par->right = NULL;
        }
        else 
        {
            par->left = NULL;
        }
        free(del);
        return;
    }
    if (del->left == NULL) 
    {
        if (par->val > (del->right)->val) 
        {
            par->left = del->right;
            free(del);
            return;
        }
        else 
        {
            par->right = del->right;
            free(del);
            return;
        }
    }
    if (del->right == NULL) 
    {
        if (par->val < (del->left)->val) 
        {
            par->right = del->left;
            free(del);
            return;
        }
        else {
            par->left = del->left;
            free(del);
            return;
        }
    }
    if ((del->right != NULL) && (del->left != NULL))
    {
        struct Node* swap = del->right;
        struct Node* pswap = del;
        int i = 0;
        while (swap->left != NULL) 
        {
            if (i >= 1) 
            {
                pswap = pswap->left;
            }
            else 
            {
                pswap = pswap->right;
            }
            swap = swap->left;
            i++;
        }

        if (i != 0) swap->right = del->right;
        swap->left = del->left;

        if (par->val < del->val) 
        {
            par->right = swap;
        }
        else {
            par->left = swap;
        }

        pswap->left = NULL;
        free(del);
        return;
    }
}

int main() 
{
    struct Node* tree = NULL;                                           
    int a;
    scanf("%d", &a);
    while (a != 0) 
    {
        tree = tree_add(tree, a);
        scanf("%d", &a);                                                // добавляем элементы в дерево пока одно из значений не будет равно нулю    
    }
    tree_print(tree);                                                   // напечатать дерево
    tree_findmax(tree);       // найти максимальное значение в дереве
    Data a1;
    printf("\nenter Search elem, it delete from tree = ");
    scanf("%d", &a1);                                                   // Элемент который должен удалиться
    //maxim( tree->val );
    printf("Max = %d", maxim(tree)->val );                              // максимальное значение в дереве, ему же будет равна глобальная переменная MAX      
    printf("\nFound elem = %d", search(tree, a1)->val);                 // Найденный элемент в дереве
    struct Node* find = search(tree, a1);                               //
    printf("\naddress Found elem = %p", find);                          // Адрес найденного значения
    printf("\nparents Found elem = %d and parents address = %p", search_parents(tree, find)->val, search_parents(tree, find)); 
    // parents - предыдущее значение в дереве от найденного элемента ex: 1 2 3 4 5 6 7 8   -----> допустим мы искали 6, то parents = 5
    deleting(tree, a1);             // удаление элемента из дерева
    printf("\nAfter delete = ");    // как выглядит дерево после удаления
    tree_print(tree);               // напечатать дерево
    printf("\n");
    tree_destroy(tree);             // очистить память дерева
    return 0;
}
