#include "../../include/DataStructures/Stack.h"

#include <stdio.h>
#include <stdlib.h>

////////////////////////////////////////////////////////
typedef struct Node {
    void* data;
    struct Node* next;
} Node;

struct stack{
    Node* top;
    int size;
} ;
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
Stack* initStack() {
    Stack* stack = malloc(sizeof(Stack));
    
    stack->top = NULL;
    stack->size = 0;
    
    return stack;
}

void push(Stack* stack, void* data) {
    Node* newNode = malloc(sizeof(Node));
    
    newNode->data = data;
    newNode->next = stack->top;
    
    stack->top = newNode;
    
    stack->size++;
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void ** getStackMembers(Stack *stack, int *numMembers) {
    if (stack == NULL || stack->size == 0) {
        *numMembers = 0;
        return NULL;
    }

    void **members = malloc(stack->size * sizeof(void *));
    Node *current = stack->top;
    
    for(int i = 0;current != NULL; i++) {
        members[i] = current->data;
        current = current->next;
    }

    *numMembers = stack->size;
    return members;
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void freeStack(Stack *stack) {

    while (stack->top != NULL) {
        Node *top = stack->top;
        stack->top = top->next;
        free(top);
    }
    
    free(stack);
}
////////////////////////////////////////////////////////