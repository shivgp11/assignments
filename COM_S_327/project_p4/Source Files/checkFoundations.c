#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "check.h"
#include <stdlib.h>

extern int line;
extern char c;

int checkFoundations(FILE *fp)
{
	char ranks[] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
	char foundations[13];
	fgets(foundations, 13, fp);
	if (strcmp(foundations, "FOUNDATIONS:") != 0)
	{
		fprintf(stderr, "Expected 'FOUNDATIONS:' near line %d\n", line);
		return 0;
	}

	parse(fp);
	char clubs[2];
	fgets(clubs, 3, fp);
	if (clubs[1] != 'c')
	{
		fprintf(stderr, "Expected clubs foundation' near line %d\n", line);
		return 0;
	}

	if (clubs[0] != '_')
	{
		int found = 0;
		for (int i = 0; i < sizeof(ranks); i++)
		{
			if (ranks[i] == clubs[0])
			{
				found = 1;
				break;
			}
		}
		if (found == 0)
		{
			fprintf(stderr, "Invalid Rank near line %d\n", line);
			return 0;
		}
	}

	node *current = clubsFoundation;
	node *previous;
	char z;
	int count = 0;

	if (clubs[0] != '_')
	{
		z = clubs[0];
		while (z != ranks[count])
		{
			count++;
		}
		for (int i = count; i >= 0; i--)
		{
			if (current == NULL)
			{
				current = (node *)malloc(sizeof(node) * 1);
				current->rank = ranks[i];
				current->suit = 'c';
				clubsFoundation = current;
				previous = current;
			}
			else
			{
				current = (node *)malloc(sizeof(node) * 1);
				current->rank = ranks[i];
				current->suit = 'c';
				previous->next = current;
				previous = current;
			}
		}
	}

	parse(fp);
	char diamonds[2];
	fgets(diamonds, 3, fp);
	if (diamonds[1] != 'd')
	{
		fprintf(stderr, "Expected 'diamonds foundation' near line %d\n", line);
		return 0;
	}

	if (diamonds[0] != '_')
	{
		int found = 0;
		for (int i = 0; i < sizeof(ranks); i++)
		{
			if (ranks[i] == diamonds[0])
			{
				found = 1;
				break;
			}
		}
		if (found == 0)
		{
			fprintf(stderr, "Invalid Rank near line %d\n", line);
			return 0;
		}
	}

	current = diamondsFoundation;
	count = 0;
	if (diamonds[0] != '_')
	{
		z = diamonds[0];
		while (z != ranks[count])
		{
			count++;
		}
		for (int i = count; i >= 0; i--)
		{
			if (current == NULL)
			{
				current = (node *)malloc(sizeof(node) * 1);
				current->rank = ranks[i];
				current->suit = 'd';
				diamondsFoundation = current;
				previous = current;
			}
			else
			{
				current = (node *)malloc(sizeof(node) * 1);
				current->rank = ranks[i];
				current->suit = 'd';
				previous->next = current;
				previous = current;
			}
		}
	}

	parse(fp);
	char hearts[2];
	fgets(hearts, 3, fp);
	if (hearts[1] != 'h')
	{
		fprintf(stderr, "Expected 'hearts foundation' near line %d\n", line);
		return 0;
	}

	if (hearts[0] != '_')
	{
		int found = 0;
		for (int i = 0; i < sizeof(ranks); i++)
		{
			if (ranks[i] == hearts[0])
			{
				found = 1;
				break;
			}
		}
		if (found == 0)
		{
			fprintf(stderr, "Invalid Rank near line %d\n", line);
			return 0;
		}
	}

	current = heartsFoundation;
	count = 0;
	if (hearts[0] != '_')
	{
		z = hearts[0];
		while (z != ranks[count])
		{
			count++;
		}
		for (int i = count; i >= 0; i--)
		{
			if (current == NULL)
			{
				current = (node *)malloc(sizeof(node) * 1);
				current->rank = ranks[i];
				current->suit = 'h';
				heartsFoundation = current;
				previous = current;
			}
			else
			{
				current = (node *)malloc(sizeof(node) * 1);
				current->rank = ranks[i];
				current->suit = 'h';
				previous->next = current;
				previous = current;
			}
		}
	}

	parse(fp);
	char spades[2];
	fgets(spades, 3, fp);
	if (spades[1] != 's')
	{
		fprintf(stderr, "Expected 'spades foundation' near line %d\n", line);
		return 0;
	}

	if (spades[0] != '_')
	{
		int found = 0;
		for (int i = 0; i < sizeof(ranks); i++)
		{
			if (ranks[i] == spades[0])
			{
				found = 1;
				break;
			}
		}
		if (found == 0)
		{
			fprintf(stderr, "Invalid Rank near line %d\n", line);
			return 0;
		}
	}

	current = spadesFoundation;
	count = 0;
	if (spades[0] != '_')
	{
		z = spades[0];
		while (z != ranks[count])
		{
			count++;
		}
		for (int i = count; i >= 0; i--)
		{
			if (current == NULL)
			{
				current = (node *)malloc(sizeof(node) * 1);
				current->rank = ranks[i];
				current->suit = 's';
				spadesFoundation = current;
				previous = current;
			}
			else
			{
				current = (node *)malloc(sizeof(node) * 1);
				current->rank = ranks[i];
				current->suit = 's';
				previous->next = current;
				previous = current;
			}
		}
	}

	// printf("FOUNDATIONS:\n");

	// current = clubsFoundation;
	// while(current != NULL) {
	// 	printf("%c", current->rank);
	// 	printf("%c ", current->suit);
	// 	current = current->next;

	// }
	// printf("\n");

	// current = diamondsFoundation;
	// while(current != NULL) {
	// 	printf("%c", current->rank);
	// 	printf("%c ", current->suit);
	// 	current = current->next;
	// }
	// printf("\n");

	// current = heartsFoundation;
	// while(current != NULL) {
	// 	printf("%c", current->rank);
	// 	printf("%c ", current->suit);
	// 	current = current->next;
	// }
	// printf("\n");

	// current = spadesFoundation;
	// while(current != NULL) {
	// 	printf("%c", current->rank);
	// 	printf("%c ", current->suit);
	// 	current = current->next;
	// }
	// printf("\n");
	return 1;
}