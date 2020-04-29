#include <stdio.h>
#include <stdlib.h>
#include "cards.h"
#include "random.h"

extern unsigned long RNG_seed;

int deck[52];
node *Cards[52];

char Ranks[] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
char Suits[] = {'c', 'd', 'h', 's'};

void randomize()
{
    createCards();
    shuffle(deck);
    createGame();
}

void createGame()
{
    node *current;
    node *previous;

    int counter = 0;
    uncoveredTable[6] = Cards[deck[counter] - 1];
    counter++;

    current = coveredTable[5];
    for (int i = 0; i < 1; i++)
    {
        if (current == NULL)
        {
            current = Cards[deck[counter] - 1];
            counter++;
            previous = current;
            coveredTable[5] = current;
        }
        else
        {
            current = Cards[deck[counter] - 1];
            counter++;
            previous->next = current;
            previous = current;
        }
    }
    uncoveredTable[5] = Cards[deck[counter] - 1];
    counter++;

    current = coveredTable[4];
    for (int i = 0; i < 2; i++)
    {
        if (current == NULL)
        {
            current = Cards[deck[counter] - 1];
            counter++;
            previous = current;
            coveredTable[4] = current;
        }
        else
        {
            current = Cards[deck[counter] - 1];
            counter++;
            previous->next = current;
            previous = current;
        }
    }
    uncoveredTable[4] = Cards[deck[counter] - 1];
    counter++;

    current = coveredTable[3];
    for (int i = 0; i < 3; i++)
    {
        if (current == NULL)
        {
            current = Cards[deck[counter] - 1];
            counter++;
            previous = current;
            coveredTable[3] = current;
        }
        else
        {
            current = Cards[deck[counter] - 1];
            counter++;
            previous->next = current;
            previous = current;
        }
    }
    uncoveredTable[3] = Cards[deck[counter] - 1];
    counter++;

    current = coveredTable[2];
    for (int i = 0; i < 4; i++)
    {
        if (current == NULL)
        {
            current = Cards[deck[counter] - 1];
            counter++;
            previous = current;
            coveredTable[2] = current;
        }
        else
        {
            current = Cards[deck[counter] - 1];
            counter++;
            previous->next = current;
            previous = current;
        }
    }
    uncoveredTable[2] = Cards[deck[counter] - 1];
    counter++;

    current = coveredTable[1];
    for (int i = 0; i < 5; i++)
    {
        if (current == NULL)
        {
            current = Cards[deck[counter] - 1];
            counter++;
            previous = current;
            coveredTable[1] = current;
        }
        else
        {
            current = Cards[deck[counter] - 1];
            counter++;
            previous->next = current;
            previous = current;
        }
    }
    uncoveredTable[1] = Cards[deck[counter] - 1];
    counter++;

    current = coveredTable[0];
    for (int i = 0; i < 6; i++)
    {
        if (current == NULL)
        {
            current = Cards[deck[counter] - 1];
            counter++;
            previous = current;
            coveredTable[0] = current;
        }
        else
        {
            current = Cards[deck[counter] - 1];
            counter++;
            previous->next = current;
            previous = current;
        }
    }
    uncoveredTable[0] = Cards[deck[counter] - 1];
    counter++;

    current = stockStack;
    while (counter < 52)
    {
        if (current == NULL)
        {
            current = Cards[deck[counter] - 1];
            counter++;
            previous = current;
            stockStack = current;
        }
        else
        {
            current = Cards[deck[counter] - 1];
            counter++;
            previous->next = current;
            previous = current;
        }
    }
}

void createCards()
{
    for (int i = 0; i < 13; i++)
    {
        Cards[i] = (node *)malloc(sizeof(node));
        Cards[i]->rank = Ranks[i];
        Cards[i]->suit = 'c';
    }
    for (int i = 13; i < 26; i++)
    {
        Cards[i] = (node *)malloc(sizeof(node));
        Cards[i]->rank = Ranks[i - 13];
        Cards[i]->suit = 'd';
    }
    for (int i = 26; i < 39; i++)
    {
        Cards[i] = (node *)malloc(sizeof(node));
        Cards[i]->rank = Ranks[i - 26];
        Cards[i]->suit = 'h';
    }
    for (int i = 39; i < 52; i++)
    {
        Cards[i] = (node *)malloc(sizeof(node));
        Cards[i]->rank = Ranks[i - 39];
        Cards[i]->suit = 's';
    }
}
void shuffle(int deck[])
{
    for (int i = 0; i < 52; i++)
    {
        deck[i] = i + 1;
    }
    for (int i = 0; i < 51; i++)
    {
        int j = choose_randomly_between(i, 51);
        if (i != j)
        {
            Swap(i, j);
        }
    }
}

long choose_randomly_between(long a, long b)
{
    return a + (long)((b - a + 1) * Random());
}

void Swap(int i, int j)
{
    int temp = deck[i];
    deck[i] = deck[j];
    deck[j] = temp;
}

double Random()
{
    const unsigned long MODULUS = 2147483647;
    const unsigned long MULTIPLIER = 48271;
    const unsigned long Q = MODULUS / MULTIPLIER;
    const unsigned long R = MODULUS % MULTIPLIER;
    unsigned long t1 = MULTIPLIER * (RNG_seed % Q);
    unsigned long t2 = R * (RNG_seed / Q);

    if (t1 > t2)
    {
        RNG_seed = t1 - t2;
    }
    else
    {
        RNG_seed = t1 + (MODULUS - t2);
    }
    return ((double)RNG_seed / MODULUS);
}