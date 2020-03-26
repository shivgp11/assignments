#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "check.h"
#include "cards.h"

int validateMove(char *str);
int compareCards(node *card1, node *card2);
int compareSuit(char suitCard1, char suitCard2);
int compareRank(char rankCard1, char rankCard2);
int compareFoundationCards(node *card1, node *card2);
int compareFoundationRank(char rankCard1, char rankCard2);
int validateDot();
int reset();

extern int numMoves;
extern int line;
extern int readMoves;
extern int turnNum;
extern int limit;
extern int checkMovesIs2;

int checkMoves(FILE *fp)
{
	char src[] = {'1', '2', '3', '4', '5', '6', '7', 'w'};
	char dest[] = {'1', '2', '3', '4', '5', '6', '7', 'f'};
	int found = 0;
	int currentResets = 0;
	char moves[7];
	char currentMove[4];

	char r;
	fgets(moves, 7, fp);
	if (strcmp(moves, "MOVES:") != 0)
	{
		fprintf(stderr, "Expected 'MOVES:' near line %d\n", line);
		return 0;
	}
	parse(fp);

	while (numMoves <= readMoves - 1)
	{
		r = fgetc(fp);

		if (r == EOF)
		{
			break;
		}

		if (r == '.')
		{
			numMoves++;
			if (validateDot() == 0)
			{
				fprintf(stderr, "Move %d is illegal: %c\n", numMoves, r);
				return 0;
			}
			parse(fp);
			continue;
		}

		if (r == 'r')
		{
			currentResets++;
			numMoves++;
			if (currentResets > limit)
			{
				fprintf(stderr, "Move %d is illegal: %c\n", numMoves, r);
				return 0;
			}
			else
			{
				if (reset() == 0)
				{
					fprintf(stderr, "Move %d is illegal: %c\n", numMoves, r);
					return 0;
				}
			}
			parse(fp);
			continue;
		}

		ungetc(r, fp);
		fgets(currentMove, 5, fp);

		for (int i = 0; i < sizeof(src); i++)
		{
			if (src[i] == currentMove[0])
			{
				found = 1;
				break;
			}
		}

		if (found == 0)
		{
			fprintf(stderr, "Invalid move format in %d\n", line);
			return 0;
		}

		found = 0;

		if (currentMove[1] != '-' || currentMove[2] != '>')
		{
			fprintf(stderr, "Invalid move format in %d\n", line);
			return 0;
		}

		for (int i = 0; i < sizeof(dest); i++)
		{
			if (dest[i] == currentMove[3])
			{
				found = 1;
				break;
			}
		}

		if (found == 0)
		{
			fprintf(stderr, "Invalid move format in %d\n", line);
			return 0;
		}

		numMoves++;
		if (validateMove(currentMove) == 0)
		{
			fprintf(stderr, "Move %d is illegal: %s\n", numMoves, currentMove);
			checkMovesIs2 = 1;
			return 1;
		}
		parse(fp);
	}
	return 1;
}

int reset()
{
	if (stockStack != NULL)
	{
		return 0;
	}
	node *current = wasteStack;
	node *previous = NULL;
	node *next = NULL;
	while (current != NULL)
	{
		next = current->next;
		current->next = previous;
		previous = current;
		current = next;
	}
	wasteStack = previous;
	stockStack = wasteStack;
	fprintf(stdout, "stack is %c%c\n", stockStack->rank, stockStack->suit);
	wasteStack = NULL;

	return 1;
}

int validateDot()
{
	if (stockStack == NULL)
	{
		return 0;
	}
	node *current = NULL;
	node *next = NULL;
	for (int i = 0; i < turnNum; i++)
	{
		if (wasteStack == NULL)
		{
			current = stockStack;
			next = current->next;
			current->next = NULL;
			wasteStack = current;
			stockStack = next;
		}
		else
		{
			current = stockStack;
			next = current->next;
			current->next = wasteStack;
			wasteStack = current;
			stockStack = next;
		}
		if (stockStack == NULL)
		{
			break;
		}
	}
	//fprintf(stdout, "stack is %c%c\n", stockStack->rank,  stockStack->suit);
	return 1;
}

