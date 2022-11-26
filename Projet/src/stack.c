#include "../headers/stack.h"
#include <stdio.h>

void init_stack(stack_t* stack) {
    stack->head = NULL;
    stack->size = 0;
}

void push(stack_t* stack, void* data) {
    node_t* node = malloc(sizeof(node_t));
    if (node == NULL) {
        perror("Memory allocation in push failed.");
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->next = stack->head;
    stack->head = node;
    stack->size++;
}

void* pop(stack_t* stack) {
    if(stack->size == 0) {
        return NULL;
    }
    void* data = stack->head->data;
    node_t* node_to_free = stack->head;
    stack->head = stack->head->next;
    free(node_to_free);
    stack->size--;
    return data;
}

