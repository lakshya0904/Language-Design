// Group no: 25
// Siddharth Jain: 2017B3A70551P
// Divya Tyagi: 2017B3A70727P
// Siva Sai Reddy: 2017B3A70779P
// Lakshya Agarwal: 2017B5A70904P

// #include "parse.h"
// #include "lexer.h"   // NOT DEFINED YET
#include<string.h>
#include "hashTable.h"
#include <ctype.h>
#include <malloc.h>
#include <math.h>
#include "stack.h"  // NOT DEFINED
// #include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"      // ORIGIN COMMENT
#include "parseDef.h"  //extra added
#include "parse_table.h"
// #include "treeADT.h"     ORIGIN UNCOMMENT
// #include "semantic_analyzer.h"
// symbol getSymbol(char string[]);

// treeasdtdef

extern char non_terminal_string[NUM_OF_NONTERMINALS][MAX_SYMBOL_LENGTH];
extern char terminal_string[NUM_OF_TERMINALS][MAX_SYMBOL_LENGTH];


typedef struct TREENODE
{
  int depth;
  symbol sym;     //stores information of node being a terminal or a non terminal and its enum
  TOKEN token;    //initialised only in case of terminal ( lexem + line no. + enum )
  int num_child;  //number of childrens of this node.
	//to store leftmost and rightmost childs of any node
  struct TREENODE *leftmost_child;
  struct TREENODE *rightmost_child;
  //to store right sibling of any node.
  struct TREENODE *sibling;
  struct TREENODE *parent;
  //type *encl_fun_type_ptr; //later include header file which has its defination
} tree_node;

// treeadt.h

/********************/
struct range_element{
    bool is_variable;
    union
    {
        char* lexeme;
        int val;
    } value;
};
typedef struct range_element range_element;
/********************/

/********************/
enum type_val{
    primitive, rect_array, jagged_array
};
typedef enum type_val  type_val;
/********************/

/********************/
struct type{
    bool is_array;   
    type_val tv;
    int is_dynamic;     // 0, 1, -1 (NA)
    union type_expr
    {
        tokenName t;          // Integer /Real /Boolean
        
        struct
        {
            int num_dimensions;
            range_element ***range_values;
            tokenName basic_elem_type;
        } rect;
        
        struct
        {
            int num_dimensions; // 2 or 3
            int first_dim_lval;
            int first_dim_rval;
            int **further_dims;
        } jagged;
    } texp ;
};
typedef struct type  type;
/********************/

/********************/
typedef struct Linkedlist_node{
    char* var_name;
    type* type_exp;
    struct Linkedlist_node *next;
} linkedlist_node ;
/********************/

tree_node* create_tree_node();

void add_child(tree_node *parent, tree_node *child);

tree_node* delete_child(tree_node* parent, tree_node* prev, tree_node *child);

tree_node *get_nth_child(tree_node *root, int n);

//tree.c

tree_node* create_tree_node() 
{
   
    tree_node *node = (tree_node *)malloc(sizeof(tree_node));
    
    if (node == NULL) 
    {
      perror("tree_node allocation error..\n");
      exit(0);
    }

    node->parent = NULL;
    node->sibling = NULL;
    node->leftmost_child = NULL;
    node->rightmost_child = NULL;
    node->num_child = 0;
    strncpy(node->token.id.str, "", MAX_LEXEME_LEN);
    //node->encl_fun_type_ptr = NULL;
    return node;

}


void add_child(tree_node *parent, tree_node *child)
{    
    if (parent->rightmost_child == NULL) 
    {
      parent->leftmost_child = child;
      parent->rightmost_child = child;
    }

    else
    {
      parent->rightmost_child->sibling = child;
      parent->rightmost_child = child;
    }
  
    parent->num_child++;
    child->parent = parent;
    child->sibling = NULL;
}

