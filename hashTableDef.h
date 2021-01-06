// Group no: 25
// Siddharth Jain: 2017B3A70551P
// Divya Tyagi: 2017B3A70727P
// Siva Sai Reddy: 2017B3A70779P
// Lakshya Agarwal: 2017B5A70904P

#ifndef HASHTABLEDEF_H  // if you've not defined HASHTABLEDEF_H somewhere, define it now
#define HASHTABLEDEF_H

#include<stdbool.h>
#define PRIME 119
#define HASH_SIZE 67
#define HASH_SIZE 67
#define MAX_LEXEME_LEN 100
#define KEY_NOT_FOUND -1

typedef struct{
    char lexeme[MAX_LEXEME_LEN];//key
    void *value;//hashvalue
    bool present;
}HashElement;
typedef HashElement HashTable[HASH_SIZE];

typedef struct stWrapper{
    HashTable ht;
    int levelNum;
    struct stWrapper *leftmostChildTable;
    struct stWrapper *rightmostChildTable;
    struct stWrapper *parentTable;//just for easy access to all nodes and avoid tree traversals
    struct stWrapper *siblingTable;
}SymbolTableWrapper;
#endif