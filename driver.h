// Group no: 25
// Siddharth Jain: 2017B3A70551P
// Divya Tyagi: 2017B3A70727P
// Siva Sai Reddy: 2017B3A70779P
// Lakshya Agarwal: 2017B5A70904P

#ifndef DRIVER_H
#define DRIVER_H

#include<stdio.h>

#define NUM_OF_TERMINALS 32
#define NUM_OF_NONTERMINALS 40
#define NUM_OF_RULES 61     // in our
#define MAX_SYMBOL_LENGTH 50
#define COLUMN_WIDTH 20


char terminal_string[NUM_OF_TERMINALS][MAX_SYMBOL_LENGTH];
char non_terminal_string[NUM_OF_NONTERMINALS][MAX_SYMBOL_LENGTH];


int num_tree_nodes;


#endif