tree_node *delete_child(tree_node *parent, tree_node *prev, tree_node *child) 
{
    if (prev != NULL) 
    {
       prev->sibling = child->sibling;
    }

    if (child == parent->leftmost_child) 
    {
      parent->leftmost_child = child->sibling;
    }

    if (child == parent->rightmost_child) 
    {
      parent->rightmost_child = prev;
    }
  
    free(child);
  
    parent->num_child--;

    if (prev != NULL)
      return prev->sibling;
    else
      return parent->leftmost_child;
}


tree_node *get_nth_child(tree_node *root, int n)
{
  	if((root == NULL) || (n > root->num_child))
	  	return NULL;
	
	  tree_node *tmp_child = root->leftmost_child;

	  for(int i = 1; i < n; i++)
    {		
      // loop tells how many child u have to go ahead
		  tmp_child = tmp_child->sibling;
	  }

	  return tmp_child;
}





void parser_init() {

  initialiseHashTable(terminal_table);
  initialiseHashTable(non_terminal_table);

  // initialize all first sets to be null
  // for (int i = 0; i < NUM_OF_NONTERMINALS; i++) {
	// set_init(first_set[i]);
  // }

  for (int i = 0; i < NUM_OF_TERMINALS; i++) {
    //   printf("Insert in terminal table ");
	hashInsert(terminal_table, terminal_string[i], i);
  }

  for (int i = 0; i < NUM_OF_NONTERMINALS; i++) {
	hashInsert(non_terminal_table, non_terminal_string[i], i);
  }

  // initializing parse table
//   for (int i = 0; i < NUM_OF_NONTERMINALS; i++) {
//     for (int j = 0; j < NUM_OF_TERMINALS; j++) {
//       parse_table[i][j] = NO_MATCHING_RULE;
//     }
//   }

	num_tree_nodes = 0;
}

void insertAtEnd(rightExpansionPtr *ptrRear, symbol sym) {
// create a node  & insert it @ end
// rightExpansionPtr is ptr 
  rightExpansionPtr node = (rightExpansionPtr)malloc(sizeof(rightnode));

  if (node == NULL) {
// The POSIX error function, perror, is used in C and C++ to print an error message to stderr, based on the error state stored in errno.It prints str 
	perror("Insertion failed\n");
	exit(1);
  }
  node->sym = sym;
  node->next = NULL;
    // O(1) access directly with tail . Can also acces through head 
  if (*ptrRear != NULL) {
	  (*ptrRear)->next = node;//(*ptrRear) accessing the actual rear pointer
  }
  // for the first node ptrRear wpuld be nul intilally 
  *ptrRear = node;
//   printf("%p\t",&(*ptrRear)->sym);
}

symbol getSymbol(char string[]){
    symbol sym;// = (symbol)malloc(sizeof(symbol));
    // NEED NOT TO ALLOCATE SPACE FOR SYMB ??
    // getSymbol() is defined for both terminals & non-termianls. But All NTs are mad of capital letters. So just check the first char & decide if its a NT or T
    // if NTerminal

    if(!((string[0]<='Z') && (string[0]>='A'))){
        sym.isTerminal=true;
        // printf("1");
        char temp[strlen(string)];
        // printf("2");
        strcpy(temp,string);
        // printf("3");
        // seems all the entries  -keys in HT are in UPPer case, so converting terminals to uper case. 
        // You don't need that for NTs as they are alrady upper
        // CAN DO: check if all are CAPS for NT'S
        // for(int i=0; i<strlen(temp); ++i){
        //     // printf("4");
        //     temp[i]=toupper(temp[i]); // C FUNCTION toUpper()
        // }
        // printf("5");
        sym.t=searchHashTable(terminal_table,temp);
        // printf("6");
        // CAN DO: It seems that are using 2 differnt HTs fr terminals & non-termianls. Can just merge into one & search directly w/o if-else condn
    }
    else{
        sym.isTerminal=false;
        sym.nt=searchHashTable(non_terminal_table,string);//giving enum coressponding to this lexeme or return -1
        //printf("In getSymbol() : string is %s and non-terminal is %d \n ", string, sym.nt);
    }
    return sym;
}


