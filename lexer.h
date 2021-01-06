// Group no: 25
// Siddharth Jain: 2017B3A70551P
// Divya Tyagi: 2017B3A70727P
// Siva Sai Reddy: 2017B3A70779P
// Lakshya Agarwal: 2017B5A70904P

#include "lexerDef.h"

void insert_at_end(TOKENQ tq, TOKEN t);
tokenName getTerminal(char *str);
TOKEN createToken(char *str, int line_num);

void tokenize_source_file(FILE *source,TOKENQ tq);

TOKENQ init_tokenq();