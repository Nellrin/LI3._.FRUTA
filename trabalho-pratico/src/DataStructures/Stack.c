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
/*Dada uma Stack, e uma função específica para cada cenário (*f)
vai à stack, cria uma lista de strings capaz de conter
num_argumentos * quantidade de elementos presentes na stack,
e, dependendo de como a função (*f) for feita,
copiará informação específica de cada elemento da stack
para o array,


e.g.

se quiser o id e nome de um user, posso especificar isso na função,
e o array resultante poderá ter o seguinte aspeto

num_argumentos == 2;

(*amount) == num_elementos;
num_elementos == 2;

arr = malloc(2 * 2 * sizeof(char *))

i == 0

arr[0] == "gfaslgasi029740"
arr[0 + 1] == "José"

i += 2
i == 2

arr[2] == "IFLHSA83920417"
arr[2 + 1] == "Maria"
*/
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