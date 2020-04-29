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

    if (argc > 1)
    {
        fp = fopen(argv[1], "r");
        if (fp == NULL)
        {
            printf("No such file\n");
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

    fprintf(stdout, "Input file is valid\n");
    fprintf(stdout, "%d covered cards\n", covered);
    fprintf(stdout, "%d stock cards\n", stockC);
    fprintf(stdout, "%d waste cards\n", wasteC);

    fclose(fp);

    return 0;
}