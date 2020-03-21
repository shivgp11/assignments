#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "parse.h"
#include "cards.h"

extern int line;
int validateMove(char* str);
int compareCards(node* card1, node* card2);
int compareSuit(char suitCard1, char suitCard2);
int compareRank(char rankCard1, char rankCard2);
int compareFoundationCards(node* card1, node* card2);
int compareFoundationRank(char rankCard1, char rankCard2);

int numMoves = 0;

int checkMoves(FILE* fp) {
	char src[] = {'1', '2', '3', '4', '5', '6', '7', 'w'};
	char dest[] = {'1', '2', '3', '4', '5', '6', '7', 'f'};
	int found = 0;
	char moves[7];
	char currentMove[4];
	
	char r;
	fgets(moves, 7, fp);
	if(strcmp(moves, "MOVES:") != 0) {
		fprintf(stderr, "Expected 'MOVES:' near line %d\n", line);
		return 0;
	}
	parse(fp);
	
	for(;;) {
		r = fgetc(fp);

		if(r == EOF){
			break;
		}

		if(r == '.'){
			parse(fp);
			numMoves++;
			continue;
		}

		if (r == 'r'){
			parse(fp);
			numMoves++;
			continue;
		}

		ungetc(r, fp);
		fgets(currentMove, 5, fp);

		for(int i = 0; i < sizeof(src); i++) {
			if (src[i] == currentMove[0]){
				found = 1;
				break;
			}
		}

		if(found == 0){
			fprintf(stderr, "Invalid move format in %d\n", line);
			return 0;
		} 

		found = 0;

		if(currentMove[1] != '-' || currentMove[2] != '>'){
			printf("Invalid move format in %d\n", line);
			return 0;
		} 

		for(int i = 0; i < sizeof(dest); i++) {
			if (dest[i] == currentMove[3]){
				found = 1;
				break;
			}
		}

		if(found == 0){
			fprintf(stderr, "Invalid move format in %d\n", line);
			return 0;
		} 
		
		numMoves++;
		if (validateMove(currentMove) == 0){
			fprintf(stderr, "Move %d is illegal: %s\n", numMoves, currentMove);
			return 0;
		}
		parse(fp);
	}
	
	printf("%d moves\n", numMoves);
    return 1;
}

int validateMove(char* str){
	int src = str[0] - '0';
	int dest = str[3] - '0';
	node* next = NULL;
	node* current = NULL;
	node* prev = NULL;
	node* end = NULL;
	if(str[0] == 'w' && str[3] == 'f'){
		if(wasteStack == NULL) {
			return 0;
		}
			
		if(wasteStack->rank == 'A') {
			if(wasteStack->suit == 'c') {
				current = wasteStack;
				next = current->next;
				current->next = NULL;
				clubsFoundation = current;
				wasteStack = next;	
				return 1;
			}
			else if(wasteStack->suit == 'd') {
				current = wasteStack;
				next = current->next;
				current->next = NULL;
				diamondsFoundation = current;
				wasteStack = next;
				return 1;
			}
			else if(wasteStack->suit == 'h') {
				current = wasteStack;
				next = current->next;
				current->next = NULL;
				heartsFoundation = current;
				wasteStack = next;
				return 1;
			}
			else {
				current = wasteStack;
				next = current->next;
				current->next = NULL;
				spadesFoundation = current;
				wasteStack = next;
				return 1;
			}
		}
		if(compareFoundationCards(wasteStack, clubsFoundation) == 1) {
			
			current = wasteStack;
			next = current->next;
			current->next = clubsFoundation;
			clubsFoundation = current;
			wasteStack = next;
		}
		else if(compareFoundationCards(wasteStack, diamondsFoundation) == 1) {
			current = wasteStack;
			next = current->next;
			current->next = diamondsFoundation;
			diamondsFoundation = current;
			wasteStack = next;
		}
		else if(compareFoundationCards(wasteStack, heartsFoundation) == 1) {
			current = wasteStack;
			next = current->next;
			current->next = heartsFoundation;
			heartsFoundation = current;
			wasteStack = next;
		}
		else if(compareFoundationCards(wasteStack, spadesFoundation) == 1) {
			current = wasteStack;
			next = current->next;
			current->next = spadesFoundation;
			spadesFoundation = current;
			wasteStack = next;
		}
		else {
			return 0;
		}
	} else if (str[0] == 'w' && (dest > 0 && dest < 8)){
		if(wasteStack == 0) {
			return 0;
		}
		if((wasteStack->rank) == 'K' && uncoveredTable[7 - dest] == NULL) {
			current = wasteStack;
			next = current->next;
			current->next = NULL;
			uncoveredTable[7 - dest] = current;
			wasteStack = next;
			return 1;
			
		}
		end = uncoveredTable[7 - dest];
		while(end->next != NULL) {
			end = end->next;
		}
		if(compareCards(wasteStack, end) == 1){
			current = wasteStack;
			next = current->next;
			current->next = NULL;
			wasteStack = next;
			end->next = current;
			
		} else {
			return 0;
		}
	} else if ((src > 0 && src < 8) && str[3] == 'f'){
		if(uncoveredTable[7 - src] == NULL) {
			return 0;
		}
		end = uncoveredTable[7 - src];
		while(end->next != NULL) {
			prev = end;
			end = end->next;
		}
		
		if(end->rank == 'A') {
			if(end->suit == 'c') {
				clubsFoundation = end;
			}
			else if(end->suit == 'd') {
				diamondsFoundation = end;
			}
			else if(end->suit == 'h') {
				heartsFoundation = end;
			}
			else {
				spadesFoundation = end;
			}
			
			if(coveredTable[7 - src] == NULL) {
				uncoveredTable[7 - src] = NULL;
				return 1;
			}
			else {
				end = coveredTable[7 - src];
				while(end->next != NULL) {
					prev = end;
					end = end->next;
				}
				uncoveredTable[7 - src] = end;
				if(prev == NULL) {
					coveredTable[7 - src] = NULL;
				}
				else {
					prev->next = NULL;
				}
				
			}
			return 1;
		}
		
		
		if(compareFoundationCards(end, clubsFoundation) == 1) {
			end->next = clubsFoundation;
			prev->next = NULL;
			clubsFoundation = end;
		}
		else if(compareFoundationCards(end, diamondsFoundation) == 1) {
			end->next = diamondsFoundation;
			prev->next = NULL;
			clubsFoundation = end;
		}
		else if(compareFoundationCards(end, heartsFoundation) == 1) {
			end->next = heartsFoundation;
			prev->next = NULL;
			clubsFoundation = end;
		}
		else if(compareFoundationCards(end, spadesFoundation) == 1) {
			end->next = spadesFoundation;
			prev->next = NULL;
			clubsFoundation = end;
		}
		else {
			return 0;
		}
	} else if ((src > 0 && src < 8) && (dest > 0 && dest < 8)){
		end = uncoveredTable[7 - dest];
		while(end->next != NULL) {
			prev = end;
			end = end->next;
		}
		if(compareCards(uncoveredTable[7 - src], end) == 1){
			current = uncoveredTable[7 - src];
			end->next = current;
			uncoveredTable[7 - dest] = NULL;	
			
		} else {
			return 0;
		}
	}
	return 1;
}

