#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonctions_tri.h"

void tri_selection(int** tabJoueur, int nbJoueur)
{
     int i,j,k;
     int min,temp;
     for(k=0;k<nbJoueur;k++)
     {
        for(i = 0 ; i < 10-1 ; i++)
        {
            min = i;
            for(j = i+1 ; j < 10 ; j++)
                if(tabJoueur[k][j] < tabJoueur[k][min])
                    min = j;
            if(min!=i)
            {
                temp = tabJoueur[k][i];
                tabJoueur[k][i]=tabJoueur[k][min];
                tabJoueur[k][min]=temp;
            }
        }
     }
}

void tri_Deck(int* tab, int nbJoueur)
{
    int tmp =0;
    int i, j;

    for(i=1; i<nbJoueur; i++)
    {
        tmp = tab[i];
        j = i-1;
        while(j>-1 && tab[j]>tmp)
        {
            tab[j+1] = tab[j];
            j--;
        }
        tab[j+1] = tmp;
    }
}