// fptr to grammar.txt
void grammar_fill(FILE *fptr){
    // populate_terminal_string();
    // populate_non_terminal_string();
    int ruleNum=0;
    char buffer[RHS_MAX_LENGTH];
// Read lines from fptr and store in buffer
// It stops when sizeof(buffer) characters are read, the newline character is read, or the end-of-file is reached, whichever comes first.
    while(fgets(buffer,sizeof(buffer),fptr)!=NULL){
        int i;
        char *symRead;
        // Doubt : Should be space ? Becoz, fgets make you read only one line at at time!
        symRead=strtok(buffer," \n");    //predefined function #include<string.h>
        // WAS symRead=strtok(buffer,"\n");
        // loop over 1 line of grammar ! 
        // printf("\n");
        for(int i=0; symRead!=NULL; ++i){
        //   printf(" SymRead is %s ",symRead);
            
            if(i!=0){
                // store the token, 
                symbol sym=getSymbol(symRead);
                // insert at end
                insertAtEnd(&(grammar[ruleNum].rear),sym);
                // if((grammar[ruleNum].rear)->sym.isTerminal)
                //   printf(" right node terminal %d",(grammar[ruleNum].rear)->sym.t);
                // else
                // {
                //     // printf(" right node non-term %d",(grammar[ruleNum].rear)->sym.nt);
                // }
                
                // for the first RHS symbol.. 
                if(grammar[ruleNum].front==NULL){
                    grammar[ruleNum].front=grammar[ruleNum].rear;
                }
            }
            // get the next sumbol(terminal/ nonterminal from line)
            // space agin here ?? 
            else{
                // storing the LHS(no terinal) its' symbol, pointer to right nodes
                grammar[ruleNum].leftnode=getSymbol(symRead).nt;
                // printf("\n GET SYMBOL  %d",grammar[ruleNum].leftnode); 
                grammar[ruleNum].front=NULL;
                grammar[ruleNum].rear=NULL;
            }
            symRead=strtok(NULL," \n");
        }
        // go to next rule 
        ruleNum++;
      
    }
}

  


// struct node* init_get_next_token(FILE* source){
struct tokensQ* init_get_next_token(FILE* source){

    // printf("ENTERED init_get_next_token");
	if (source == NULL) {
		printf("Error opening file\n");
	}

    struct tokensQ* tq = (struct tokensQ*) malloc(sizeof(struct tokensQ));
                                // remove this 23 ? 
	tokenize_source_file(source,tq);

    // printf("FINISHED init_get_next_token");

    return tq;//->front;
   
}

TOKEN get_next_token(struct tokensQ* tq){

    if(tq->front!=NULL){
        TOKEN t = (tq->front)->token;
        tq->front = (tq->front)->next;
        return t;
    }

    if(tq->front==NULL){
        // printf("Tokens linked-list ended !! ");
        TOKEN t;
        t.line_no=-1;
        return t;
        // return NULL:
    }

    // return t;
}
// parses entire program 

