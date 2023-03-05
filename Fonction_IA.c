#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Fonction_IA.h"
#include "Remplir.h"


int choisirCarte_IA(int** tabJoueur, int nbJoueur, int board[4][5], int board2[4][5], int l, int c, int deckIA)
{
    int i,j,k;
    duplique(board,board2,l, c);
    for(i=0;i<10;i++)
    {
        for(j=0;j<l;j++)
        {
            for(k=0;k<c-1;k++)
            {
                if(tabJoueur[deckIA][i] != 0 && tabJoueur[deckIA][i] > board2[j][k] && board2[j][k] != 0)
                {
                    return tabJoueur[deckIA][i];
                }
            }
        }
    }
    for(i=0;i<10;i++)
    {
        if(tabJoueur[deckIA][i] != 0)
        return tabJoueur[deckIA][i];
    }
}

void point_ligne(int* tabCompt, int board[4][5], int l, int c)
{
    int i,j, k=0;
    for(i=0;i<l;i++)
    {
        for(j=0;j<c;j++)
        {
            if(board[i][j]%5 == 0 && board[i][j]%10 == 0 && board[i][j] != 0)
            {
            tabCompt[k] = tabCompt[k] + 3;
            }
        else if(board[i][j]%5 == 0 && board[i][j]%10 != 0 && board[i][j] != 55)
            {
            tabCompt[k] = tabCompt[k] + 2;
            }
        else if(board[i][j] == 11 || board[i][j] == 22 || board[i][j] == 33 || board[i][j] == 44 || board[i][j] == 66 || board[i][j] == 77 || board[i][j] == 88 || board[i][j] == 99)
            {
            tabCompt[k] = tabCompt[k] + 5;
            }
        else if(board[i][j] == 55)
            {
             tabCompt[k] = tabCompt[k] + 7;
            }
        else if(board[i][j] == 0)
            {
             tabCompt[k] = tabCompt[k] + 0;
            }
        else
            {
            tabCompt[k] = tabCompt[k] + 1;
            }
        }
        k++;
    }
}

int valeurPlusProche(int* tabStock2, int tabBoard2[4], int board2[4][5], int l, int c)
{
    int i,j, k = -1;
    int stock;
    int stock1;
    int min = 104;
    for(i=0;i<l;i++)
    {
        for(j=0;j<c;j++)
        {
            if(board2[i][j] != 0)
            {
                k++;
                tabBoard2[k] = board2[i][j];
            }
        }
    }

    for(i=0;i<10;i++)
    {
        for(j=0;j<4;j++)
        {
            if(tabStock2[i] - tabBoard2[j] > 0)
            stock = tabStock2[i] - tabBoard2[j];
            if(min > stock)
            min = stock;
            stock1 = tabStock2[i];
        }
    }
    return stock1;
}