int validateMove(char *str)
{
	int src = str[0] - '0';
	int dest = str[3] - '0';
	node *next = NULL;
	node *current = NULL;
	node *prev = NULL;
	node *end = NULL;
	if (str[0] == 'w' && str[3] == 'f')
	{
		if (wasteStack == NULL)
		{
			return 0;
		}
		if (wasteStack->rank == 'A')
		{
			if (wasteStack->suit == 'c')
			{
				// printf("clubs\n");
				// printf("start\n");
				current = wasteStack;
				next = current->next;
				current->next = NULL;
				clubsFoundation = current;
				wasteStack = next;
				//printf("finish\n");
			}
			else if (wasteStack->suit == 'd')
			{
				// printf("diamonds\n");
				// printf("start\n");
				current = wasteStack;
				next = current->next;
				current->next = NULL;
				diamondsFoundation = current;
				wasteStack = next;
				//printf("finish\n");
			}
			else if (wasteStack->suit == 'h')
			{
				// printf("hearts\n");
				// printf("start\n");
				current = wasteStack;
				next = current->next;
				current->next = NULL;
				heartsFoundation = current;
				wasteStack = next;
				//printf("finish\n");
			}
			else if (wasteStack->suit == 's')
			{
				// printf("spades\n");
				// printf("start\n");
				current = wasteStack;
				next = current->next;
				current->next = NULL;
				spadesFoundation = current;
				wasteStack = next;
				//printf("finish\n");
			}
		}
		else if (compareFoundationCards(wasteStack, clubsFoundation) == 1)
		{
			// printf("clubs\n");
			// printf("start\n");
			current = wasteStack;
			next = current->next;
			current->next = clubsFoundation;
			clubsFoundation = current;
			wasteStack = next;
			//printf("finish\n");
		}
		else if (compareFoundationCards(wasteStack, diamondsFoundation) == 1)
		{
			// printf("diamonds\n");
			// printf("start\n");
			current = wasteStack;
			next = current->next;
			current->next = diamondsFoundation;
			diamondsFoundation = current;
			wasteStack = next;
			//printf("finish\n");
		}
		else if (compareFoundationCards(wasteStack, heartsFoundation) == 1)
		{
			// printf("heart\n");
			// printf("start\n");
			current = wasteStack;
			next = current->next;
			current->next = heartsFoundation;
			heartsFoundation = current;
			wasteStack = next;
			//printf("finish\n");
		}
		else if (compareFoundationCards(wasteStack, spadesFoundation) == 1)
		{
			// printf("spades\n");
			// printf("start\n");
			current = wasteStack;
			next = current->next;
			current->next = spadesFoundation;
			spadesFoundation = current;
			wasteStack = next;
			//printf("finish\n");
		}
		else
		{
			return 0;
		}
	}
	else if (str[0] == 'w' && (dest > 0 && dest < 8))
	{
		if (wasteStack == 0)
		{
			return 0;
		}
		if ((wasteStack->rank) == 'K' && uncoveredTable[7 - dest] == NULL)
		{
			current = wasteStack;
			next = current->next;
			current->next = NULL;
			uncoveredTable[7 - dest] = current;
			wasteStack = next;
			return 1;
		}
		else if ((wasteStack->rank) != 'K' && uncoveredTable[7 - dest] == NULL)
		{
			return 0;
		}

		end = uncoveredTable[7 - dest];
		while (end->next != NULL)
		{
			end = end->next;
		}
		if (compareCards(wasteStack, end) == 1)
		{
			current = wasteStack;
			next = current->next;
			end->next = current;
			current->next = NULL;
			wasteStack = next;
		}
		else
		{
			return 0;
		}
	}
	else if ((src > 0 && src < 8) && str[3] == 'f')
	{
		if (uncoveredTable[7 - src] == NULL)
		{
			return 0;
		}
		end = uncoveredTable[7 - src];
		while (end->next != NULL)
		{
			prev = end;
			end = end->next;
		}

		if (end->rank == 'A')
		{
			if (end->suit == 'c')
			{
				clubsFoundation = end;
			}
			else if (end->suit == 'd')
			{
				diamondsFoundation = end;
			}
			else if (end->suit == 'h')
			{
				heartsFoundation = end;
			}
			else if (end->suit == 's')
			{
				spadesFoundation = end;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			if (compareFoundationCards(end, clubsFoundation) == 1)
			{
				end->next = clubsFoundation;
				clubsFoundation = end;
			}
			else if (compareFoundationCards(end, diamondsFoundation) == 1)
			{
				end->next = diamondsFoundation;
				diamondsFoundation = end;
			}
			else if (compareFoundationCards(end, heartsFoundation) == 1)
			{
				end->next = heartsFoundation;
				heartsFoundation = end;
			}
			else if (compareFoundationCards(end, spadesFoundation) == 1)
			{
				end->next = spadesFoundation;
				spadesFoundation = end;
			}
			else
			{
				return 0;
			}
		}
		if (prev != NULL)
		{
			prev->next = NULL;
			return 1;
		}
		if (coveredTable[7 - src] == NULL)
		{
			uncoveredTable[7 - src] = NULL;
			return 1;
		}
		else
		{
			end = coveredTable[7 - src];
			while (end->next != NULL)
			{
				prev = end;
				end = end->next;
			}
			uncoveredTable[7 - src] = end;
			if (prev == NULL)
			{
				coveredTable[7 - src] = NULL;
			}
			else
			{
				prev->next = NULL;
			}
		}

		return 1;
	}
	else if ((src > 0 && src < 8) && (dest > 0 && dest < 8))
	{
		//printf("here\n");
		end = uncoveredTable[7 - dest];

		if (end == NULL && (uncoveredTable[7 - src]->rank) == 'K')
		{
			current = uncoveredTable[7 - src];
			uncoveredTable[7 - dest] = current;
		}
		else if (end == NULL && (uncoveredTable[7 - src]->rank) != 'K')
		{
			return 0;
		}
		else
		{
			while (end->next != NULL)
			{
				prev = end;
				end = end->next;
			}
			//printf("%c%c\n", end->rank, end->suit);
			if (compareCards(uncoveredTable[7 - src], end) == 1)
			{
				current = uncoveredTable[7 - src];
				end->next = current;
				//printf("%c%c\n", current->rank, current->suit);
			}
			else
			{
				return 0;
			}
		}

		if (coveredTable[7 - src] == NULL)
		{
			uncoveredTable[7 - src] = NULL;
			current = uncoveredTable[7 - dest];
		}
		else
		{
			end = coveredTable[7 - src];
			prev = NULL;
			while (end->next != NULL)
			{
				prev = end;
				end = end->next;
			}
			//printf("%c%c\n", end->rank, end->suit);
			uncoveredTable[7 - src] = end;
			//printf("%p\n", prev);
			//printf("hi\n");
			if (prev == NULL)
			{

				coveredTable[7 - src] = NULL;
			}
			else
			{
				//printf("%c%c\n", prev->rank, prev->suit);
				prev->next = NULL;
			}
		}
	}
	return 1;
}

int compareCards(node *card1, node *card2)
{
	char rankCard1 = (card1->rank);
	char rankCard2 = (card2->rank);
	char suitCard1 = card1->suit;
	char suitCard2 = card2->suit;

	if ((compareSuit(suitCard1, suitCard2) == 1) && (compareRank(rankCard1, rankCard2) == 1))
	{
		return 1;
	}
	return 0;
}

int compareSuit(char suitCard1, char suitCard2)
{
	if ((suitCard1 == 'h' && suitCard2 == 's') || (suitCard1 == 's' && suitCard2 == 'h'))
	{
		return 1;
	}
	else if ((suitCard1 == 'c' && suitCard2 == 'd') || (suitCard1 == 'd' && suitCard2 == 'c'))
	{
		return 1;
	}
	else if ((suitCard1 == 's' && suitCard2 == 'd') || (suitCard1 == 'd' && suitCard2 == 's'))
	{
		return 1;
	}
	else if ((suitCard1 == 'c' && suitCard2 == 'h') || (suitCard1 == 'h' && suitCard2 == 'c'))
	{
		return 1;
	}
	return 0;
}

int compareRank(char rankCard1, char rankCard2)
{
	if ((rankCard1 == 'Q' && rankCard2 == 'K') ||
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
		(rankCard1 == 'A' && rankCard2 == '2'))
	{
		return 1;
	}
	return 0;
}

int compareFoundationCards(node *card1, node *card2)
{
	if (card2 == NULL)
	{
		return 0;
	}
	char rankCard1 = (card1->rank);
	//printf("(1)\n");
	char rankCard2 = (card2->rank);
	//printf("(2)\n");
	char suitCard1 = card1->suit;
	//printf("(3)\n");
	char suitCard2 = card2->suit;
	// printf("(4)\n");
	// printf("%c\n", rankCard1);
	// printf("%c\n", suitCard1);
	// printf("%c\n", rankCard2);
	// printf("%c\n", suitCard2);
	if (suitCard1 == 'h' && suitCard2 == 'h')
	{
		//printf("(5)\n");
		if (compareFoundationRank(rankCard1, rankCard2) == 1)
		{
			//printf("(6)\n");
			return 1;
		}
	}
	else if (suitCard1 == 'c' && suitCard2 == 'c')
	{
		//printf("(5)\n");
		if (compareFoundationRank(rankCard1, rankCard2) == 1)
		{
			//printf("(6)\n");
			return 1;
		}
	}
	else if (suitCard1 == 'd' && suitCard2 == 'd')
	{
		//printf("(5)\n");
		if (compareFoundationRank(rankCard1, rankCard2) == 1)
		{
			//printf("(6)\n");
			return 1;
		}
	}
	else if (suitCard1 == 's' && suitCard2 == 's')
	{
		//printf("(5)\n");
		if (compareFoundationRank(rankCard1, rankCard2) == 1)
		{
			//printf("(6)\n");
			return 1;
		}
	}
	//printf("bad\n");
	return 0;
}

int compareFoundationRank(char rankCard1, char rankCard2)
{
	if ((rankCard1 == 'K' && rankCard2 == 'Q') ||
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
		(rankCard1 == '2' && rankCard2 == 'A'))
	{
		return 1;
	}
	return 0;
}