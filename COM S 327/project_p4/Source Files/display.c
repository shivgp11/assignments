#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "display.h"
#include "cards.h"
#include <termbox.h>

struct tb_cell cell;
extern int turnNum;
extern int limit;
extern int found_limit;
extern char *filename;
extern int found_f;

void init_hotkeys_display()
{
    cell.bg = TB_GREEN;
    cell.fg = TB_GREEN;
    cell.ch = ' ';
    for (int i = 0; i < 34; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (i == 0 || j == 0 || i == 34 - 1 || j == 10 - 1)
            {
                tb_put_cell(i, j, &cell);
            }
        }
    }

    char str[50];
    int k = 0;

    if (found_f == 1)
    {
        strcpy(str, "File: ");
        cell.fg = TB_BLACK;
        k = 8;
        for (int i = 0; i < strlen(str); i++)
        {
            cell.ch = str[i];
            tb_put_cell(k, 0, &cell);
            k++;
        }

        strcpy(str, filename);
        k = 14;
        for (int i = 0; i < strlen(str); i++)
        {
            cell.ch = str[i];
            tb_put_cell(k, 0, &cell);
            k++;
        }
    }

    cell.fg = TB_BLACK;
    cell.bg = TB_MAGENTA;

    strcpy(str, "ESC");
    k = 2;

    for (int i = 0; i < strlen(str); i++)
    {
        cell.ch = str[i];
        tb_put_cell(k, 1, &cell);
        k++;
    }

    cell.ch = 'r';
    tb_put_cell(2, 2, &cell);

    cell.ch = 'n';
    tb_put_cell(2, 3, &cell);

    cell.ch = '.';
    tb_put_cell(2, 5, &cell);

    cell.ch = 'p';
    tb_put_cell(17, 1, &cell);

    cell.ch = 'u';
    tb_put_cell(17, 3, &cell);

    cell.ch = 'x';
    tb_put_cell(17, 5, &cell);

    strcpy(str, ": quit");
    k = 5;
    cell.fg = TB_WHITE;
    cell.bg = TB_BLACK;
    for (int i = 0; i < strlen(str); i++)
    {
        cell.ch = str[i];
        tb_put_cell(k, 1, &cell);
        k++;
    }

    strcpy(str, ": restart");
    k = 3;
    for (int i = 0; i < strlen(str); i++)
    {
        cell.ch = str[i];
        tb_put_cell(k, 2, &cell);
        k++;
    }

    strcpy(str, ": new game");
    k = 3;
    for (int i = 0; i < strlen(str); i++)
    {
        cell.ch = str[i];
        tb_put_cell(k, 3, &cell);
        k++;
    }

    strcpy(str, ": new card");
    k = 3;
    for (int i = 0; i < strlen(str); i++)
    {
        cell.ch = str[i];
        tb_put_cell(k, 5, &cell);
        k++;
    }

    strcpy(str, ": save to file");
    k = 18;
    for (int i = 0; i < strlen(str); i++)
    {
        cell.ch = str[i];
        tb_put_cell(k, 1, &cell);
        k++;
    }

    strcpy(str, ": undo move");
    k = 18;
    for (int i = 0; i < strlen(str); i++)
    {
        cell.ch = str[i];
        tb_put_cell(k, 3, &cell);
        k++;
    }

    strcpy(str, ": reset stock");
    k = 18;
    for (int i = 0; i < strlen(str); i++)
    {
        cell.ch = str[i];
        tb_put_cell(k, 5, &cell);
        k++;
    }

    strcpy(str, "To move, press the source and");
    k = 2;
    for (int i = 0; i < strlen(str); i++)
    {
        cell.ch = str[i];
        tb_put_cell(k, 6, &cell);
        k++;
    }

    strcpy(str, "then destination (one of W, F,");
    k = 2;
    for (int i = 0; i < strlen(str); i++)
    {
        cell.ch = str[i];
        tb_put_cell(k, 7, &cell);
        k++;
    }

    strcpy(str, "1, 2, 3, 4, 5, 6, 7)");
    k = 2;
    for (int i = 0; i < strlen(str); i++)
    {
        cell.ch = str[i];
        tb_put_cell(k, 8, &cell);
        k++;
    }
}

