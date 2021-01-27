#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <termbox.h>
#include "check.h"
#include "display.h"
#include "random.h"

int covered = 0;
int uncovered = 0;
int line = 1;
int stockC;
int wasteC;
int readMoves = 99999;
int c;
int turnNum = 0;
int limit = 99999;
int numMoves = 0;
int checkMovesIs2 = 0;
unsigned long RNG_seed;

int found_f = 0;
int found_s = 0;
int found_limit = 0;
char *filename;

struct tb_cell cell;

int parseFiles(FILE *fp);
void initTable();
void clearGame();

int main(int argc, char *argv[])
{
    FILE *fp;

    int i = 1;
    if (strcmp(argv[i], "-f") == 0)
    {
        found_f = 1;
        i++;
        filename = argv[i];
        fp = fopen(filename, "r");
        if (fp == NULL)
        {
            printf("No such file\n");
        }
    }
    else if (strcmp(argv[i], "-s") == 0)
    {
        i++;
        RNG_seed = atoi(argv[i]);
        i++;
        found_s = 1;
        for (i; i < argc; i++)
        {
            if (strcmp(argv[i], "-1") == 0)
            {
                turnNum = 1;
            }
            else if (strcmp(argv[i], "-3") == 0)
            {
                turnNum = 3;
            }
            else if (strcmp(argv[i], "-l") == 0)
            {
                i++;
                found_limit = 1;
                limit = atoi(argv[i]);
            }
        }
    }

    if (found_f == 1)
    {
        parseFiles(fp);
    }
    else if (found_s == 1)
    {
        randomize();
    }

    tb_init();
    initTable();

    int wasteMove = 0;
    int foundationMove = 0;
    int col1Move = 0;
    int col2Move = 0;
    int col3Move = 0;
    int col4Move = 0;
    int col5Move = 0;
    int col6Move = 0;
    int col7Move = 0;

    for (;;)
    {
        tb_present();
        struct tb_event event;
        tb_poll_event(&event);

        if (TB_KEY_ESC == event.key)
            break;

        if ('.' == event.ch)
        {
            if (validateDot() == 0)
            {
                invalidMove(1);
                continue;
            }
            initTable();
            continue;
        }

        if ('x' == event.ch)
        {
            if (limit != 0)
            {
                if (reset() == 0)
                {
                    invalidMove(1);
                    continue;
                }
                limit--;
                initTable();
                continue;
            }
            else
            {
                invalidMove(1);
                continue;
            }
        }

        if ('w' == event.ch)
        {
            if (wasteMove == 1)
            {
                invalidMove(1);
                continue;
            }
            wasteMove = 1;
            continue;
        }

        if ('f' == event.ch)
        {
            if (foundationMove == 1)
            {
                invalidMove();
                continue;
            }
            foundationMove = 1;

            if (wasteMove == 1)
            {
                foundationMove = 0;
                wasteMove = 0;
                if (validateMove("w->f") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col1Move == 1)
            {
                col1Move = 0;
                foundationMove = 0;
                if (validateMove("1->f") == 0)
                {
                    invalidMove();
                    continue;
                }
                initTable();
                continue;
            }

            if (col2Move == 1)
            {
                col2Move = 0;
                foundationMove = 0;
                if (validateMove("2->f") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col3Move == 1)
            {
                col3Move = 0;
                foundationMove = 0;
                if (validateMove("3->f") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col4Move == 1)
            {
                col4Move = 0;
                foundationMove = 0;
                if (validateMove("4->f") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col5Move == 1)
            {
                col5Move = 0;
                foundationMove = 0;
                if (validateMove("5->f") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col6Move == 1)
            {
                col6Move = 0;
                foundationMove = 0;
                if (validateMove("6->f") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col7Move == 1)
            {
                col7Move = 0;
                foundationMove = 0;
                if (validateMove("7->f") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }
            continue;
        }

        if ('1' == event.ch)
        {
            if (col1Move == 1)
            {
                invalidMove(1);
                continue;
            }
            col1Move = 1;

            if (wasteMove == 1)
            {
                col1Move = 0;
                wasteMove = 0;
                if (validateMove("w->1") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col2Move == 1)
            {
                col2Move = 0;
                col1Move = 0;
                if (validateMove("2->1") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col3Move == 1)
            {
                col3Move = 0;
                col1Move = 0;
                if (validateMove("3->1") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col4Move == 1)
            {
                col4Move = 0;
                col1Move = 0;
                if (validateMove("4->1") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col5Move == 1)
            {
                col5Move = 0;
                col1Move = 0;
                if (validateMove("5->1") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col6Move == 1)
            {
                col6Move = 0;
                col1Move = 0;
                if (validateMove("6->1") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col7Move == 1)
            {
                col7Move = 0;
                col1Move = 0;
                if (validateMove("7->1") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }
            continue;
        }

        if ('2' == event.ch)
        {
            if (col2Move == 1)
            {
                invalidMove(1);
                continue;
            }
            col2Move = 1;

            if (wasteMove == 1)
            {
                col2Move = 0;
                wasteMove = 0;
                if (validateMove("w->2") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col1Move == 1)
            {
                col1Move = 0;
                col2Move = 0;
                if (validateMove("1->2") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col3Move == 1)
            {
                col3Move = 0;
                col2Move = 0;
                if (validateMove("3->2") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col4Move == 1)
            {
                col4Move = 0;
                col2Move = 0;
                if (validateMove("4->2") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col5Move == 1)
            {
                col5Move = 0;
                col2Move = 0;
                if (validateMove("5->2") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col6Move == 1)
            {
                col6Move = 0;
                col2Move = 0;
                if (validateMove("6->2") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col7Move == 1)
            {
                col7Move = 0;
                col2Move = 0;
                if (validateMove("7->2") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }
            continue;
        }

        if ('3' == event.ch)
        {
            if (col3Move == 1)
            {
                invalidMove(1);
                continue;
            }
            col3Move = 1;

            if (wasteMove == 1)
            {
                col3Move = 0;
                wasteMove = 0;
                if (validateMove("w->3") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col1Move == 1)
            {
                col1Move = 0;
                col3Move = 0;
                if (validateMove("1->3") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col2Move == 1)
            {
                col2Move = 0;
                col3Move = 0;
                if (validateMove("2->3") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col4Move == 1)
            {
                col4Move = 0;
                col3Move = 0;
                if (validateMove("4->3") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col5Move == 1)
            {
                col5Move = 0;
                col3Move = 0;
                if (validateMove("5->3") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col6Move == 1)
            {
                col6Move = 0;
                col3Move = 0;
                if (validateMove("6->3") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col7Move == 1)
            {
                col7Move = 0;
                col3Move = 0;
                if (validateMove("7->3") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }
            continue;
        }

        if ('4' == event.ch)
        {
            if (col4Move == 1)
            {
                invalidMove(1);
                continue;
            }
            col4Move = 1;

            if (wasteMove == 1)
            {
                col4Move = 0;
                wasteMove = 0;
                if (validateMove("w->4") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col1Move == 1)
            {
                col1Move = 0;
                col4Move = 0;
                if (validateMove("1->4") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col2Move == 1)
            {
                col2Move = 0;
                col4Move = 0;
                if (validateMove("2->4") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col3Move == 1)
            {
                col3Move = 0;
                col4Move = 0;
                if (validateMove("3->4") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col5Move == 1)
            {
                col5Move = 0;
                col4Move = 0;
                if (validateMove("5->4") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col6Move == 1)
            {
                col6Move = 0;
                col4Move = 0;
                if (validateMove("6->4") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col7Move == 1)
            {
                col7Move = 0;
                col4Move = 0;
                if (validateMove("7->4") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }
            continue;
        }

        if ('5' == event.ch)
        {
            if (col5Move == 1)
            {
                invalidMove(1);
                continue;
            }
            col5Move = 1;

            if (wasteMove == 1)
            {
                col5Move = 0;
                wasteMove = 0;
                if (validateMove("w->5") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col1Move == 1)
            {
                col1Move = 0;
                col5Move = 0;
                if (validateMove("1->5") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col2Move == 1)
            {
                col2Move = 0;
                col5Move = 0;
                if (validateMove("2->5") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col3Move == 1)
            {
                col3Move = 0;
                col5Move = 0;
                if (validateMove("3->5") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col4Move == 1)
            {
                col4Move = 0;
                col5Move = 0;
                if (validateMove("4->5") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col6Move == 1)
            {
                col6Move = 0;
                col5Move = 0;
                if (validateMove("6->5") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col7Move == 1)
            {
                col7Move = 0;
                col5Move = 0;
                if (validateMove("7->5") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }
            continue;
        }

        if ('6' == event.ch)
        {
            if (col6Move == 1)
            {
                invalidMove(1);
                continue;
            }
            col6Move = 1;

            if (wasteMove == 1)
            {
                col6Move = 0;
                wasteMove = 0;
                if (validateMove("w->6") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col1Move == 1)
            {
                col1Move = 0;
                col6Move = 0;
                if (validateMove("1->6") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col2Move == 1)
            {
                col2Move = 0;
                col6Move = 0;
                if (validateMove("2->6") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col3Move == 1)
            {
                col3Move = 0;
                col6Move = 0;
                if (validateMove("3->6") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col4Move == 1)
            {
                col4Move = 0;
                col6Move = 0;
                if (validateMove("4->6") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col5Move == 1)
            {
                col5Move = 0;
                col6Move = 0;
                if (validateMove("5->6") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col7Move == 1)
            {
                col7Move = 0;
                col6Move = 0;
                if (validateMove("7->6") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }
            continue;
        }

        if ('7' == event.ch)
        {
            if (col7Move == 1)
            {
                invalidMove(1);
                continue;
            }
            col7Move = 1;

            if (wasteMove == 1)
            {
                col7Move = 0;
                wasteMove = 0;
                if (validateMove("w->7") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col1Move == 1)
            {
                col1Move = 0;
                col7Move = 0;
                if (validateMove("1->7") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col2Move == 1)
            {
                col2Move = 0;
                col7Move = 0;
                if (validateMove("2->7") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col3Move == 1)
            {
                col3Move = 0;
                col7Move = 0;
                if (validateMove("3->7") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col4Move == 1)
            {
                col4Move = 0;
                col7Move = 0;
                if (validateMove("4->7") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col5Move == 1)
            {
                col5Move = 0;
                col7Move = 0;
                if (validateMove("5->7") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }

            if (col6Move == 1)
            {
                col6Move = 0;
                col7Move = 0;
                if (validateMove("6->7") == 0)
                {
                    invalidMove(1);
                    continue;
                }
                initTable();
                continue;
            }
            continue;
        }

        if ('r' == event.ch)
        {
            clearGame();
            if (found_f == 1)
            {
                fseek(fp, 0, SEEK_SET);
                parseFiles(fp);
            }
            else if (found_s == 1)
            {
                randomize();
            }
            tb_clear();
            initTable();
            continue;
        }
    }

    tb_shutdown();
    fprintf(stdout, "Done!\n");
    return 0;
}

int parseFiles(FILE *fp)
{
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
    return 1;
}

void initTable()
{
    tb_clear();
    init_hotkeys_display();
    init_tablueau_display();
    init_foundations_display();
    init_waste_display();
}

void clearGame()
{
    node *current;
    node *next;
    if (wasteStack != NULL)
    {
        current = wasteStack;
        while (current != NULL)
        {
            next = current->next;
            free(current);
            current = next;
        }
        wasteStack = NULL;
    }
    if (stockStack != NULL)
    {
        current = stockStack;
        while (current != NULL)
        {
            next = current->next;
            free(current);
            current = next;
        }
        stockStack = NULL;
    }
    if (clubsFoundation != NULL)
    {
        current = clubsFoundation;
        while (current != NULL)
        {
            next = current->next;
            free(current);
            current = next;
        }
        clubsFoundation = NULL;
    }
    if (diamondsFoundation != NULL)
    {
        current = diamondsFoundation;
        while (current != NULL)
        {
            next = current->next;
            free(current);
            current = next;
        }
        diamondsFoundation = NULL;
    }
    if (heartsFoundation != NULL)
    {
        current = heartsFoundation;
        while (current != NULL)
        {
            next = current->next;
            free(current);
            current = next;
        }
        heartsFoundation = NULL;
    }
    if (spadesFoundation != NULL)
    {
        current = spadesFoundation;
        while (current != NULL)
        {
            next = current->next;
            free(current);
            current = next;
        }
        spadesFoundation = NULL;
    }
    for (int i = 0; i < 7; i++)
    {
        if (coveredTable[i] != NULL)
        {
            current = coveredTable[i];
            while (current != NULL)
            {
                next = current->next;
                free(current);
                current = next;
            }
            coveredTable[i] = NULL;
        }
    }
    for (int i = 0; i < 7; i++)
    {
        if (uncoveredTable[i] != NULL)
        {
            current = uncoveredTable[i];
            while (current != NULL)
            {
                next = current->next;
                free(current);
                current = next;
            }
            uncoveredTable[i] = NULL;
        }
    }
}