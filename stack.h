// #ifndef STACK_H
// #define STACK_H

#include "stackADTDef.h"

stack *stackInit();

void push(stack *stack_ptr, void* node);

void* peek(stack *stack_ptr);

void* pop(stack* stack_ptr);

// #endif