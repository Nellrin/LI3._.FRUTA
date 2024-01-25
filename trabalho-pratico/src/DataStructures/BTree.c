#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
BTree *create_node(void *data) {
    BTree *newNode = malloc(sizeof(BTree));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}
void insert(BTree **root, void *data, int (*compare)(const void *, const void *)) {
    if (*root == NULL)
    *root = create_node(data);
    
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

        free(root);
    }
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void get_every_node(FILE * file,BTree * root, char ** arguments,int * n,char F, void (*f)(FILE * file,void *,char **, int *, char)){

    if(root->left!=NULL)
    get_every_node(file,root->left,arguments,n,F,f);
    
    f(file,root->data,arguments,n,F);

    if(root->right!=NULL)
    get_every_node(file,root->right,arguments,n,F,f);
}


void general_btree_function(BTree * root, char * argument,int * n){
    if(root == NULL) return;

    int date_day = strncmp(argument,root->data,10);
        switch ((*n)){
            case 0:
                (*n) += (date_day==0);    //mesmo dia
                (*n) += (strncmp(argument,root->data,7)==0);     //mesmo mes
                (*n) += (strncmp(argument,root->data,4)==0);     //mesmo ano

            break;
        case 1:
                (*n) += (date_day==0);    //mesmo dia
                (*n) += (strncmp(argument,root->data,7)==0);     //mesmo mes

            break;
        case 2:
                (*n) += (date_day==0);    //mesmo dia
            break;

        default:
            break;
        }




    if(root->left!=NULL && (*n) < 3){
        if((date_day == 0)){
            if(strncmp(argument,(root->left)->data,4) >= 0)
            general_btree_function(root->left,argument,n);
        }

        else
        general_btree_function(root->left,argument,n);
    }
    
    

    if(root->right!=NULL && (*n) < 3){
        if((date_day == 0)){
            if(strncmp(argument,(root->right)->data,4) >= 0)
            general_btree_function(root->right,argument,n);
        }

        else
        general_btree_function(root->right,argument,n);
    }
}
////////////////////////////////////////////////////////