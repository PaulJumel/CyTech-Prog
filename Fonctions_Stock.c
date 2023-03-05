#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Fonctions_Stock.h"

int stock(int* tabDeck2, int nbJoueur)
{
    int i;
    int stock_i = 1;
    int min = tabDeck2[0];
    for(i=1;i<nbJoueur;i++)
    {
        if(min > tabDeck2[i]){
            min = tabDeck2[i];
            stock_i = i+1;
        }
    }
    return stock_i;
}


int stock2(int* tabDeck2, int* tabDeck, int nbJoueur, int k)
{
    int i;
    int stock_i;
    for(i=0;i<nbJoueur;i++)
    {
        if(tabDeck2[i] == tabDeck[k])
        stock_i = i;
    }
    return stock_i;
}