void init_tablueau_display()
{
    int col1Point = 38;

    cell.fg = TB_BLACK;
    cell.bg = TB_MAGENTA;
    int colNum = 1;
    int x = col1Point + 1;
    while (x <= 81)
    {
        cell.ch = colNum + '0';
        tb_put_cell(x, 0, &cell);
        x = x + 7;
        colNum++;
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

    node *coveredTableCopy[7];
    for (int i = 0; i < 7; i++)
    {
        coveredTableCopy[i] = coveredTable[i];
    }
    node *uncoveredTableCopy[7];
    for (int i = 0; i < 7; i++)
    {
        uncoveredTableCopy[i] = uncoveredTable[i];
    }

    int currRow = 1;
    int colPoint = col1Point;
    for (int i = 0; i < cardLineSize; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (coveredTableCopy[k] != NULL)
            {
                cell.fg = TB_BLACK;
                cell.bg = TB_CYAN;
                cell.ch = '#';
                for (int n = colPoint; n < colPoint + 4; n++)
                {
                    for (int m = currRow; m < currRow + 4; m++)
                    {
                        tb_put_cell(n, m, &cell);
                    }
                }
                coveredTableCopy[k] = coveredTableCopy[k]->next;
            }
            else
            {
                if (uncoveredTableCopy[k] != NULL)
                {
                    displayCard(uncoveredTableCopy[k]->rank, uncoveredTableCopy[k]->suit, colPoint, currRow);
                    uncoveredTableCopy[k] = uncoveredTableCopy[k]->next;
                }
            }
            colPoint = colPoint + 7;
            k--;
        }
        currRow++;
        colPoint = col1Point;
        k = 6;
    }
}

void displayCard(char rank, char suit, int col, int row)
{
    unsigned short suitSymbol;
    if (suit == 'c')
    {
        cell.fg = TB_BLACK;
        suitSymbol = 0x02663;
    }
    else if (suit == 'd')
    {
        cell.fg = TB_RED;
        suitSymbol = 0x02666;
    }
    else if (suit == 'h')
    {
        cell.fg = TB_RED;
        suitSymbol = 0x02665;
    }
    else if (suit == 's')
    {
        cell.fg = TB_BLACK;
        suitSymbol = 0x02660;
    }

    cell.bg = TB_WHITE;
    for (int i = col; i < col + 4; i++)
    {
        for (int j = row; j < row + 4; j++)
        {
            if ((i == col && j == row) || (i == col + 2 && j == row + 3))
            {
                cell.ch = rank;
                tb_put_cell(i, j, &cell);
                cell.ch = ' ';
                continue;
            }

            if ((i == col + 1 && j == row) || (i == col + 3 && j == row + 3))
            {
                cell.ch = suitSymbol;
                tb_put_cell(i, j, &cell);
                cell.ch = ' ';
                continue;
            }
            tb_put_cell(i, j, &cell);
        }
    }
}

void clearCard(int col, int row)
{
    cell.bg = TB_GREEN;
    cell.fg = TB_GREEN;
    cell.ch = ' ';
    for (int i = col; i < col + 4; i++)
    {
        for (int j = row; j < row + 4; j++)
        {
            tb_put_cell(i, j, &cell);
        }
    }
}

void invalidMove(int isInvalid)
{
    char str[13] = "Invalid Move";
    int column = 53;
    cell.fg = TB_BLACK;
    cell.bg = TB_RED;
    for (int i = 0; i < strlen(str); i++)
    {
        cell.ch = str[i];
        tb_put_cell(column, 23, &cell);
        column++;
    }
}

void init_foundations_display()
{
    int column; //represents column index on term box
    int row;    // represents the row index on term box

    char str[50] = "Foundations:";

    //"F" in magenta
    cell.fg = TB_BLACK;
    cell.bg = TB_MAGENTA;
    cell.ch = str[0];
    tb_put_cell(11, 11, &cell);

    // "Foundations"
    column = 12;
    cell.bg = TB_BLACK;
    cell.fg = TB_WHITE;
    for (int i = 1; i < strlen(str); i++)
    {
        cell.ch = str[i];
        tb_put_cell(column, 11, &cell);
        column++;
    }

    //empty foundations (4x4)
    if (clubsFoundation == NULL)
    {
        cell.bg = TB_GREEN;
        cell.fg = TB_BLACK;
        cell.ch = 0x02663; //unicode for clubs
        for (row = 13; row < 17; row++)
        {
            for (column = 4; column < 8; column++)
            {
                tb_put_cell(column, row, &cell);
            }
        }
    }
    else
    {
        displayCard(clubsFoundation->rank, clubsFoundation->suit, 4, 13);
    }

    if (diamondsFoundation == NULL)
    {
        cell.bg = TB_GREEN;
        cell.fg = TB_BLACK;
        cell.ch = 0x02666; //unicode for diamonds
        for (row = 13; row < 17; row++)
        {
            for (column = 11; column < 15; column++)
            {
                tb_put_cell(column, row, &cell);
            }
        }
    }
    else
    {
        displayCard(diamondsFoundation->rank, diamondsFoundation->suit, 11, 13);
    }

    if (heartsFoundation == NULL)
    {
        cell.bg = TB_GREEN;
        cell.fg = TB_BLACK;
        cell.ch = 0x02665; //unicode for hearts
        for (row = 13; row < 17; row++)
        {
            for (column = 18; column < 22; column++)
            {
                tb_put_cell(column, row, &cell);
            }
        }
    }
    else
    {
        displayCard(heartsFoundation->rank, heartsFoundation->suit, 18, 13);
    }

    if (spadesFoundation == NULL)
    {
        cell.bg = TB_GREEN;
        cell.fg = TB_BLACK;
        cell.ch = 0x02660; //unicode for spades
        for (row = 13; row < 17; row++)
        {
            for (column = 25; column < 29; column++)
            {
                tb_put_cell(column, row, &cell);
            }
        }
    }
    else
    {
        displayCard(spadesFoundation->rank, spadesFoundation->suit, 25, 13);
    }
}

