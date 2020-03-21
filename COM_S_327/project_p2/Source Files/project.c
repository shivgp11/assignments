#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cards.h"
#include "check.h"

char ranks[] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
char suits[] = {'c', 'd', 'h', 's'};
int covered = 0;
int uncovered = 0;
int line = 1;
int stockC;
int wasteC;

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

	char str[1000];

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

	if (found_x == 1)
	{
		if (found_o == 1)
		{
			fprintf(writingFp, "RULES:\n");
			fprintf(writingFp, "  turn %d\n", turnNum);
			fprintf(writingFp, "  unlimited\n");
			fprintf(writingFp, "FOUNDATIONS:\n");
			// fprintf(writingFp, "  %c%c\n", clubsFoundation->rank, clubsFoundation->suit);
			// fprintf(writingFp, "  %c%c\n", diamondsFoundation->rank, diamondsFoundation->suit);
			// fprintf(writingFp, "  %c%c\n", heartsFoundation->rank, heartsFoundation->suit);
			// fprintf(writingFp, "  %c%c\n", spadesFoundation->rank, spadesFoundation->suit);
			fprintf(writingFp, "TABLEAU:\n");
			fprintf(writingFp, "STOCK:\n");
			fprintf(writingFp, "MOVES:\n");
			fclose(writingFp);
		}
		else
		{
			fprintf(stdout, "RULES:\n");
			fprintf(stdout, "  turn %d\n", turnNum);
			fprintf(stdout, "  unlimited\n");
			fprintf(stdout, "FOUNDATIONS:\n");
			// fprintf(stdout, "  %c%c\n", clubsFoundation->rank, clubsFoundation->suit);
			// fprintf(stdout, "  %c%c\n", diamondsFoundation->rank, diamondsFoundation->suit);
			// fprintf(stdout, "  %c%c\n", heartsFoundation->rank, heartsFoundation->suit);
			// fprintf(stdout, "  %c%c\n", spadesFoundation->rank, spadesFoundation->suit);
			fprintf(stdout, "TABLEAU:\n");
			fprintf(stdout, "STOCK:\n");
			fprintf(stdout, "MOVES:\n");
		}
	}
	else if (found_o == 1)
	{
		fprintf(writingFp, "Processed %d moves, all valid\n", numMoves);
		fprintf(writingFp, "Foundations\n");
		// fprintf(writingFp, "%c%c %c%c %c%c %c%c\n", clubsFoundation->rank, clubsFoundation->suit,
		// 	diamondsFoundation->rank, diamondsFoundation->suit, heartsFoundation->rank, heartsFoundation->suit,
		// 	spadesFoundation->rank, spadesFoundation->suit);
		fprintf(writingFp, "Tableau\n");
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
		fprintf(stdout, "Processed %d moves, all valid\n", numMoves);
		fprintf(stdout, "Foundations\n");
		fprintf(stdout, "%c%c %c%c %c%c %c%c\n", clubsFoundation->rank, clubsFoundation->suit,
			diamondsFoundation->rank, diamondsFoundation->suit, heartsFoundation->rank, heartsFoundation->suit,
			spadesFoundation->rank, spadesFoundation->suit);
		fprintf(stdout, "Tableau\n");
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