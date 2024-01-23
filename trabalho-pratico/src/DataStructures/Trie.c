#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "../../include/DataStructures/Trie.h"
#include "../../include/Tools/Utilities.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct trie_node{
    TRie_Node ** children;
    int next_entities;
    int local_entities;
    char first_char;
    char amount_chars;
    char** ids;
    char** names; 
};

struct trie{
    TRie_Node * root;
};

static TRie_Node * init_trie_node(char start, char amount) {
    TRie_Node* node = (TRie_Node*)malloc(sizeof(TRie_Node));
    if (node != NULL) {
        node->first_char = start;
        node->amount_chars = amount;
        node->next_entities = 0;
        node->local_entities = 0;
        node->ids = NULL;
        node->names = NULL;

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

void insert_trie(TRie* trie, char* name, char* id) {
    TRie_Node* current = trie->root;
    int index = 0;

    for (int i = 0; i < (int)strlen(name); i++){
        if(name[i] < current->first_char || name[i] >= current->first_char + current->amount_chars) continue;
        index = name[i] - current->first_char;

        // if(index < 0) index = current->amount_chars -1;
        if (current->children[index] == NULL)
        current->children[index] = init_trie_node(current->first_char,current->amount_chars);
        
        current->next_entities++;
        current = current->children[index];
    }


    current->next_entities++;

    current->ids = realloc(current->ids, (current->local_entities + 1) * sizeof(char*));
    current->names = realloc(current->names, (current->local_entities + 1) * sizeof(char*));

    // if(index != MAX - 1){
        current->ids[current->local_entities] = strdup(id);
        current->names[current->local_entities] = strdup(name);
        current->local_entities++;
    // }

    // else{
    //     insert_string(&current->names,&current->ids,name,id,&current->local_entities);
    // }
}

static void name_getter(TRie_Node* trie, char *** ids, char *** names, char* prefix, int* count){
    if (trie->local_entities>0)
        for(int i = 0; i < trie->local_entities; i++){
            if(strncmp(prefix,trie->names[i],strlen(prefix)) == 0){
                (*ids)[(*count)] = strdup(trie->ids[i]);
                (*names)[(*count)] = strdup(trie->names[i]);
                (*count)++;
            }
        }

    
    for (int i = 0; i < trie->amount_chars; i++)
        if (trie->children[i] != NULL)
        name_getter(trie->children[i], ids, names, prefix, count);
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
   
    name_getter(current,ids,names,prefix,count);
    sort_strings(names,ids,(*count));
}

static void destroy_trie_node(TRie_Node* node) {
    if (node != NULL){
        for (int i = 0; i < node->amount_chars ; i++)
        destroy_trie_node(node->children[i]);

        for (int i = 0; i < node->local_entities; i++){
            free(node->ids[i]);
            free(node->names[i]);
        }
        free(node->ids);
        free(node->names);

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