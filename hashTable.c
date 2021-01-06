// Group no: 25
// Siddharth Jain: 2017B3A70551P
// Divya Tyagi: 2017B3A70727P
// Siva Sai Reddy: 2017B3A70779P
// Lakshya Agarwal: 2017B5A70904P

// #include "hashTable.h"
// #include "semantic_analyzerDef.h"
// #incl
#include "hashTableDef.h"   //ye shiva ne #include "hashTable.h" hata ke def include kiya h
#include<stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "driver.h"
int fastModExp(int a, int b, int m){
    int res=1;//A 
    while(b>0){
        if(b&1){
            res=(res*a)%m;
        }
        a=(a*a)%m;
        b>>=1;
    }
    
    
    return res;
}
int hash(char * string){
    int len=strlen(string);
    int hashValue=0;
    for(int i=0; i<len; ++i){
        hashValue+=(string[i]*fastModExp(PRIME,i,HASH_SIZE)%HASH_SIZE);//need to check value and location of PRIME and HASH_SIZE
    }

    return hashValue%HASH_SIZE;
}

void initialiseHashTable(HashTable ht){
    if (ht==NULL)
    {
        perror("Hash ht allocation error: memory not available\n");
		exit(1);
    }
    for(int i=0; i<HASH_SIZE; ++i){
        ht[i].present=false;    // @ time of initalisation(before insertung), no key is present 
        ht[i].value=NULL;
    }

}
// 
void hashInsert(HashTable ht, char * lexeme, int val){
    int hashValue;
    hashValue=hash(lexeme);
    // 
    int probeNum=1;
    while(ht[hashValue].present==true){ // till yoou aer able to find a location 
        // incase of collision, do quadratic probing & go to next location(hash value )
        if(strcmp(lexeme, ht[hashValue].lexeme)==0)
            break;
        hashValue=(hashValue+probeNum*probeNum)%HASH_SIZE;
        probeNum++;
    }
    strncpy(ht[hashValue].lexeme,lexeme,MAX_LEXEME_LEN);
    ht[hashValue].present=true;
    ht[hashValue].value=malloc(sizeof(int));//malloc function returns void * only, np
    *(int*)(ht[hashValue].value)=val;// assign map from key(lexeme) to value(val)
    
}
 

int searchHashTable(HashTable ht, char *lexeme) {
	int hashValue = hash(lexeme);
	int probeNum = 1;
    // printf("lexeme in Search hash table => %s \n",lexeme);
	while (ht[hashValue].present == true) 
	{   //printf("hashtable's present is true");
		if (strcmp(ht[hashValue].lexeme, lexeme) == 0) 
		{
			return *(int*)(ht[hashValue].value);
		}
		hashValue = (hashValue + probeNum * probeNum) % HASH_SIZE;
		probeNum++;
	}
	return KEY_NOT_FOUND;
}