int compareCards(node* card1, node* card2){
	char rankCard1 = (card1->rank);
	char rankCard2 = (card2->rank);
	char suitCard1 = card1->suit;
	char suitCard2 = card2->suit;

	if((compareSuit(suitCard1, suitCard2) == 1) && (compareRank(rankCard1, rankCard2) == 1)){
		return 1;
	}
	return 0;
}

int compareFoundationCards(node* card1, node* card2){
	char rankCard1 = (card1->rank);
	char rankCard2 = (card2->rank);
	char suitCard1 = card1->suit;
	char suitCard2 = card2->suit;

	if (suitCard1 == 'h' && suitCard2 == 'h') {
		if (compareFoundationRank(rankCard1, rankCard2) == 1){
			return 1;
		}
	} else if (suitCard1 == 'c' && suitCard2 == 'c'){
		if (compareFoundationRank(rankCard1, rankCard2) == 1){
			return 1;
		}
	} else if (suitCard1 == 'd' && suitCard2 == 'd'){
		if (compareFoundationRank(rankCard1, rankCard2) == 1){
			return 1;
		}
	} else if (suitCard1 == 's' && suitCard2 == 's'){
		if (compareFoundationRank(rankCard1, rankCard2) == 1){
			return 1;
		}
	} 
	return 0; 
}

int compareSuit(char suitCard1, char suitCard2){
	if ((suitCard1 == 'h' && suitCard2 == 's') || (suitCard1 == 's' && suitCard2 == 'h')) {
		return 1;
	} else if ((suitCard1 == 'c' && suitCard2 == 'd') || (suitCard1 == 'd' && suitCard2 == 'c')) {
		return 1;
	} else if ((suitCard1 == 's' && suitCard2 == 'd') || (suitCard1 == 'd' && suitCard2 == 's')) {
		return 1;
	} else if ((suitCard1 == 'c' && suitCard2 == 'h') || (suitCard1 == 'h' && suitCard2 == 'c')) {
		return 1;
	} 
	return 0;
}

int compareRank(char rankCard1, char rankCard2){
	if((rankCard1 == 'Q' && rankCard2 == 'K') ||
	(rankCard1 == 'J' && rankCard2 == 'Q') ||
	(rankCard1 == 'T' && rankCard2 == 'J') ||
	(rankCard1 == '9' && rankCard2 == 'T') ||
	(rankCard1 == '8' && rankCard2 == '9') ||
	(rankCard1 == '7' && rankCard2 == '8') ||
	(rankCard1 == '6' && rankCard2 == '7') ||
	(rankCard1 == '5' && rankCard2 == '6') ||
	(rankCard1 == '4' && rankCard2 == '5') ||
	(rankCard1 == '3' && rankCard2 == '4') ||
	(rankCard1 == '2' && rankCard2 == '3') ||
	(rankCard1 == 'A' && rankCard2 == '2')){
		return 1;
	}
	return 0;
}

int compareFoundationRank(char rankCard1, char rankCard2){
	if((rankCard1 == 'K' && rankCard2 == 'Q') ||
	(rankCard1 == 'Q' && rankCard2 == 'J') ||
	(rankCard1 == 'J' && rankCard2 == 'T') ||
	(rankCard1 == 'T' && rankCard2 == '9') ||
	(rankCard1 == '9' && rankCard2 == '8') ||
	(rankCard1 == '8' && rankCard2 == '7') ||
	(rankCard1 == '7' && rankCard2 == '6') ||
	(rankCard1 == '6' && rankCard2 == '5') ||
	(rankCard1 == '5' && rankCard2 == '4') ||
	(rankCard1 == '4' && rankCard2 == '3') ||
	(rankCard1 == '3' && rankCard2 == '2') ||
	(rankCard1 == '2' && rankCard2 == 'A')){
		return 1;
	}
	return 0;
}