tree_node *parseInputSourceCode(FILE * sourceCode){     //, FILE* grammarRules

    struct tokensQ* tokenqueue =  init_get_next_token(sourceCode);
    // printf("EXITED FROM TOKENIZE SOURCE CODE ");

    // parser_init();   // SHOULD BE BEFORE GRAMMAR FILL RIGTHT ?? Yes
    // int rule_no=0;
    TOKEN tkn=get_next_token(tokenqueue); 
    // printf(" getToken() %d",tkn.name);
    // printf("EXITED FROM TOKENIZE get next token ");
    
    stack *auxStack=stackInit();   // to ensure left-most derivation. 
    stack *mainStack=stackInit();
  
    tree_node *root=create_tree_node();
    // start with pushing the PROGRAM
    // INCLUDE THE requred file header
    root->sym.nt=PROGRAM;
    root->sym.isTerminal=false;
    root->depth=0;
    push(mainStack,root);
    // printf("5");
    
    if(tkn.line_no==-1) return root;
    while (true)
    {
        num_tree_nodes++;
        tree_node *node=(tree_node *)pop(mainStack);
        // popping from main stack one by one
        if(node==NULL) return root;
        // printf("entered while(true) \n ");
        // printf("Is terminal %d\n",(node->sym).isTerminal);
        // printf("node is Terminal ?? : %s\n", (node->sym).isTerminal ? "true" : "false");
        if((node!=NULL) &&(node->sym).isTerminal==true){
            // if epsilon, sthg terminated here, continue     
            if(node->sym.t==epsilon){//made small case
                strncpy(node->token.id.str,"epsilon",MAX_LEXEME_LEN);
                node->token.name=epsilon;//made small case
                continue;
                
            }
                
                switch(tkn.name){
                    case num://made small case
                        if(tkn.isRnum)
                          node->token.id.rnum = tkn.id.rnum;
                        else
                          node->token.id.num = tkn.id.num;
                        break;

                    // case rnum://made small case
                    //     node->token.id.rnum = tkn.id.rnum;
                    //     break;

                    default:
                        strncpy(node->token.id.str, tkn.id.str, MAX_LEXEME_LEN);
                }
                node->token.line_no=tkn.line_no;
                node->token.name=tkn.name;
                tkn = get_next_token(tokenqueue);

                if(tkn.line_no==-1) return root;
	            continue; 
            // }//corressponding to else part
        }   // NEWLY INSERTED 
            
        if(tkn.line_no==-1) return root;

        if (node == NULL) {
            break;
        }
        int rule_no = parse_table[node->sym.nt][tkn.name];
        // printf("Rule no: %d\n",rule_no);
        if (rule_no == NO_MATCHING_RULE) {
            continue;
        }  
        
        // printf("RULE NO %d\n",rule_no);
        cell rule = grammar[rule_no];
        rightExpansionPtr rhs_ptr = rule.front;
          for(;rhs_ptr != NULL;rhs_ptr = rhs_ptr->next){
            tree_node *temp = create_tree_node();

            temp->parent = node;    // the current node is the parent of the node of the RHS grammar !!
            temp->depth = node->depth+1;
            temp->sym = rhs_ptr->sym;
            add_child(node, temp);
            push(auxStack, temp); 
        }

        tree_node *temp = (tree_node *)pop(auxStack);

        while (temp != NULL) {
            push(mainStack, temp);
            temp = (tree_node *)pop(auxStack);
        }
    // }
    
    }
    return root;
}

void print_space(int count){
  int i=0;
  for(i=0; i<count; ++i)
    printf(" ");
}

void pretty_print(char *s) {
	int column_size = COLUMN_WIDTH, len, left_margin;

	len = strlen(s);
	left_margin = (column_size - len) / 2;
  print_space(left_margin);

	printf("%s", s);
	
	int right_margin = left_margin;
	
	if (len % 2 == 1)
		right_margin++;
  print_space(right_margin);
	
	printf("|");
}

