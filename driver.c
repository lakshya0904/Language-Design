// Group no: 25
// Siddharth Jain: 2017B3A70551P
// Divya Tyagi: 2017B3A70727P
// Siva Sai Reddy: 2017B3A70779P
// Lakshya Agarwal: 2017B5A70904P
#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void populate_terminal_string() {

	FILE *file = fopen("tokens.txt", "r");
	fseek(file, 0, SEEK_END);
	int length = ftell(file);
	fseek(file, 0, SEEK_SET);
    // printf("terminal string length: %d\n",length);
	char *t_file = malloc(sizeof(char) * (length + 1));
	if (t_file == NULL) {
		perror("terminal_string filling failed\n");
		exit(1);
	}

	fread(t_file, sizeof(char), length, file);
	t_file[length] = '\0';
	fclose(file);

	char *tk_read = NULL;
	int i;
	tk_read = strtok(t_file, ", \n");

	for (i = 0; tk_read != NULL; i++) {
        // printf("Put T %s in tstring\n",tk_read);
		strncpy(terminal_string[i], tk_read, MAX_SYMBOL_LENGTH);
		tk_read = strtok(NULL, ", \n");
        //you need to put comma even after last enum in toikens.txt
	}

	free(t_file);
}

void populate_non_terminal_string() {
	FILE *file = fopen("nonTerminals.txt", "r");

	fseek(file, 0, SEEK_END);
	int length = ftell(file);
	fseek(file, 0, SEEK_SET);

	char *nt_file = malloc(sizeof(char) * (length + 1));

	if (nt_file == NULL) {
		//store_error(-1, INTERNAL_ERROR, "Parser init failed");
        perror("non_terminal_string filling failed\n");
		exit(1);
	}

	fread(nt_file, sizeof(char), length, file);
	nt_file[length] = '\0';
	fclose(file);

	char *nt_read = NULL;
	int i;
	nt_read = strtok(nt_file, ", \n");

	for (i = 0; nt_read != NULL; i++) {
        // printf("Put NT %s in ntstring\n",nt_read);
		strncpy(non_terminal_string[i], nt_read, MAX_SYMBOL_LENGTH);
		nt_read = strtok(NULL, ", \n");
	}
	free(nt_file);
}


int main(int argc, char * argv){
    FILE *fptr = fopen("grammar.txt", "r");

    // printf("hello ");
    if (fptr == NULL)
    {
        // perror("fopen");
        printf("error opening grammar.txt");
    }
    populate_terminal_string();
    populate_non_terminal_string();

    int choice;
    while(true){
        printf("\nSelect one choice from the given below choices:\n");
        printf("0 to exit\n");
        printf("1 to create parse tree\n");
        printf("2 to traverse the parse tree to construct typeExpressionTable\n");
        printf("3 to print the parse tree\n");
        printf("4 to print type expression table \n");
        scanf("%d", &choice);
		printf("\n");

        switch (choice)
        {
        case 0:
            return 0;
            break;

        case 1: //create parse tree
            createParseTree();
            printf("\n Parse tree created successfully!!");
            break;

        case 2: //traverse the parse tree to construct typeExpressionTable
            break;

        case 3: //traverse the parse tree in the specified format
            printParseTree();
            printf("\n Parse tree printed successfully!!");
            break;
        
        case 4: //print typeExpressionTable
            printTypeExpressionTable();
            printf("\n Type expression table printed successfully!!");
            break;

        default:
            break;
        }
    }


    return 0;
}
// printf("%p",grammar[3].front); is giving null,
// so any later access would give seg falut  // ACTUALLY, IT'S SET TO NUL ONLY IN THE CODE , in the beginning!!