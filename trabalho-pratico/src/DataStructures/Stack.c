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
void ** stack_to_array(Stack *stack, int *numMembers) {
    if (stack == NULL || stack->size == 0) {
        *numMembers = 0;
        return NULL;
    }

    void **members = malloc(stack->size * sizeof(void *));
    Stack_Node *current = stack->top;
    
    for(int i = 0;current != NULL; i++) {
        members[i] = current->data;
        current = current->next;
    }

    *numMembers = stack->size;
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