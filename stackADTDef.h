// #ifndef STACK_ADT_H
//     #define a 200
// else
// {
//     #define a 22
// }
// #endif
// #define STACK_ADT_H
// #include "parseDef.h"
// #include "treeADT.h"

#define INIT_STACK_SIZE 200

/**
 * @brief Stack implemented as dynamic array
 *
 */
typedef struct
{
    void **arr;
    int top;
    int size;
} stack;

// #endif