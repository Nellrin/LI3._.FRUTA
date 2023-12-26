#include <stdio.h>
#include <stdlib.h>

#include "../../include/DataStructures/BTree.h"
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
double money_trees(void * box,BTree *root, char * start, char * end, double (*f)(void *,const void *, char *, char *)){
    if (root == NULL)
    return 0;

    return (money_trees(box,root->left,start,end,f)) + (f(box,root->data,start,end)) + (money_trees(box,root->right,start,end,f));
}
void get_tlines(BTree * root, char *** list_id,char *** list_dates, int * n, void (*f)(void *, char ***,char ***, int *)){

    if(root->left!=NULL)
    get_tlines(root->left,list_id,list_dates,n,f);
    
    f(root->data,list_id,list_dates,n);

    if(root->right!=NULL)    
    get_tlines(root->right,list_id,list_dates,n,f);
}
void get_prefix(FILE * file,BTree * root, char * prefix, int * n,char F, void (*f)(FILE *, void *, int *,char, char *), short (*g)(void*,char*)){

    if(root->left!=NULL)
    // if((g(root->left->data,prefix)) || (!g(root->data,prefix)))
    get_prefix(file,root->left,prefix, n,F, f,g);    
    
    f(file,root->data,n,F,prefix);

    if(root->right!=NULL)
    // if((g(root->right->data,prefix)) || (!g(root->data,prefix)))
    get_prefix(file,root->right,prefix, n,F, f,g);
}
void get_every_node(FILE * file,BTree * root, int * n,char F, void (*f)(FILE * file,void *, int *, char)){

    if(root->left!=NULL)
    get_every_node(file,root->left,n,F,f);
    
    f(file,root->data,n,F);

    if(root->right!=NULL)
    get_every_node(file,root->right,n,F,f);
}
void get_every_node2(FILE * file,BTree * root, char ** arguments,int * n,char F, void (*f)(FILE * file,void *,char **, int *, char)){

    if(root->left!=NULL)
    get_every_node2(file,root->left,arguments,n,F,f);
    
    f(file,root->data,arguments,n,F);

    if(root->right!=NULL)
    get_every_node2(file,root->right,arguments,n,F,f);
}
////////////////////////////////////////////////////////