void print_node(tree_node *node) 
{
	char *s = (char *)calloc(MAX_LEXEME_LEN, sizeof(char));
	for (int i = 0; i < MAX_LEXEME_LEN; i++) 
	{
		s[i] = '\0';
	}

	if(node == NULL)
		return;

	bool isTerminal = (node->sym).isTerminal;

  // char depthstr[5];
  // snprintf(depthstr, MAX_LEXEME_LEN, "%d", node->depth);

	if(isTerminal==false) 
	{
    // printf("\t\t%s\n",non_terminal_string[(node->sym).nt]);//symbol name
    pretty_print(non_terminal_string[(node->sym).nt]);
    // printf("   |   \n");
    pretty_print("no");//is terminal
    pretty_print("type exp");//type expression not there with us...
    pretty_print("----");
		pretty_print("----");
    if (node->parent)//grammar rule
			pretty_print(non_terminal_string[(node->parent->sym).nt]);
		else
			pretty_print("(ROOT)");

    // pretty_print(s);
    char depthstr[5];
    // sprintf(depthstr, "%d", node->depth);
    // pretty_print(depthstr);
    snprintf(depthstr, MAX_LEXEME_LEN,"%d", node->depth);
    pretty_print(depthstr);
		// pretty_print("----");//lexeme as in : literally written as colon
		// pretty_print("----");//value in case of num and rnum
    printf("\n");
		

	}

	else{

    // printf("\n%s\n", terminal_string[(node->sym).t]);//symbol name
    pretty_print(terminal_string[(node->sym).t]);//symbol name
    // printf("   |   \n");
		pretty_print("yes");//is terminal
    pretty_print("type exp");//type expression not there with us...

		if((node->token.name != num /*&& node->token.name != rnum*/) && node->token.id.str != NULL)
		{
			snprintf(s, MAX_LEXEME_LEN, "%s", (node->token).id.str);
			pretty_print(s);
		} 
		else
		{
			pretty_print("----");
		}
		snprintf(s, MAX_LEXEME_LEN, "%d", (node->token).line_no+1);
		pretty_print(s);

    snprintf(s, MAX_LEXEME_LEN, "%s", non_terminal_string[(node->parent->sym).nt]);
    //above n below are for grammar rule
		pretty_print(s);

    char depthstr[5];
    snprintf(depthstr, MAX_LEXEME_LEN,"%d", node->depth);

    pretty_print(depthstr);
		
    printf("\n");
		
	} 
}


void print_parse_tree(tree_node *root) {
	if (root == NULL)
		return;
    // pre-order traversal 
	printf("\n");
	print_node(root);

	if (root->leftmost_child)
		print_parse_tree(root->leftmost_child);
	if (root->leftmost_child)
  	{
      tree_node *temp = root->leftmost_child->sibling;

      while (temp != NULL) 
      {
        print_parse_tree(temp);
        temp = temp->sibling;
      }
  	}
}

void make_parse_tree(){
    // FILE *source = fopen("sourcecode.txt", "r");
	// if (source == NULL) {
	// 	printf("Error opening file\n");
	// }

    // struct tokensQ* tq = (struct tokensQ*) malloc(sizeof(struct tokensQ));//look into size if some error occurs...
  
    // struct tokensQ* tokenqueue = init_get_next_token(source);
    // TOKEN tkn=get_next_token(tokenqueue);
    // return; 
    FILE* sourceCode = fopen("sourcecode.txt","r");
    FILE* grammarRules = fopen("grammar.txt","r");

    // populate_terminal_string();
    // printf("\nterminal string populated");
    // populate_non_terminal_string();
    // printf("\nnon-terminal string populated");

    parser_init();
    grammar_fill(grammarRules);     // IS IT NECESSARY ?
    // printf("ENTERING parseInputSourceCode ");
    tree_node* x = parseInputSourceCode(sourceCode);    //,grammarRules
    printf("\n");
    pretty_print("Symbol name");
    pretty_print("Is terminal");
    pretty_print("Type Exp");
    pretty_print("Lexeme name");
    pretty_print("Line no");
    pretty_print("Grammar Rule");
    pretty_print("Depth of node");
    print_parse_tree(x);
    // printf("parse tree printed!!");
    return ; 
}
void createParseTree(){
  FILE* sourceCode = fopen("sourcecode.txt","r");
  FILE* grammarRules = fopen("grammar.txt","r");
  parser_init();
  grammar_fill(grammarRules);     // IS IT NECESSARY ?
  // printf("ENTERING parseInputSourceCode ");
  tree_node* x = parseInputSourceCode(sourceCode);    //,grammarRules
} 
void printParseTree(){
  make_parse_tree();
}

