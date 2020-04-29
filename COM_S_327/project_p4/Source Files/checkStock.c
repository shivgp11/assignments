#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "check.h"
#include <stdlib.h>

extern int line;
extern char c;
extern int stockC;
extern int wasteC;

int checkStock(FILE *fp)
{
    char stock[7];
    fgets(stock, 7, fp);
    if (strcmp(stock, "STOCK:") != 0)
    {
        fprintf(stderr, "Expected 'STOCK:' near line %d\n", line);
        return 0;
    }
    parse(fp);
    int r;
    int s;
    int b;
    int i = 0;
    node *previous;
    node *current = wasteStack;
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
                wasteStack = current;
            }
            else
            {
                current = (node *)malloc(sizeof(node) * 1);
                current->rank = r;
                current->suit = s;
                previous->next = current;
                previous = current;
            }

            wasteC++;
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
    i = 0;
    b = fgetc(fp);
    ungetc(b, fp);

    if (b != ' ' && b != '\r' && b != '\n' && b != '\t')
    {
        fprintf(stderr, "1: ");
        fprintf(stderr, "Expecting ' ' after '|' near line %d\n", line);
        return 0;
    }
    current = stockStack;
    for (;;)
    {
        parse(fp);
        c = fgetc(fp);
        ungetc(c, fp);
        if (c == 'M')
        {
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
                stockStack = current;
            }
            else
            {
                current = (node *)malloc(sizeof(node) * 1);
                current->rank = r;
                current->suit = s;
                previous->next = current;
                previous = current;
            }

            stockC++;
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

    //printing
    // printf("WASTE | STOCK:\n");

    // current = wasteStack;
    // while(current != NULL) {
    // 	printf("%c", current->rank);
    // 	printf("%c ", current->suit);
    // 	current = current->next;
    // }
    // printf("| ");
    // current = stockStack;
    // while(current != NULL) {
    // 	printf("%c", current->rank);
    // 	printf("%c ", current->suit);
    // 	current = current->next;
    // }
    // printf("\n");

    //reverses the waste linked list
    current = wasteStack;
    previous = NULL;
    node *next = NULL;
    while (current != NULL)
    {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    wasteStack = previous;

    return 1;
}