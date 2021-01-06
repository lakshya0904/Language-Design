// Group no: 25
// Siddharth Jain: 2017B3A70551P
// Divya Tyagi: 2017B3A70727P
// Siva Sai Reddy: 2017B3A70779P
// Lakshya Agarwal: 2017B5A70904P

#ifndef PARSER_H
#define PARSER_H

#include "parseDef.h"
#include <stdio.h>

void insertAtEnd(rightExpansionPtr *ptrRear, symbol sym);
void grammar_fill(FILE *fptr);
symbol getSymbol(char string[]);
void make_parse_tree();
void parser_init();
void print_space(int count);
void createParseTree();
void printParseTree();
void printTypeExpressionTable();

#endif