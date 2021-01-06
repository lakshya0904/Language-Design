// Group no: 25
// Siddharth Jain: 2017B3A70551P
// Divya Tyagi: 2017B3A70727P
// Siva Sai Reddy: 2017B3A70779P
// Lakshya Agarwal: 2017B5A70904P

#include "lexerDef.h"
#include "hashTable.h"
#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

tokenName getTerminal(char *s){
    char *str  = s;
    tokenName term;
    if(strcmp(str, "/") == 0){
	    term = div_op;
    }
    else if(strcmp(str, "*") == 0){
	    term = mul_op;
    }
    else if(strcmp(str, "-") == 0){
	    term = minus_op;
    }
    else if(strcmp(str, "+") == 0){
	    term = plus_op;
    }
    else if(strcmp(str, "]") == 0){
	    term = rsb;
    }
    else if(strcmp(str, "[") == 0){
	    term = lsb;
    }
    else if(strcmp(str, "&&&") == 0){
	    term = and_op;
    }
    else if(strcmp(str, "|||") == 0){
	    term = or_op;
    }
    else if(strcmp(str, "=") == 0){
	    term = equal_op;
    }
    // else if(strcmp(str, ",") == 0){
	//     term = comma;
    // }
    else if(strcmp(str, ":") == 0){
	    term = colon;
    }
    else if(strcmp(str, ";") == 0){
	    term = semicolon;
    }
    else if(strcmp(str, "{") == 0){
	    term = lcb;
    }
    else if(strcmp(str, "}") == 0){
	    term = rcb;
    }
    else if(strcmp(str, "values") == 0){
	    term = values;
    }
    // else if(strcmp(str, "colon") == 0){
	//     term = colon;
    // }
    else if(strcmp(str, "size") == 0){
	    term = size;
    }
    else if(strcmp(str, "R1") == 0){
	    term = r1;
    }
    else if(strcmp(str, "integer") == 0){
	    term = integer;
    }
    else if(strcmp(str, "of") == 0){
	    term = of;
    }
    else if(strcmp(str, "..") == 0){
	    term = dotdot;
    }
    else if(strcmp(str, "array") == 0){
	    term = array;
    }
    else if(strcmp(str, "jagged") == 0){
	    term = jagged;
    }
    else if(strcmp(str, "boolean") == 0){
	    term = boolean;
    }
    else if(strcmp(str, "real") == 0){
	    term = real;
    }
    else if(strcmp(str, "variables") == 0){
	    term = variables;
    }
    else if(strcmp(str, "list") == 0){
	    term = list;
    }
    else if(strcmp(str, "declare") == 0){
	    term = declare;
    }
    else if(strcmp(str, "(") == 0){
	    term = lpar;
    }
    else if(strcmp(str, ")") == 0){
	    term = rpar;
    }
    else if(strcmp(str, "program") == 0){
	    term = program;
    }
    else if(isalpha(str[0])){
        term = id;
    }
    else if(strcmp(str,"epsilon")==0)  // No impact 
    {
         term=epsilon;
    }
    
    // if(str[0]>='0' && str[0]<='9'){
    //     term=num;
    // }


    else if(str[0]>=48 && str[0]<=57){
        // printf("NUMBBBBBBER %s\n",str);
        // boolean point=false;
        
        term = num;
    }
    // else{
    //     // printf("printing -1 %s\n",str);
    //     return -1;
    // }
    // else if(strcmp(str,"45")){
    //     printf("45 is here");
    //     term =num;
    // }
    // printf(" String is %s ANd Term: %d \n",str,term);
    return term;
    
}


TOKEN createToken(char *st, int line_num){
    TOKEN t;
    char *str = st; 
    t.name=getTerminal(str);
    t.line_no = line_num;
    if(t.name==num){
        
        if(strchr(str, '.')!=NULL) // char* willl be returned..   // .42 fails 
        {   
            // printf("IN RNUM %s\n",str);
             char *ptr;
            char ch[123];
            strcpy(ch,str);
            double d = strtod(ch,NULL);
            // printf("assigned rnum: %lf",d);
            t.id.rnum = d;
            // printf("assigned rnum: %lf",t.id.rnum);
            t.isRnum=true;
        }
        else{
            t.isRnum=false;
            t.id.num = atoi(str);
        }
    }
    else{
        // t.isRnum=false;
        strcpy(t.id.str,str);
    }
    return t;
}

void insert_at_end(struct tokensQ* tq, TOKEN t){
    NODE node = (NODE)malloc(sizeof(struct node));
    // if yoi donr assign mem, it goes fine to day Insertion failed 
    if (node == NULL) {
        perror("Insertion failed\n");
        exit(1);
    }
    node->token=t;   
    node->next=NULL;  
    if(tq->front==NULL){
        tq->front=node;
        tq->rear=node;
        return;
    }
    (tq->rear)->next=node;
    tq->rear=node;
    
    return;
    
}


void tokenize_source_file(FILE *source,struct tokensQ* tq){
    char buffer[MAX_LENGTH_OF_LINE_IN_SOURCE_CODE]; 
    int line_num = 0;
    while(fgets(buffer,sizeof(buffer),source)!=NULL){
        // printf("ENTERED into fgets");
        char *symRead;
        symRead=strtok(buffer," \t\n");   // needed ??
        // printf("%s ",symRead);
        for(int i=0; symRead!=NULL; ++i){
            // printf("%s |||| ",symRead);
            TOKEN t = createToken(symRead, line_num);
            
            // printf("\n%d",t.line_no);
            // printf("\t%s",t.id.str);
        
            insert_at_end(tq, t);
        
            // printf("%p insert_at_end\n", tq->rear);
            // printf("%p insert_at_end\n",tq->rear->token);            
            // printf("%s insert_at_end\n",tq->rear->token.id.str);   
            symRead=strtok(NULL," \t\n");//   symRead=strtok(NULL,"\n"); means u want to read till you get \n
        }
        // printf("\n");
        line_num++;
        //if(line_num==5) return; 
    }
    return; 
}

