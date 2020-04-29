#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "compare.h"

extern int turnNum;
extern int found_f;

char ranksArr[] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};

int reset()
{
	if (stockStackCopy != NULL)
	{
		return 0;
	}
	node *current = wasteStackCopy;
	node *previous = NULL;
	node *next = NULL;
	while (current != NULL)
	{
		next = current->next;
		current->next = previous;
		previous = current;
		current = next;
	}
	wasteStackCopy = previous;
	stockStackCopy = wasteStackCopy;
	fprintf(stdout, "stack is %c%c\n", stockStackCopy->rank, stockStackCopy->suit);
	wasteStackCopy = NULL;

	return 1;
}

int validateDot()
{
	if (stockStackCopy == NULL)
	{
		return 0;
	}
	node *current = NULL;
	node *next = NULL;
	for (int i = 0; i < turnNum; i++)
	{
		if (wasteStackCopy == NULL)
		{
			current = stockStackCopy;
			next = current->next;
			current->next = NULL;
			wasteStackCopy = current;
			stockStackCopy = next;
		}
		else
		{
			current = stockStackCopy;
			next = current->next;
			current->next = wasteStackCopy;
			wasteStackCopy = current;
			stockStackCopy = next;
		}
		if (stockStackCopy == NULL)
		{
			break;
		}
	}
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
		if (wasteStackCopy == NULL)
		{
			return 0;
		}
		if (wasteStackCopy->rank == 'A')
		{
			if (wasteStackCopy->suit == 'c')
			{
				current = wasteStackCopy;
				next = current->next;
				current->next = NULL;
				clubsFoundationCopy = current;
				wasteStackCopy = next;
			}
			else if (wasteStackCopy->suit == 'd')
			{
				current = wasteStackCopy;
				next = current->next;
				current->next = NULL;
				diamondsFoundationCopy = current;
				wasteStackCopy = next;
			}
			else if (wasteStackCopy->suit == 'h')
			{
				current = wasteStackCopy;
				next = current->next;
				current->next = NULL;
				heartsFoundationCopy = current;
				wasteStackCopy = next;
			}
			else if (wasteStackCopy->suit == 's')
			{
				current = wasteStackCopy;
				next = current->next;
				current->next = NULL;
				spadesFoundationCopy = current;
				wasteStackCopy = next;
			}
		}
		else if (compareFoundationCards(wasteStackCopy, clubsFoundationCopy) == 1)
		{
			current = wasteStackCopy;
			next = current->next;
			current->next = clubsFoundationCopy;
			clubsFoundationCopy = current;
			wasteStackCopy = next;
		}
		else if (compareFoundationCards(wasteStackCopy, diamondsFoundationCopy) == 1)
		{
			current = wasteStackCopy;
			next = current->next;
			current->next = diamondsFoundationCopy;
			diamondsFoundationCopy = current;
			wasteStackCopy = next;
		}
		else if (compareFoundationCards(wasteStackCopy, heartsFoundationCopy) == 1)
		{
			current = wasteStackCopy;
			next = current->next;
			current->next = heartsFoundationCopy;
			heartsFoundationCopy = current;
			wasteStackCopy = next;
		}
		else if (compareFoundationCards(wasteStackCopy, spadesFoundationCopy) == 1)
		{
			current = wasteStackCopy;
			next = current->next;
			current->next = spadesFoundationCopy;
			spadesFoundationCopy = current;
			wasteStackCopy = next;
		}
		else
		{
			return 0;
		}
	}
	else if (str[0] == 'w' && (dest > 0 && dest < 8))
	{
		if (wasteStackCopy == 0)
		{
			return 0;
		}
		if ((wasteStackCopy->rank) == 'K' && uncoveredTable[7 - dest] == NULL)
		{
			current = wasteStackCopy;
			next = current->next;
			current->next = NULL;
			uncoveredTable[7 - dest] = current;
			wasteStackCopy = next;
			return 1;
		}
		else if ((wasteStackCopy->rank) != 'K' && uncoveredTable[7 - dest] == NULL)
		{
			return 0;
		}

		end = uncoveredTable[7 - dest];
		while (end->next != NULL)
		{
			end = end->next;
		}
		if (compareCards(wasteStackCopy, end) == 1)
		{
			current = wasteStackCopy;
			next = current->next;
			end->next = current;
			current->next = NULL;
			wasteStackCopy = next;
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
				clubsFoundationCopy = end;
			}
			else if (end->suit == 'd')
			{
				diamondsFoundationCopy = end;
			}
			else if (end->suit == 'h')
			{
				heartsFoundationCopy = end;
			}
			else if (end->suit == 's')
			{
				spadesFoundationCopy = end;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			if (compareFoundationCards(end, clubsFoundationCopy) == 1)
			{
				end->next = clubsFoundationCopy;
				clubsFoundationCopy = end;
			}
			else if (compareFoundationCards(end, diamondsFoundationCopy) == 1)
			{
				end->next = diamondsFoundationCopy;
				diamondsFoundationCopy = end;
			}
			else if (compareFoundationCards(end, heartsFoundationCopy) == 1)
			{
				end->next = heartsFoundationCopy;
				heartsFoundationCopy = end;
			}
			else if (compareFoundationCards(end, spadesFoundationCopy) == 1)
			{
				end->next = spadesFoundationCopy;
				spadesFoundationCopy = end;
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
			if (compareCards(uncoveredTable[7 - src], end) == 1)
			{
				current = uncoveredTable[7 - src];
				end->next = current;
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
	for (int i = 0; i < sizeof(ranksArr); i++)
	{
		if (ranksArr[i] == rankCard1)
		{
			if (ranksArr[i + 1] == rankCard2)
			{
				return 1;
			}
		}
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
	char rankCard2 = (card2->rank);
	char suitCard1 = card1->suit;
	char suitCard2 = card2->suit;

	if (suitCard1 == 'h' && suitCard2 == 'h')
	{
		if (compareFoundationRank(rankCard1, rankCard2) == 1)
		{
			return 1;
		}
	}
	else if (suitCard1 == 'c' && suitCard2 == 'c')
	{
		if (compareFoundationRank(rankCard1, rankCard2) == 1)
		{
			return 1;
		}
	}
	else if (suitCard1 == 'd' && suitCard2 == 'd')
	{
		if (compareFoundationRank(rankCard1, rankCard2) == 1)
		{
			return 1;
		}
	}
	else if (suitCard1 == 's' && suitCard2 == 's')
	{
		if (compareFoundationRank(rankCard1, rankCard2) == 1)
		{
			return 1;
		}
	}
	return 0;
}

int compareFoundationRank(char rankCard1, char rankCard2)
{
	for (int i = 0; i < sizeof(ranksArr); i++)
	{
		if (ranksArr[i] == rankCard1)
		{
			if (ranksArr[i - 1] == rankCard2)
			{
				return 1;
			}
		}
	}
	return 0;
}

int compareOppositeColor(node *card)
{
	int j = 0;
	int found = 0;
	if (card->suit == 'c')
	{
		for (int i = 0; i < sizeof(ranksArr); i++)
		{
			if (ranksArr[i] == card->rank)
			{
				if (i - 1 == 0)
				{
					j = 0;
				}
				else
				{
					j = i - 1;
				}

				for (int k = j; k < sizeof(ranksArr); k++)
				{
					if (ranksArr[k] == diamondsFoundation->rank)
					{
						found = 1;
					}
				}

				for (int k = j; k < sizeof(ranksArr); k++)
				{
					if (ranksArr[k] == heartsFoundation->rank)
					{
						if (found == 1)
						{
							return 1;
						}
					}
				}
			}
		}
	}
	else if (card->suit == 'd')
	{
		for (int i = 0; i < sizeof(ranksArr); i++)
		{
			if (ranksArr[i] == card->rank)
			{
				if (i - 1 == 0)
				{
					j = 0;
				}
				else
				{
					j = i - 1;
				}

				for (int k = j; k < sizeof(ranksArr); k++)
				{
					if (ranksArr[k] == clubsFoundation->rank)
					{
						found = 1;
					}
				}

				for (int k = j; k < sizeof(ranksArr); k++)
				{
					if (ranksArr[k] == spadesFoundation->rank)
					{
						if (found == 1)
						{
							return 1;
						}
					}
				}
			}
		}
	}
	else if (card->suit == 'h')
	{
		for (int i = 0; i < sizeof(ranksArr); i++)
		{
			if (ranksArr[i] == card->rank)
			{
				if (i - 1 == 0)
				{
					j = 0;
				}
				else
				{
					j = i - 1;
				}

				for (int k = j; k < sizeof(ranksArr); k++)
				{
					if (ranksArr[k] == clubsFoundation->rank)
					{
						found = 1;
					}
				}

				for (int k = j; k < sizeof(ranksArr); k++)
				{
					if (ranksArr[k] == spadesFoundation->rank)
					{
						if (found == 1)
						{
							return 1;
						}
					}
				}
			}
		}
	}
	else if (card->suit == 's')
	{
		for (int i = 0; i < sizeof(ranksArr); i++)
		{
			if (ranksArr[i] == card->rank)
			{
				if (i - 1 == 0)
				{
					j = 0;
				}
				else
				{
					j = i - 1;
				}

				for (int k = j; k < sizeof(ranksArr); k++)
				{
					if (ranksArr[k] == diamondsFoundation->rank)
					{
						found = 1;
					}
				}

				for (int k = j; k < sizeof(ranksArr); k++)
				{
					if (ranksArr[k] == heartsFoundation->rank)
					{
						if (found == 1)
						{
							return 1;
						}
					}
				}
			}
		}
	}
	return 0;
}