/********************/
int compare_type( type *a, type* b )
{
    if(a->tv!=b->tv)                          // // Ensure that they are of same type ( out of primitive, rect, jagged )
      return 0;
    else if( a->tv == 0 && a->texp.t!=b->texp.t )        // // Ensure that if they are of same type out of Int/ real/ bool 
      return 0;
    else if( a->tv == 1 && ( a->texp.rect.basic_elem_type != b->texp.rect.basic_elem_type || a->texp.rect.num_dimensions != b->texp.rect.num_dimensions ) )  // // if they are rect and then basic_ele_type or dimension dont match
      return 0;
    else if( a->tv == 1 ) // if ranges dont match return 0;
    {
        for( int i = 0 ; i < a->texp.rect.num_dimensions ; i++ )
        {
            if( a->texp.rect.range_values[i][0] != b->texp.rect.range_values[i][0] || a->texp.rect.range_values[i][1] != b->texp.rect.range_values[i][1] )
              return 0; 
        }
    }
    // //// when they are jagged
    // // else if( ) 
    // // 
    else
    {
        printf("no support provided for jagged in compare_type function type.c");
    }
    return 1;
}
/********************/

/********************/
linkedlist_node *insert( linkedlist_node *head, linkedlist_node *node ){
    linkedlist_node *temp = head;
    if( !head ) {
        return node;
    }

    while( temp->next ) {
        temp = temp->next;
    }
    temp->next = node;
    return head;
}
/********************/

