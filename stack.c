// Group no: 25
// Siddharth Jain: 2017B3A70551P
// Divya Tyagi: 2017B3A70727P
// Siva Sai Reddy: 2017B3A70779P
// Lakshya Agarwal: 2017B5A70904P

#include "stackADT.h"
#include<stdio.h>
#include<stdlib.h>
stack* stackInit(){
    stack *stackPtr=(stack *)malloc(sizeof(stack));
    if(stackPtr==NULL){
        perror("Stack Initialisation Problem...No memory to allocate");
    }
    stackPtr->size=INIT_STACK_SIZE;
    stackPtr->arr=(void **)malloc(sizeof(void *)*(stackPtr->size));
    if(stackPtr->arr==NULL){
        perror("Stack member arr initialisation problem...No memory to allocate");
    }
    stackPtr->top=0;
    return stackPtr;
}

void * pop(stack * stackPtr){
    if(stackPtr->top==0)
        return NULL;
    stackPtr->top--;
    return stackPtr->arr[stackPtr->top];
}
void *peek(stack * stackPtr){
    if(stackPtr->top==0)
        return NULL;
    else
        return stackPtr->arr[stackPtr->top-1];
    
}

void push(stack *stack_ptr, void *node) {
  if (stack_ptr->top == (stack_ptr->size)) {
    stack_ptr->size *= 2;
    void **tmp =
        realloc(stack_ptr->arr, sizeof(void *) * stack_ptr->size);
    if (tmp != NULL) {
      stack_ptr->arr = tmp;
    } else {
      perror("Error in doubling stack's size: realloc failed\n");
    }
  }
  stack_ptr->arr[stack_ptr->top] = node;
  stack_ptr->top++;
}