void init_waste_display()
{
    cell.fg = TB_BLACK;
    cell.bg = TB_MAGENTA;
    cell.ch = 'W';
    tb_put_cell(3, 18, &cell);

    cell.fg = TB_WHITE;
    cell.bg = TB_BLACK;
    char str[20] = "aste (";
    char buffer[6];

    int column = 4;
    for (int i = 0; i < strlen(str); i++)
    {
        cell.ch = str[i];
        tb_put_cell(column, 18, &cell);
        column++;
    }

    if (found_limit == 0)
    {
        strcpy(str, "unlimited)");
        for (int i = 0; i < strlen(str); i++)
        {
            cell.ch = str[i];
            tb_put_cell(column, 18, &cell);
            column++;
        }
    }
    else
    {
        sprintf(buffer, "%d", limit);
        strcpy(str, " resets remaining)");
        for (int i = 0; i < strlen(buffer); i++)
        {
            cell.ch = buffer[i];
            tb_put_cell(column, 18, &cell);
            column++;
        }

        for (int i = 0; i < strlen(str); i++)
        {
            cell.ch = str[i];
            tb_put_cell(column, 18, &cell);
            column++;
        }
    }

    node *current;
    current = wasteStack;

    int wasteNum = 0;
    int stockNum = 0;
    column = 7;
    if (wasteStack == NULL)
    {
        clearCard(column, 20);
    }
    else
    {
        current = wasteStack;
        if (turnNum == 3)
        {
            if ((wasteStack->next) != NULL)
            {
                if ((wasteStack->next)->next != NULL)
                {
                    displayCard(((wasteStack->next)->next)->rank, ((wasteStack->next)->next)->suit, 7, 20);
                    displayCard((wasteStack->next)->rank, (wasteStack->next)->suit, 9, 20);
                    displayCard(wasteStack->rank, wasteStack->suit, 11, 20);
                }
                else
                {
                    displayCard((wasteStack->next)->rank, (wasteStack->next)->suit, 7, 20);
                    displayCard(wasteStack->rank, wasteStack->suit, 9, 20);
                    cell.bg = TB_BLACK;
                    cell.fg = TB_BLACK;
                    int col = 13;
                    int row = 20;
                }
            }
            else
            {
                displayCard(wasteStack->rank, wasteStack->suit, 7, 20);
                cell.bg = TB_BLACK;
                cell.fg = TB_BLACK;
                int col = 11;
                int row = 20;
            }
            while (current != NULL)
            {
                wasteNum++;
                current = current->next;
            }
        }
        else if (turnNum == 1)
        {
            displayCard(wasteStack->rank, wasteStack->suit, column, 20);
            while (current != NULL)
            {
                wasteNum++;
                current = current->next;
            }
        }
    }

    if (stockStack == NULL)
    {
        clearCard(22, 20);
    }
    else
    {
        current = stockStack;
        if (stockStack != NULL)
        {
            cell.fg = TB_BLACK;
            cell.bg = TB_CYAN;
            cell.ch = '#';
            for (int n = 22; n < 26; n++)
            {
                for (int m = 20; m < 24; m++)
                {
                    tb_put_cell(n, m, &cell);
                }
            }
        }
    }

    while (current != NULL)
    {
        stockNum++;
        current = current->next;
    }

    column = 9;
    sprintf(buffer, "%d", wasteNum);
    cell.fg = TB_WHITE;
    cell.bg = TB_BLACK;
    for (int i = 0; i < strlen(buffer); i++)
    {
        cell.ch = buffer[i];
        tb_put_cell(column, 24, &cell);
        column++;
    }

    sprintf(buffer, "%d", stockNum);
    column = 23;
    for (int i = 0; i < strlen(buffer); i++)
    {
        cell.ch = buffer[i];
        tb_put_cell(column, 24, &cell);
        column++;
    }
}