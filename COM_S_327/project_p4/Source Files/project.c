#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "check.h"

char ranks[] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
char suits[] = {'c', 'd', 'h', 's'};
int covered = 0;
int uncovered = 0;
int line = 1;
int stockC;
int wasteC;
int checkMovesIs2 = 0;
int found_limit = 0;

int c;
int turnNum = 0;
int numMoves = 0;
int limit = 99999;

int readMoves = 99999;
int found_m = 0;
int found_o = 0;
int found_x = 0;

int main(int argc, char *argv[])
{
	FILE *fp;
	FILE *writingFp;

	fp = stdin;

	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-m") == 0)
		{
			found_m = 1;
			if (atoi(argv[i + 1]) != 0)
			{
				i++;
				readMoves = atoi(argv[i]);
			}
		}
		else if (strcmp(argv[i], "-x") == 0)
		{
			found_x = 1;
		}
		else if (strcmp(argv[i], "-o") == 0)
		{
			found_o = 1;
			i++;
			writingFp = fopen(argv[i], "w+");
			if (writingFp == NULL)
			{
				printf("No such file\n");
			}
		}
		else
		{
			fp = fopen(argv[i], "r");
			if (fp == NULL)
			{
				printf("No such file\n");
			}
		}
	}

	parse(fp);
	if ((checkRules(fp) == 0))
	{
		return 0;
	}

	parse(fp);
	if ((checkFoundations(fp) == 0))
	{
		return 0;
	}

	parse(fp);
	if ((checkTableau(fp) == 0))
	{
		return 0;
	}

	parse(fp);
	if ((checkStock(fp) == 0))
	{
		return 0;
	}

	if ((checkMoves(fp) == 0))
	{
		return 0;
	}

	int cardLineSize = 0;
	int temp = 0;
	int k = 6;
	node *current;

	for (int i = 0; i < 7; i++)
	{
		current = coveredTable[i];
		while (current != NULL)
		{
			temp++;
			current = current->next;
		}

		current = uncoveredTable[i];
		while (current != NULL)
		{
			temp++;
			current = current->next;
		}
		if (temp > cardLineSize)
		{
			cardLineSize = temp;
		}
		temp = 0;
	}

	if (found_x == 1)
	{
		if (found_o == 1)
		{
			if (checkMovesIs2 == 0)
			{
				fprintf(stdout, "Processed %d moves, all valid\n", numMoves);
			}
			fprintf(writingFp, "RULES:\n");
			fprintf(writingFp, "  turn %d\n", turnNum);
			fprintf(writingFp, "  unlimited\n");
			fprintf(writingFp, "FOUNDATIONS:\n");
			if (clubsFoundation == NULL)
			{
				fprintf(writingFp, "_c \n");
			}
			else
			{
				fprintf(writingFp, "%c%c \n", clubsFoundation->rank, clubsFoundation->suit);
			}
			if (diamondsFoundation == NULL)
			{
				fprintf(writingFp, "_d \n");
			}
			else
			{
				fprintf(writingFp, "%c%c \n", diamondsFoundation->rank, diamondsFoundation->suit);
			}
			if (heartsFoundation == NULL)
			{
				fprintf(writingFp, "_h \n");
			}
			else
			{
				fprintf(writingFp, "%c%c \n", heartsFoundation->rank, heartsFoundation->suit);
			}
			if (spadesFoundation == NULL)
			{
				fprintf(writingFp, "_s \n");
			}
			else
			{
				fprintf(writingFp, "%c%c \n", spadesFoundation->rank, spadesFoundation->suit);
			}

			fprintf(writingFp, "TABLEAU:\n");
			for (int i = 0; i < 7; i++)
			{
				current = coveredTable[i];
				while (current != NULL)
				{
					fprintf(writingFp, "%c", current->rank);
					fprintf(writingFp, "%c ", current->suit);
					current = current->next;
				}
				fprintf(writingFp, "| ");
				current = uncoveredTable[i];
				while (current != NULL)
				{
					fprintf(writingFp, "%c", current->rank);
					fprintf(writingFp, "%c ", current->suit);
					current = current->next;
				}
				fprintf(writingFp, "\n");
			}
			fprintf(writingFp, "STOCK:\n");
			current = wasteStack;
			while (current != NULL)
			{
				fprintf(writingFp, "%c", current->rank);
				fprintf(writingFp, "%c ", current->suit);
				current = current->next;
			}
			fprintf(writingFp, "| ");
			current = stockStack;
			while (current != NULL)
			{
				fprintf(writingFp, "%c", current->rank);
				fprintf(writingFp, "%c ", current->suit);
				current = current->next;
			}
			fprintf(writingFp, "\n");
			fprintf(writingFp, "MOVES:\n");
			fclose(writingFp);
		}
		else
		{
			if (checkMovesIs2 == 0)
			{
				fprintf(stdout, "Processed %d moves, all valid\n", numMoves);
			}
			fprintf(stdout, "RULES:\n");
			fprintf(stdout, "  turn %d\n", turnNum);
			fprintf(stdout, "  unlimited\n");
			fprintf(stdout, "FOUNDATIONS:\n");
			if (clubsFoundation == NULL)
			{
				fprintf(stdout, "_c \n");
			}
			else
			{
				fprintf(stdout, "%c%c \n", clubsFoundation->rank, clubsFoundation->suit);
			}
			if (diamondsFoundation == NULL)
			{
				fprintf(stdout, "_d \n");
			}
			else
			{
				fprintf(stdout, "%c%c \n", diamondsFoundation->rank, diamondsFoundation->suit);
			}
			if (heartsFoundation == NULL)
			{
				fprintf(stdout, "_h \n");
			}
			else
			{
				fprintf(stdout, "%c%c \n", heartsFoundation->rank, heartsFoundation->suit);
			}
			if (spadesFoundation == NULL)
			{
				fprintf(stdout, "_s \n");
			}
			else
			{
				fprintf(stdout, "%c%c \n", spadesFoundation->rank, spadesFoundation->suit);
			}

			fprintf(stdout, "TABLEAU:\n");
			for (int i = 0; i < 7; i++)
			{
				current = coveredTable[i];
				while (current != NULL)
				{
					fprintf(stdout, "%c", current->rank);
					fprintf(stdout, "%c ", current->suit);
					current = current->next;
				}
				fprintf(stdout, "| ");
				current = uncoveredTable[i];
				while (current != NULL)
				{
					fprintf(stdout, "%c", current->rank);
					fprintf(stdout, "%c ", current->suit);
					current = current->next;
				}
				fprintf(stdout, "\n");
			}
			fprintf(stdout, "STOCK:\n");
			current = wasteStack;
			while (current != NULL)
			{
				fprintf(stdout, "%c", current->rank);
				fprintf(stdout, "%c ", current->suit);
				current = current->next;
			}
			fprintf(stdout, "| ");
			current = stockStack;
			while (current != NULL)
			{
				fprintf(stdout, "%c", current->rank);
				fprintf(stdout, "%c ", current->suit);
				current = current->next;
			}
			fprintf(stdout, "\n");
			fprintf(stdout, "MOVES:\n");
		}
	}
	else if (found_o == 1)
	{
		if (checkMovesIs2 == 0)
		{
			fprintf(stdout, "Processed %d moves, all valid\n", numMoves);
		}
		fprintf(writingFp, "Foundations\n");
		if (clubsFoundation == NULL)
		{
			fprintf(writingFp, "_c ");
		}
		else
		{
			fprintf(writingFp, "%c%c ", clubsFoundation->rank, clubsFoundation->suit);
		}
		if (diamondsFoundation == NULL)
		{
			fprintf(writingFp, "_d ");
		}
		else
		{
			fprintf(writingFp, "%c%c ", diamondsFoundation->rank, diamondsFoundation->suit);
		}
		if (heartsFoundation == NULL)
		{
			fprintf(writingFp, "_h ");
		}
		else
		{
			fprintf(writingFp, "%c%c ", heartsFoundation->rank, heartsFoundation->suit);
		}
		if (spadesFoundation == NULL)
		{
			fprintf(writingFp, "_s ");
		}
		else
		{
			fprintf(writingFp, "%c%c ", spadesFoundation->rank, spadesFoundation->suit);
		}
		fprintf(writingFp, "\n");

		fprintf(writingFp, "Tableau\n");
		for (int i = 0; i < cardLineSize; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				if (coveredTable[k] != NULL)
				{
					fprintf(writingFp, "## ");
					coveredTable[k] = coveredTable[k]->next;
				}
				else
				{
					if (uncoveredTable[k] != NULL)
					{
						fprintf(writingFp, "%c%c ", uncoveredTable[k]->rank, uncoveredTable[k]->suit);
						uncoveredTable[k] = uncoveredTable[k]->next;
					}
					else
					{
						fprintf(writingFp, ".. ");
					}
				}
				k--;
			}
			fprintf(writingFp, "\n");
			k = 6;
		}

		fprintf(writingFp, "Waste top\n");
		if (wasteStack == NULL)
		{
			fprintf(writingFp, "(empty)\n");
		}
		else
		{
			fprintf(writingFp, "%c%c\n", wasteStack->rank, wasteStack->suit);
		}

		fclose(writingFp);
	}
	else
	{
		if (checkMovesIs2 == 0)
		{
			fprintf(stdout, "Processed %d moves, all valid\n", numMoves);
		}
		fprintf(stdout, "Foundations\n");
		if (clubsFoundation == NULL)
		{
			fprintf(stdout, "_c ");
		}
		else
		{
			fprintf(stdout, "%c%c ", clubsFoundation->rank, clubsFoundation->suit);
		}
		if (diamondsFoundation == NULL)
		{
			fprintf(stdout, "_d ");
		}
		else
		{
			fprintf(stdout, "%c%c ", diamondsFoundation->rank, diamondsFoundation->suit);
		}
		if (heartsFoundation == NULL)
		{
			fprintf(stdout, "_h ");
		}
		else
		{
			fprintf(stdout, "%c%c ", heartsFoundation->rank, heartsFoundation->suit);
		}
		if (spadesFoundation == NULL)
		{
			fprintf(stdout, "_s ");
		}
		else
		{
			fprintf(stdout, "%c%c ", spadesFoundation->rank, spadesFoundation->suit);
		}
		fprintf(stdout, "\n");

		fprintf(stdout, "Tableau\n");

		for (int i = 0; i < cardLineSize; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				if (coveredTable[k] != NULL)
				{
					fprintf(stdout, "## ");
					coveredTable[k] = coveredTable[k]->next;
				}
				else
				{
					if (uncoveredTable[k] != NULL)
					{
						fprintf(stdout, "%c%c ", uncoveredTable[k]->rank, uncoveredTable[k]->suit);
						uncoveredTable[k] = uncoveredTable[k]->next;
					}
					else
					{
						fprintf(stdout, ".. ");
					}
				}
				k--;
			}
			fprintf(stdout, "\n");
			k = 6;
		}

		fprintf(stdout, "Waste top\n");
		if (wasteStack == NULL)
		{
			fprintf(stdout, "(empty)\n");
		}
		else
		{
			fprintf(stdout, "%c%c\n", wasteStack->rank, wasteStack->suit);
		}
	}

	fclose(fp);

	return 0;
}