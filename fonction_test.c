#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonction_test.h"

int test(int** tabJoueur, int a)
{
    int i,j;
    for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            if(a == tabJoueur[i][j])
            return 0;
        }
    }
    return 1;
}


int testValide(int** tabJoueur, int deck, int carte)
{
    int i,j;
    int v = 0;
    int c = carte;
    while(v == 0)
    {
        for(i=deck;i<=deck;i++)
        {
            for(j=0;j<10;j++)
            {
                if(c == tabJoueur[deck][j] && tabJoueur[deck][j] != 0) {
                    v = 1;
                    return c;
                    }
            }
            printf("Cette carte n'est pas comprise dans votre deck, veuillez en choisir une nouvelle : ");
            scanf("%d", &c);
        }
    }
}


int testBoard(int** tabJoueur, int board[4][5], int l, int c, int a)
{
    int i,j;
    for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            if(a == tabJoueur[i][j])
            return 0;
        }
    }

    for(i=0;i<l;i++)
    {
        for(j=0;j<l;j++)
        {
            if(a == board[i][j])
            return 0;
        }
    }
    return 1;
}

