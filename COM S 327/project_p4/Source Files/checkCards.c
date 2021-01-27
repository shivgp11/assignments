#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "check.h"

extern int line;

int checkCards(char rank, char suit)
{
	char ranks[] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
	char suits[] = {'c', 'd', 'h', 's'};
	int cardsVaild = 0;
	for (int i = 0; i < sizeof(ranks); i++)
	{
		if (ranks[i] == rank)
		{
			cardsVaild++;
			break;
		}
	}

	for (int i = 0; i < sizeof(suits); i++)
	{
		if (suits[i] == suit)
		{
			cardsVaild++;
			break;
		}
	}

	if (cardsVaild == 2)
	{
		return 1;
	}

	fprintf(stderr, "Invalid card near line %d\n", line);
	return 0;
}
