#include <stdio.h>
#include <stdlib.h>
#include "fonction_afficher.h"

void afficherTableau(int **tabJoueur, int nbJoueur, int vC)
{
    int i;
    int j;
    for(i=0; i<nbJoueur; i++)
    {
        for(j=0; j<vC; j++)
        {
            printf("%d ", tabJoueur[i][j]);

        }
        printf("\n");
    }
}




void afficherBoard(int board[4][5], int l, int c)
{
    int i,j;
    int a = 0;
    for(i=0;i<l;i++)
    {
        printf("\n|");
        for(j=0;j<c;j++)
        {
            if(board[i][j]%5 == 0 && board[i][j]%10 == 0 && board[i][j] != 0)
            {
            printf(" %d(3) |", board[i][j]);
            }
        else if(board[i][j]%5 == 0 && board[i][j]%10 != 0 && board[i][j] != 55)
            {
            printf(" %d(2) |", board[i][j]);
            }
        else if(board[i][j] == 11 || board[i][j] == 22 || board[i][j] == 33 || board[i][j] == 44 || board[i][j] == 66 || board[i][j] == 77 || board[i][j] == 88 || board[i][j] == 99)
            {
            printf(" %d(5) |", board[i][j]);
            }
        else if(board[i][j] == 55)
            {
             printf(" %d(7) |", board[i][j]);
            }
        else if(board[i][j] == 0)
            {
            printf(" %d |", board[i][j]);
            }
        else
            {
            printf(" %d(1) |", board[i][j]);
            }
        }
        printf(" ligne %d", a);
        a++;
    }
    printf("\n\n");
}


void afficherDeck(int** tabJoueur, int deck)
{
    int i,j;
    for(i=deck;i<=deck;i++)
    {
        for(j=0;j<10;j++)
         {
             printf("%d ", tabJoueur[i][j]);
         }
    }
    printf("\n\n");
}
