#include "cards.h"

int validateMove(char *str);

int compareCards(node *card1, node *card2);

int compareSuit(char suitCard1, char suitCard2);

int compareRank(char rankCard1, char rankCard2);

int compareFoundationCards(node *card1, node *card2);

int compareFoundationRank(char rankCard1, char rankCard2);

int validateDot();

int reset();

node *coveredTableCopy[7];
node *uncoveredTableCopy[7];

node *stockStackCopy;
node *wasteStackCopy;
node *clubsFoundationCopy;
node *diamondsFoundationCopy;
node *heartsFoundationCopy;
node *spadesFoundationCopy;