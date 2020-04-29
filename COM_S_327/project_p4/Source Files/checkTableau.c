#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "check.h"

extern int line;
extern char c;
extern int covered;
extern int uncovered;

int checkTableau(FILE *fp)
{
	char tableau[9];
	fgets(tableau, 9, fp);
	if (strcmp(tableau, "TABLEAU:") != 0)
	{
		fprintf(stderr, "Expected 'TABLEAU:' near line %d\n", line);
		return 0;
	}

	int r;
	int b;
	int s;

	int count = 0;

	parse(fp);
	int curline = line;

	node *previous;
	node *current;

	for (int i = 0; i < 7; i++)
	{
		count = 0;
		current = coveredTable[i];
		for (;;)
		{
			r = fgetc(fp);
			if (r == '|')
			{
				break;
			}
			s = fgetc(fp);
			if (checkCards(r, s) == 1)
			{
				if (current == NULL)
				{
					current = (node *)malloc(sizeof(node) * 1);
					current->rank = r;
					current->suit = s;
					previous = current;
					coveredTable[i] = current;
				}
				else
				{
					current = (node *)malloc(sizeof(node) * 1);
					current->rank = r;
					current->suit = s;
					previous->next = current;
					previous = current;
				}
				covered++;
			}
			else
			{
				return 0;
			}

			b = fgetc(fp);
			ungetc(b, fp);
			if (b != ' ')
			{
				fprintf(stderr, "Expected ' ' after card on line %d\n", line);
				return 0;
			}
			parse(fp);
		}

		b = fgetc(fp);
		ungetc(b, fp);

		if (b != ' ' && b != '\r' && b != '\n' && b != '\t')
		{
			fprintf(stderr, "1: ");
			fprintf(stderr, "Expecting ' ' after '|' near line %d\n", line);
			return 0;
		}

		current = uncoveredTable[i];
		for (;;)
		{
			parse(fp);
			if (line > curline)
			{
				curline = line;
				break;
			}
			r = fgetc(fp);
			s = fgetc(fp);
			if (checkCards(r, s) == 1)
			{
				if (current == NULL)
				{
					current = (node *)malloc(sizeof(node) * 1);
					current->rank = r;
					current->suit = s;
					previous = current;
					uncoveredTable[i] = current;
				}
				else
				{
					current = (node *)malloc(sizeof(node) * 1);
					current->rank = r;
					current->suit = s;
					previous->next = current;
					previous = current;
				}

				uncovered++;
			}
			else
			{
				return 0;
			}
			b = fgetc(fp);
			ungetc(b, fp);
			if (b != ' ' && b != '\r' && b != '\n' && b != '\t')
			{
				fprintf(stderr, "2: ");
				fprintf(stderr, "Expected ' ' after card on line %d\n", line);
				return 0;
			}
		}
	}

	// printf("TABLEAU: \n");
	// for(int i = 0; i < 7; i++) {
	// 	current = coveredTable[i];
	// 	while(current != NULL) {
	// 		printf("%c", current->rank);
	// 		printf("%c ", current->suit);
	// 		current = current->next;
	// 	}
	// 	printf("| ");
	// 	current = uncoveredTable[i];
	// 	while(current != NULL) {
	// 		printf("%c", current->rank);
	// 		printf("%c ", current->suit);
	// 		current = current->next;
	// 	}
	// 	printf("\n");
	// }

	return 1;
}