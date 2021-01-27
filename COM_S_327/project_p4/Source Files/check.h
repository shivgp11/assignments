#include "cards.h"

int checkCards(char rank, char suit);

int checkFoundations(FILE *fp);

int checkMoves(FILE *fp);

int checkRules(FILE *fp);

int checkStock(FILE *fp);

int checkTableau(FILE *fp);

int checkMovesWord(FILE *fp);

void parse(FILE *fp);

int validateMove(char *str);
int compareCards(node *card1, node *card2);
int compareSuit(char suitCard1, char suitCard2);
int compareRank(char rankCard1, char rankCard2);
int compareFoundationCards(node *card1, node *card2);
int compareFoundationRank(char rankCard1, char rankCard2);
int validateDot();
int reset();