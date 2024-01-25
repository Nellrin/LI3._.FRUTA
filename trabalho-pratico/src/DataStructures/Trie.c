#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "../../include/DataStructures/Trie.h"
#include "../../include/DataStructures/Stack.h"
#include "../../include/Tools/Utilities.h"

#define amount_of_a_date 12
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct trie_node{
    TRie_Node ** children;
    int next_entities;
    char first_char;
    char amount_chars;
    Stack * ids_names;
};
struct trie{
    TRie_Node * root;
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct date_node{
    Date_Node ** children;

    char next_entities;
};
struct trie_date{
    Date_Node ** years;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
static TRie_Node * init_trie_node(char start, char amount) {
    TRie_Node* node = (TRie_Node*)malloc(sizeof(TRie_Node));
    if (node != NULL) {
        node->first_char = start;
        node->amount_chars = amount;
        node->next_entities = 0;
        node->ids_names = init_stack();

        node->children = (TRie_Node**)malloc(node->amount_chars * sizeof(TRie_Node*));
        
        for (int i = 0; i < node->amount_chars; i++)
        node->children[i] = NULL;

    }
    return node;
}
TRie * init_trie(char start, char end){
    TRie* trie = (TRie*)malloc(sizeof(TRie));

    trie->root = init_trie_node(start,end-start+1);

    return trie;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void insert_trie(TRie* trie, char* name, char* id) {
    TRie_Node* current = trie->root;
    int index = 0;

    for (int i = 0; i < (int)strlen(name); i++){
        if(name[i] < current->first_char || name[i] >= current->first_char + current->amount_chars) continue;
        index = name[i] - current->first_char;

        if (current->children[index] == NULL)
        current->children[index] = init_trie_node(current->first_char,current->amount_chars);
        
        current->next_entities++;
        current = current->children[index];
    }


    current->next_entities++;


    push(current->ids_names,id);
    push(current->ids_names,name);
}
static void ids_names_getter(void * entity, char *** list, int i, int argumentos){
    (*list)[i*argumentos] = strdup(entity);
}
static void name_getter(TRie_Node* trie, char *** ids, char *** names, int* count){
    
    int a = 0;
    char ** list = stack_to_char_array(trie->ids_names,&a,1,ids_names_getter);

    for(int i = 0; i < a; i+=2){
        (*names)[(*count)+(i/2)] = list[i];
        (*ids)[(*count)+(i/2)] = list[i+1];
    }
    
    (*count) += (a/2);
    free(list);

    for (int i = 0; i < trie->amount_chars; i++)
        if (trie->children[i] != NULL)
        name_getter(trie->children[i], ids, names, count);
}
void lookup_prefix(TRie* trie, char *** ids, char *** names, char* prefix, int* count){
    
    TRie_Node* current = trie->root;
    for (int i = 0; i < (int)strlen(prefix); i++){
        if(prefix[i] < current->first_char || prefix[i] > current->first_char + current->amount_chars) continue;
        int index = prefix[i] - current->first_char;

        if (current->children[index] == NULL) {
            *count = 0;
            return;
        }

        current = current->children[index];
    }

    
    (*names) = malloc(sizeof(char *) * (current->next_entities));
    (*ids) = malloc(sizeof(char *) * (current->next_entities));


    name_getter(current,ids,names,count);
    sort_strings(names,ids,(*count), compare_strings);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void destroy_trie_node(TRie_Node* node){
    if (node != NULL){
        for (int i = 0; i < node->amount_chars ; i++)
        destroy_trie_node(node->children[i]);

        free_stack(node->ids_names);

        free(node->children);
        free(node);
    }
}
void destroy_trie(TRie* trie){
    if (trie != NULL) {
        destroy_trie_node(trie->root);
        free(trie);
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*tudo abaixo desta linha, foi uma tentativa de implementar
uma maneira mais eficiente de verificação de unique passengers,
onde se usaria a next entities para verificar se o user
já esteve num voo num certo ano / mês / dia,
infelizmente, não pude implementar porque, no estado em que está
resulta em segmentation fault, e quando não dá segmentation fault
ocupa cerca de 8Gb amais B)*/
static Date_Node * init_date_node(int amount, int i) {
    Date_Node* node = (Date_Node*)malloc(sizeof(Date_Node));
    if (node != NULL) {
        node->next_entities = 0;

        node->children = (Date_Node**)malloc((i*19 + amount) * sizeof(Date_Node*));
        
        for (int i = 0; i < amount; i++)
        node->children[i] = NULL;
    }

    return node;
}
TRie_Date * init_trie_date(){
    TRie_Date* trie = (TRie_Date*)malloc(sizeof(TRie_Date));

    trie->years = malloc(sizeof(Date_Node *) * 23);
    for(int i = 0; i < 23; i++)
    trie->years[i] = NULL;

    return trie;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void add_date(TRie_Date * trie, char * date){
    
    int index = 2023-atoi(date);

    if(trie->years[index]==NULL) trie->years[index] = init_date_node(amount_of_a_date,0);
    Date_Node* current = trie->years[index];

    if(current->next_entities==1)current->next_entities=2;
    else current->next_entities=1;

    for(int i = 0; i < 1; i++){
        index = atoi(date+5+(i*3)) - 1;
        
        if(current->children[index]==NULL) current->children[index] = init_date_node(amount_of_a_date,i);

        current = current->children[index];
        if(current->next_entities==1)current->next_entities=2;
        else current->next_entities=1;
    }

}
int get_date(TRie_Date * trie, short year, short month, short day){
    int result = 0;

            Date_Node* current = trie->years[2023-year];
            if(current == NULL) return result;
            
            result += (current->next_entities == 1);

                        current = current->children[month-1];
                        if(current == NULL) return result;

                        result += (current->next_entities == 1);

                                    current = current->children[day-1];
                                    if(current == NULL) return result;

                                    result += (current->next_entities == 1);

    return result;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void destroy_date_node(Date_Node* node){
    if(node != NULL){
        for (int i = 0; i < amount_of_a_date ; i++)
        destroy_date_node(node->children[i]);

        free(node->children);
        free(node);
    }
}
void destroy_date_trie(TRie_Date * trie){
    if (trie != NULL){
        for(int i = 0; i < amount_of_a_date; i++)
        destroy_date_node(trie->years[i]);

        free(trie->years);
        free(trie);
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
