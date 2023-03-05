#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Remplir.h"

void remplir(int tab[], int size)
{
    int i;
    tab[0]=0;
    for(i=1; i<size ;i++)
    {
        if(i%5 == 0 && i%10 ==0)
        {
            tab[i] = 3;
        }
        else if(i%5 == 0 && i%10 != 0 && i != 55)
        {
            tab[i] = 2;
        }
        else if(i == 11 || i == 22 || i == 33 || i == 44 || i == 66 || i == 77 || i == 88 || i == 99)
        {
            tab[i] = 5;
        }
        else if(i == 55)
        {
            tab[i] = 7;
        }
        else
        {
            tab[i] =1;
        }
    }
}

void remplacer(int** tabJoueur, int* tabDeck, int deck, int k)
{
    int i,j;
    for(i=0;i<=deck;i++)
    {
        for(j=0;j<10;j++)
        {
            if(tabJoueur[deck][j] == tabDeck[k])
            tabJoueur[deck][j] = 0;
        }
    }
}

void duplique(int board[4][5], int board2[4][5], int l, int c)
{
    int i,j;
    int a;
    for(i=0;i<l;i++)
    {
        for(j=0;j<c;j++)
        {
            board2[i][j] = 0;
        }
    }
    for(i=0;i<l;i++)
    {
        a=0;
        for(j=0;j<c-1;j++)
        {
            if(board[i][j] < board[i][j+1])
            {
               a++;
            }
        }
        board2[i][a] = board[i][a];
    }
}