/********************/
linkedlist_node *get_type( tree_node *node,  linkedlist_node *head )
{
    // node points to DECLARATION_DASH node.
    type *pointingto_type = (type*) malloc( sizeof(type) );
    // // pointer to TYPE node
    tree_node *pointingto_TYPE = node->rightmost_child ;
    // // pointer to datatype node ( integer/ real/ Boolean/ ARRAY )
    tree_node *pointingto_datatype = pointingto_TYPE->leftmost_child ;

    // //// if pointingto_datatype points to terminals like integer/ real/ boolean
    if( pointingto_datatype->sym.isTerminal ) {
        // //// basic initialisation for terminals like integer/ real/ boolean
        pointingto_type->is_array = false ;
        pointingto_type->is_dynamic = -1 ;
        pointingto_type->tv = 0;
        // //////////////////////////////////////////////////////////////////        
        // //// Checking is it single or multiple variable declaration
        tokenName p = id ;
        // FINE
        // // for single variable declaration.
        if( node->leftmost_child->token.name == p ) {
            // // storing datatype of id in tokenName of type.
            pointingto_type->texp.t = node->rightmost_child->leftmost_child->token.name;            
            // // make single entry into hash table ( key -> node->leftmost->token.id.str , value = pointingto_type ).
            linkedlist_node *pointingto_linkedlist_node = (linkedlist_node*) malloc( sizeof(linkedlist_node) );
            pointingto_linkedlist_node->var_name =  node->leftmost_child->token.id.str ;
            pointingto_linkedlist_node->type_exp =  pointingto_type;
            pointingto_linkedlist_node->next = NULL;
            head = insert( head, pointingto_linkedlist_node );
            return head;      
        }
        // FINE
        
        
        // // for multiple variable declaration.
        else{
            pointingto_type->texp.t = node->rightmost_child->leftmost_child->token.name;
            tree_node *g = get_nth_child( node, 4 ) ; 
            tokenName h = epsilon ;
            while( 1 )
            {   
                linkedlist_node *pointingto_linkedlist_node = (linkedlist_node*) malloc( sizeof(linkedlist_node) );
                pointingto_linkedlist_node->var_name =  g->leftmost_child->token.id.str ; // changes made leftmost_child->rightmost_child
                pointingto_linkedlist_node->type_exp =  pointingto_type;
                pointingto_linkedlist_node->next = NULL;
                head = insert( head, pointingto_linkedlist_node );
                g = g->rightmost_child->rightmost_child;
                if(g->num_child==0)
                    break;
                
            }  
            return head;
        }
    }
    // else{
    //     tree_node *pointingto_ARRAYtype = pointingto_datatype->leftmost_child;
    //     // // if ARRAY type is RECTANGULAR
    //     nonTerminal p = RECTANGULAR;
    //     if( pointingto_ARRAYtype->sym.nt == p ){
    //         // storing datatype of id's in struct rect basic_elem_type.
    //         tree_node *pointingto_basic_elem_type = get_nth_child( pointingto_ARRAYtype, pointingto_ARRAYtype->num_child-1 );
    //         pointingto_type->texp.rect.basic_elem_type = pointingto_basic_elem_type->token.name;
    //         // storing dimensions.
    //         pointingto_type->texp.rect.num_dimensions = 0;
    //         tree_node *pointingto_LiST_OF_RANGE = get_nth_child( pointingto_ARRAYtype, 2 );
    //         tree_node *b = pointingto_LiST_OF_RANGE ; // // just renaming
    //         tokenName h = epsilon ;
    //         tokenName o = id ;
    //         while( 1 ) {   
    //             // pointer to lower and higher INDEX
    //             tree_node *pointing_to_lower_INDEX = get_nth_child( b, 2 ) ;
    //             tree_node *pointing_to_higher_INDEX = get_nth_child( b, 4 ) ;
    //             // pointer to lower and higher num/ id.
    //             pointing_to_lower_INDEX = pointing_to_lower_INDEX->leftmost_child ;
    //             pointing_to_higher_INDEX = pointing_to_higher_INDEX->leftmost_child ;
    //             range_element *lower_range = (range_element*) malloc( sizeof(range_element) );
    //             range_element *higher_range = (range_element*) malloc( sizeof(range_element) );
    //             if( pointing_to_lower_INDEX->token.name == h ) {
    //                 lower_range->is_variable = true;
    //                 lower_range->value.lexeme = pointing_to_lower_INDEX->token.id.str ;
    //             }
    //             else { 
    //                 lower_range->is_variable = false;
    //                 lower_range->value.val = pointing_to_lower_INDEX->token.id.num ;
    //             }
    //             if( pointing_to_higher_INDEX->token.name == h) {
    //                 higher_range->is_variable = true;
    //                 higher_range->value.lexeme = pointing_to_higher_INDEX->token.id.str ;
    //             }
    //             else { 
    //                 higher_range->is_variable = false;
    //                 higher_range->value.val = pointing_to_higher_INDEX->token.id.num ;
    //             }
    //             pointingto_type->texp.rect.range_values[pointingto_type->texp.rect.num_dimensions][0] =  lower_range;
    //             pointingto_type->texp.rect.range_values[pointingto_type->texp.rect.num_dimensions][1] =  higher_range;
    //             pointingto_type->texp.rect.num_dimensions = pointingto_type->texp.rect.num_dimensions + 1 ;
    //             if( b->rightmost_child->leftmost_child->token.name == o )
    //                 break;
    //             b = b->rightmost_child->rightmost_child ;
    //         }
    //         // // getting all the id's.
    //         tree_node *pointingto_INPUT_LIST = get_nth_child( node, 4 ) ;
    //         tree_node *g = pointingto_INPUT_LIST; // // this is just a name change
    //         h = epsilon ;
    //         while( 1 ){
    //             linkedlist_node *pointingto_linkedlist_node = (linkedlist_node*) malloc( sizeof(linkedlist_node) );
    //             pointingto_linkedlist_node->var_name =  g->leftmost_child->token.id.str ; // changes made leftmost_child->rightmost_child
    //             pointingto_linkedlist_node->type_exp =  pointingto_type;
    //             pointingto_linkedlist_node->next = NULL;
    //             head = insert( head, pointingto_linkedlist_node );
    //             g = g->rightmost_child->rightmost_child;
    //             if(g->num_child==0)
    //                 break;
    //         }
    //         return head;
    //     } 
    //     // if ARRAY type is jagged
    //     else{
    //         tree_node *pointingto_ARRAYtype = pointingto_datatype->leftmost_child;
    //         // if ARRAY type is JAGGED
    //         nonTerminal p = JAGGED;
    //         if( pointingto_ARRAYtype->sym.nt == p ){
    //             // storing datatype of id's in struct rect basic_elem_type.
    //             tree_node *pointingto_basic_elem_type = get_nth_child( pointingto_ARRAYtype, pointingto_ARRAYtype->num_child-2 );
    //             pointingto_type->texp.rect.basic_elem_type = pointingto_basic_elem_type->token.name;
             
    //             // Store first dimension low and high index
    //             tree_node *pointing_to_lower_INDEX = get_nth_child( pointingto_ARRAYtype, 4);
    //             tree_node *pointing_to_higher_INDEX = get_nth_child( pointingto_ARRAYtype, 6);
    //             pointingto_type->texp.jagged.first_dim_lval = pointing_to_lower_INDEX->token.id.num;
    //             pointingto_type->texp.jagged.first_dim_rval = pointing_to_higher_INDEX->token.id.num;

    //             // Calculating number of dimensions
    //             tree_node *pointingto_multi_dim = get_nth_child( pointingto_ARRAYtype, pointingto_ARRAYtype->num_child-4 );
    //             tokenName p = lsb;
    //             if( pointingto_multi_dim->rightmost_child->leftmost_child->sym.t == p ){
    //                 pointingto_type->texp.jagged.num_dimensions = 3;
    //             }
    //             else{
    //                 pointingto_type->texp.jagged.num_dimensions = 2;
    //                 // // Store 2nd dimension
    //             }
    //         }
    //         return head;
    //     }
    // }
    return head;
}
/********************/

