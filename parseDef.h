// Group no: 25
// Siddharth Jain: 2017B3A70551P
// Divya Tyagi: 2017B3A70727P
// Siva Sai Reddy: 2017B3A70779P
// Lakshya Agarwal: 2017B5A70904P

#include<stdio.h>
#include<stdlib.h>

#ifndef PARSERDEF_H
#define PARSERDEF_H

#include "driver.h"
#include<stdbool.h>
// #include "set.h"
#include "hashTableDef.h"

#define RHS_MAX_LENGTH 100
#define NO_MATCHING_RULE -1
#define MAXERRTYPESTRLEN 300


HashTable terminal_table;
HashTable non_terminal_table;

typedef enum{
    #include "nonTerminals.txt"

} nonTerminal;

typedef enum{
  #include "tokens.txt"
} tokenName;

extern char nonTerminalString[NUM_OF_NONTERMINALS][MAX_SYMBOL_LENGTH];

extern  FILE* parseTreeFilePtr;

typedef struct{
    bool isTerminal;
    union{
        tokenName t;
        nonTerminal nt;
    };
}symbol;

// each node will have either token (if terminal) else no terminal
/// & a pointer to it's next node
typedef struct rightnode{
    symbol sym;
    struct rightnode *next;
} rightnode;

typedef struct rightnode *rightExpansionPtr;

typedef struct{
    rightExpansionPtr front;
    rightExpansionPtr rear;
    nonTerminal leftnode;
}cell;

cell grammar[NUM_OF_RULES];

#endif





