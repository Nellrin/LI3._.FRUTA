#include "../../include/DataStructures/SLists.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

////////////////////////////////////////////////////////
struct String_list{
    int amount;
    char ** listA; //ordenar por aqui
    char ** listB; //encher por aqui
};
////////////////////////////////////////////////////////
void print_slist(SList * a){
    printf("\n----------------------------------------------------\n");
    for(int i = 0; i < a->amount; i++)
    printf("[%s] [%s]\n",a->listA[i],a->listB[i]);


    printf("\n[AMOUNT]: %d\n",a->amount);
    printf("----------------------------------------------------\n");
}
////////////////////////////////////////////////////////
SList * slist_setter(){
    SList * a = malloc(sizeof(SList));
    
    if (a == NULL)
        return NULL;

    a->listA = NULL;
    a->listB = NULL;
    a->amount = 0;

    return a;
}
void slist_copy(SList *new, SList * origin){
    new->amount = origin->amount;

    new->listA = slists_listA_getter(origin);
    new->listB = slists_listB_getter(origin);
}
////////////////////////////////////////////////////////
char ** slists_listA_getter(SList * a){
    char ** x = malloc(sizeof(char **)*a->amount);

    if(a!=NULL){
        for(int i = 0; i<a->amount;i++)
        x[i] = strdup(a->listA[i]);
    }

    return x;
}
char ** slists_listB_getter(SList * a){
    char ** x = malloc(sizeof(char **)*a->amount);

    if(a!=NULL){
        for(int i = 0; i<a->amount;i++)
        x[i] = strdup(a->listB[i]);
    }

    return x;
}
int slists_amount_getter(SList * a){
    int x = 0;
    if(a!=NULL)
    x = a->amount;

    return x;
}
////////////////////////////////////////////////////////
void free_slists(SList * a) {
    if (a != NULL) {
        for (int i = 0; i < a->amount; ++i){
            if(a->listA[i]!=NULL)
            free(a->listA[i]);

            if(a->listB[i]!=NULL)
            free(a->listB[i]);
        }
        
        free(a->listA);
        free(a->listB);

        free(a);
    }
}
void remove_element(SList *a, char * str) {
    if(a->amount>0){

    int x;
    for(x = 0; x < a->amount; x++){
        if(!strcmp(a->listB[x],str)){
            if(a->listA[x]!=NULL)
            free(a->listA[x]);

            if(x!=a->amount-1)
            a->listA[x] = strdup(a->listA[x+1]);

            if(a->listB[x]!=NULL)
            free(a->listB[x]);

            if(x!=a->amount-1)
            a->listB[x] = strdup(a->listB[x+1]);
        }
    }

    for (int i = x; i < a->amount - 1; i++) {
        a->listA[i] = a->listA[i + 1];
        a->listB[i] = a->listB[i + 1];
    }

            if(a->listA[a->amount-1]!=NULL)
            free(a->listA[a->amount-1]);

            if(a->listB[a->amount-1]!=NULL)
            free(a->listB[a->amount-1]);

    a->amount--;
    }    
}
////////////////////////////////////////////////////////
static void swapStrings(char **str1, char **str2) {
    char *temp = *str1;
    *str1 = *str2;
    *str2 = temp;
}

void slist_sort(SList *a) {
    for (int i = 0; i < a->amount - 1; i++) {
        for (int j = 0; j < a->amount - i - 1; j++) {
            // Compare adjacent elements and swap them if they are in the wrong order
            if (strcmp(a->listA[j], a->listA[j+1]) > 0) {
                swapStrings(&a->listA[j], &a->listA[j+1]);
                swapStrings(&a->listB[j], &a->listB[j+1]);
            }
        }
    }
}
void insert_slistA(SList * a, char *elementA, char *elementB){
    for(int i = 0; i < a->amount; i++)
        if(!strcmp(elementB,a->listA[i])){
            free(a->listA[i]);
            a->listA[i] = strdup(elementA);
        }
}
void insert_slistB(SList * a, char * elementB){
    if (a == NULL)
        return;

    if (a->listA == NULL || a->listB == NULL){
        a->listA = malloc(sizeof(char *));
        a->listB = malloc(sizeof(char *));

        if (a->listA == NULL || a->listB == NULL)
            exit(EXIT_FAILURE);

        a->amount = 0;
    }

    char **tempListA = realloc(a->listA, (a->amount + 1) * sizeof(char *));
    char **tempListB = realloc(a->listB, (a->amount + 1) * sizeof(char *));

    if (tempListA == NULL || tempListB == NULL) {
        exit(EXIT_FAILURE);
    }

    a->listA = tempListA;
    a->listB = tempListB;


    if (a->listA == NULL || a->listB == NULL)
            exit(EXIT_FAILURE);

    
    a->listB[a->amount] = strdup(elementB);
    a->listA[a->amount] = strdup(elementB);

    a->amount++;
}
void insert_slistF(SList * a, char * elementA, char * elementB){
    if (a == NULL)
        return;

    if (a->listA == NULL || a->listB == NULL){
        a->listA = malloc(sizeof(char *));
        a->listB = malloc(sizeof(char *));

        if (a->listA == NULL || a->listB == NULL)
            exit(EXIT_FAILURE);

        a->amount = 0;
    }


    a->listA = realloc(a->listA, (a->amount + 1) * sizeof(char *));
    a->listB = realloc(a->listB, (a->amount + 1) * sizeof(char *));
    

    if (a->listA == NULL || a->listB == NULL)
            exit(EXIT_FAILURE);
    
    a->listB[a->amount] = strdup(elementB);
    a->listA[a->amount] = strdup(elementA);
    
    a->amount++;
}
////////////////////////////////////////////////////////