/********************/
linkedlist_node *Bulid_type_exp_table(  tree_node *root,  linkedlist_node *head ) {
    if( !root )
      return head;
    else {
        nonTerminal p = DECLARATION ;
        // if ( root is declare node ) call get_type and return ( to parent of declare node which will then visit it other children nodes. ) 
        if( !root->sym.isTerminal && root->sym.nt == p ) {
            head = get_type( root->rightmost_child, head );
            return head;
        }
        tree_node *temp = root->leftmost_child;
        while( temp ) {
            head = Bulid_type_exp_table( temp, head );
            temp = temp->sibling;
        }
    }
    return head;
}
/********************/

/********************/
void print_type_exp_table( linkedlist_node *head ) {
    linkedlist_node *curr = head;
    while( curr )
    {
        printf("%s\t", curr->var_name);
        type *p = curr->type_exp;
        // if it is not array
        if(p->tv==0)
        {
            tokenName h = integer ;
            tokenName q = real ;
            tokenName r = boolean ;
            if( p->texp.t == h )
            printf("integer");
            else if( p->texp.t == q )
            printf("real");
            else 
            printf("boolean");
        }
        // // if it is rect array
        else if(p->tv==1){
            printf("Rectangular Array\tdimension: %d\t",p->texp.rect.num_dimensions);
        }
        // // if it is jagged array
        else{
            printf("jagged Array\tdimension: %d\t",p->texp.jagged.num_dimensions);
        }
        printf("\n");
        curr = curr->next;
    }
    return;
}
/********************/

/********************/
type *search( linkedlist_node *head, char *var_name ) {
    linkedlist_node *temp = head;
    while( temp ) {
        if( strcmp( temp->var_name, var_name ) == 0 )
          return temp->type_exp;
    }
    return NULL;
}
/********************/

void printTypeExpressionTable(){
  FILE* sourceCode = fopen("sourcecode.txt","r");
    FILE* grammarRules = fopen("grammar.txt","r");

    parser_init();
    grammar_fill(grammarRules);     
    tree_node* x = parseInputSourceCode(sourceCode);    //,grammarRules
    // print_parse_tree(x);
    
    // printf(" in my code \n ");
    linkedlist_node *g = NULL;
    // printf("entering to build table\n" );
    // return;
    g = Bulid_type_exp_table( x, g);
    // printf("entering to printing table\n" );
    // return;
    print_type_exp_table(g);
    // return;
}