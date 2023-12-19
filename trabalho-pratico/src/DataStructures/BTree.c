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

float exists(const void * info){
    return(info != NULL);
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

BTree *search(BTree *root, char *key, int (*compare)(const void *, const char *)) {
    if (root == NULL || compare(key, root->data) == 0)
    return root;

    if (compare(root->data, key) < 0)
    return search(root->left, key, compare);
    
    else
    return search(root->right, key, compare);
}
float do_something(BTree *root, float (*f)(const void *)){
    if (root == NULL)
    return 0;

    return (do_something(root->left,f)) + (f(root->data)) + (do_something(root->right,f));
}
////////////////////////////////////////////////////////