// Group no: 25
// Siddharth Jain: 2017B3A70551P
// Divya Tyagi: 2017B3A70727P
// Siva Sai Reddy: 2017B3A70779P
// Lakshya Agarwal: 2017B5A70904P

#include "hashTableDef.h" 
#include "parse.h"
#define MAX_LENGTH_OF_LINE_IN_SOURCE_CODE 500


typedef struct token {
  bool isRnum;
  tokenName name;
  union {
    int num;
    double rnum;
    char str[MAX_LEXEME_LEN];  
  }id;
  int line_no;
} TOKEN;

typedef struct TOKEN *tokenPtr;


struct node{
    TOKEN token;
    struct node *next;
};
typedef struct node* NODE;

struct tokensQ{
  NODE front;
  NODE rear;
};
typedef struct tokensQ* TOKENQ;