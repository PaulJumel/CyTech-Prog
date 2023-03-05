#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonction_initialiser.h"
#include "Random.h"
#include "fonction_test.h"


void iniTabJoueur(int **tabJoueur, int nbJoueur, int vC)
{
    int i,j;
    for(i=0;i<nbJoueur;i++)
    {
        for(j=0;j<vC;j++)
        {
            tabJoueur[i][j] = 0;
        }
    }
}

void iniTabDeck(int* tabDeck, int nbJoueur)
{
    int i;
    for(i=0;i<nbJoueur;i++)
    {
            tabDeck[i] = 0;
    }
}

void initboard(int board[4][5], int** tabJoueur, int l, int c, int MAX, int MIN)
{
    int i,j;
    int a;
    int b;
    for(i=0;i<4;i++)
    {
        for(j=0;j<5;j++)
        {
            if(j==0) {
                while(board[i][j] == 0) {
                a = nbRandom(MAX, MIN);
                b = testBoard(tabJoueur, board, l, c, a);
                if(b == 1)
                board[i][j] = a;
                }
            }
            else
            board[i][j] = 0;
        }
    }
}
