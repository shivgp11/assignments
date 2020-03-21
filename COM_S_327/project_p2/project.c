#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parse.h"
#include "checkRules.h"
#include "checkFoundations.h"
#include "checkTableau.h"
#include "checkStock.h"
#include "checkMoves.h"


char ranks[] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
char suits[]  = {'c', 'd', 'h', 's'};
int covered = 0;
int uncovered = 0;
int line = 1;
int stockC;
int wasteC;

int c;
int main(int argc, char* argv[]){
    FILE* fp; 
	
	if(argc > 1){
		fp = fopen(argv[1],"r"); 
		if (fp == NULL) 
    	{ 
       		printf("No such file\n");
    	} 
	} else {
		fp = stdin;
	}
    
    char str[1000];

    parse(fp);
    if((checkRules(fp) == 0) ) {
		return 0;
	}

	parse(fp);
	if((checkFoundations(fp) == 0) ) {
		return 0;
	}

	parse(fp);
	if((checkTableau(fp) == 0) ) {
		return 0;
	}
	
	parse(fp);
	if((checkStock(fp) == 0) ) {
		return 0;
	}

	
	if((checkMoves(fp) == 0) ) {
		return 0;
	}

	printf("Input file is valid\n");
	printf("%d covered cards\n", covered);
	printf("%d stock cards\n", stockC);
	printf("%d waste cards\n", wasteC);
    
	fclose(fp);  
    
    return 0;
}