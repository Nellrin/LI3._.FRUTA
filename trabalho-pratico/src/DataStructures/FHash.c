#include "../../include/DataStructures/FHash.h"

#include <stdio.h>
#include <stdlib.h>

////////////////////////////////////////////////////////
typedef struct Node {
    void *data;
    struct Node *next;
} Node;

////////////////////////

struct h{
    Node **element;
    unsigned int amount;
};
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
static unsigned int hash(const char *str, unsigned int amount, short user){
    
    unsigned int hash;
    
    switch (user){
    case 0:
        
        hash = (atoi(str + 4))-1;

        return hash%amount;
    
    break;
    
    default:
        
        hash = 5381;
        int c;

        while ((c = *str++))
        hash = ((hash << 5) + hash) + c;    
        return hash%amount;

    break;
    }
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
FHash * fhash_init(unsigned int amount){
    FHash *almanac = malloc(sizeof(FHash));
    almanac->element = malloc(sizeof(Node *) * amount);

    for(unsigned int i = 0; i < amount; i++)
    almanac->element[i] = NULL;

    almanac->amount = amount;
    return almanac;
}
void free_fhash(FHash *almanac, void (*freeItem)(void *)){
    for (unsigned int i = 0; i < almanac->amount; i++){

        if(almanac->element[i] != NULL){
            Node *current = almanac->element[i];
            while (current != NULL) {
                Node *next = current->next;
                freeItem(current->data);
                free(current);
                current = next;
            }
        }
        
    }
    free(almanac->element);
    free(almanac);
}
////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
void check_nulls(FHash * a){
    unsigned int amount = 0;

    printf("Amount: %d\n",a->amount);
    for(unsigned int i = 0; i < a->amount; i++)
    if(a->element[i] == NULL)
    amount ++;    

    printf("Amount of NULLS: %d\n",amount);
}
static void add_to_existing(Node **element, void *new_item) {
    Node *newNode = malloc(sizeof(Node));
    
    newNode->data = new_item;
    newNode->next = *element;
    *element = newNode;
}
////////////////////////////////////////////////////////
void fhash_add(FHash *almanac,char * id, void * item, short type){

    unsigned int x = hash(id, almanac->amount,type);

    if(almanac->element[x] == NULL){
        almanac->element[x] = malloc(sizeof(Node));
        almanac->element[x]->data = item;
        almanac->element[x]->next = NULL;
    }

    else
    add_to_existing(&(almanac->element[x]),item);


}
void *fhash_get(FHash *almanac, char * target,short type, int (*f)(const char *, const void *)){
    unsigned int x = hash(target,almanac->amount, type);
    Node * current = almanac->element[x];

    while (current != NULL) {
        if (f(target, current->data))
        return current->data;


        current = current->next;
    }
    return NULL;

}
////////////////////////////////////////////////////////