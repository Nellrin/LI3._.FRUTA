#include "../../include/DataStructures/BTree.h"

#include <stdio.h>
#include <stdlib.h>
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
struct btree{
    void *data;

    BTree *left;
    BTree *right;
};
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
BTree *createNode(void *data) {
    BTree *newNode = malloc(sizeof(BTree));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}
void insert(BTree **root, void *data, int (*compare)(const void *, const void *)) {
    if (*root == NULL)
    *root = createNode(data);
    
    else{
        if (compare(data, (*root)->data) < 0)
        insert(&(*root)->left, data, compare);

        else
        insert(&(*root)->right, data, compare);
    }
}
void free_tree(BTree *root){
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);

        // if (root->data != NULL)
        //     freeData(root->data);

        free(root);
    }
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
double exists(const void * info){
    return(info != NULL);
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
BTree *search(BTree *root, char *key, int (*compare)(const void *, const char *)) {
    if (root == NULL || compare(key, root->data) == 0)
    return root;

    if (compare(root->data, key) < 0)
    return search(root->left, key, compare);
    
    else
    return search(root->right, key, compare);
}
double do_something(BTree *root, double (*f)(const void *)){
    if (root == NULL)
    return 0;

    return (do_something(root->left,f)) + (f(root->data)) + (do_something(root->right,f));
}
void get_tlines(BTree * root, char *** list_id,char *** list_dates, int * n, void (*f)(void *, char ***,char ***, int *)){

    if(root->left!=NULL)
    get_tlines(root->left,list_id,list_dates,n,f);
    
    f(root->data,list_id,list_dates,n);

    if(root->right!=NULL)    
    get_tlines(root->right,list_id,list_dates,n,f);
}
void get_prefix(BTree * root, char *** list_id,char *** list_dates, char * prefix, int * n, void (*f)(void *, char ***,char ***, int *, char *)){

    if(root->left!=NULL)
    get_prefix(root->left,list_id,list_dates,prefix,n,f);
    
    f(root->data,list_id,list_dates,n,prefix);

    if(root->right!=NULL)
    get_prefix(root->right,list_id,list_dates,prefix,n,f);
}
////////////////////////////////////////////////////////