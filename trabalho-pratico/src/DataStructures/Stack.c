#include "../../include/DataStructures/Stack.h"

#include <stdio.h>
#include <stdlib.h>

////////////////////////////////////////////////////////
typedef struct Node {
    void* data;
    struct Node* next;
} Stack_Node;

struct stack{
    Stack_Node* top;
    int size;
} ;
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
Stack* init_stack() {
    Stack* stack = malloc(sizeof(Stack));
    
    stack->top = NULL;
    stack->size = 0;
    
    return stack;
}

void push(Stack* stack, void* data) {
    Stack_Node* newNode = malloc(sizeof(Stack_Node));
    
    newNode->data = data;
    newNode->next = stack->top;
    
    stack->top = newNode;
    
    stack->size++;
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
char ** stack_to_char_array(Stack * stack, int * amount, int argumentos, void (*f)(void *,char ***,int i,int argumentos)){
    if (stack == NULL || stack->size == 0) {
        *amount = 0;
        return NULL;
    }

    *amount = stack->size;
    char **members = malloc(stack->size  * argumentos * sizeof(char *));
    Stack_Node *current = stack->top;
    
    for(int i = 0;current != NULL; i++) {
        f(current->data,&members,i,argumentos);
        current = current->next;
    }

    return members;
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void free_stack(Stack *stack) {

    while (stack->top != NULL) {
        Stack_Node *top = stack->top;
        stack->top = top->next;
        free(top);
    }
    
    free(stack);
}
////////////////////////////////////////////////////////