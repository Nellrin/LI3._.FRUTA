#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/DataStructures/SArrays.h"
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
struct snode{
    char * string;

    SNode *next;
};

struct slist{
    SNode * array;
    unsigned int amount;
};
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
static SNode * add_node(SNode * list, char * data) {
    SNode * node = malloc(sizeof(SNode));
    node->string = strdup(data);
    node->next = list;
    return node;
}

SArray * create_sarray(){
    SArray * a = malloc(sizeof(SArray));
    a->amount = 0;
    a->array = NULL;

    return a;
}

void add_string(SArray * list, char * data){
    list->array = add_node(list->array,data);
    list->amount++;
}

void free_list(SArray *list) {
    SNode *current = list->array;
    while (current != NULL) {
        SNode *temp = current;
        current = current->next;

        free(temp->string);
        free(temp);
    }
    free(list);
}

int checker(SArray * list, char * string){
    SNode * current = list->array;

    while(current!=NULL){
        if(!strcmp(string,current->string))
        return 1;
        current = current->next;
    }

    return 0;
}

void get_strings(SArray * list, char *** strings, int * amount){
    if(list == NULL) return;
    SNode * current = list->array;
    
    (*amount) = list->amount;
    (*strings) = realloc((*strings), sizeof(char *) * ((*amount) + list->amount));

    for(unsigned int i = 0; i < list->amount; i++, (*amount)++){
        (*strings)[(*amount)] = strdup(current->string);
        current = current->next;
    }
}
////////////////////////////////////////////////////////