#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Fonctions_transformer.h"
#include "Fonctions_Stock.h"

void transforme(int** tabStock, int** tabTransforme, int* tabDeck2, int nbJoueur)
{
    int i,j;
    int a = stock(tabDeck2, nbJoueur);
    for(i=a-1;i<=a-1;i++)
    {
        for(j=0; j<5 ;j++)
        {
            if(tabStock[i][j]%5 == 0 && tabStock[i][j]%10 != 0 && tabStock[i][j] != 55)
            {
                tabTransforme[a-1][0] = tabTransforme[a-1][0] + 2;
            }
            else if(tabStock[i][j]%5 == 0 && tabStock[i][j]%10 == 0 && tabStock[i][j] != 0)
            {
                tabTransforme[a-1][0] = tabTransforme[a-1][0] + 3;
            }
            else if(tabStock[i][j] == 11 || tabStock[i][j] == 22 || tabStock[i][j] == 33 || tabStock[i][j] == 44 || tabStock[i][j] == 66 || tabStock[i][j] == 77 || tabStock[i][j] == 88 || tabStock[i][j] == 99)
            {
                tabTransforme[a-1][0] = tabTransforme[a-1][0] + 5;
            }
            else if(tabStock[i][j] == 55)
            {
                tabTransforme[a-1][0] = tabTransforme[a-1][0] + 7;
            }
            else if(tabStock[i][j] == 0)
            {
                tabTransforme[a-1][0] = tabTransforme[a-1][0] + 0;
            }
            else
            {
                tabTransforme[a-1][0] = tabTransforme[a-1][0] + 1;
            }
        }
    }
}


void transforme2(int** tabStock, int** tabTransforme, int* tabDeck2, int* tabDeck, int nbJoueur, int k)
{
    int i,j;
    int a = stock2(tabDeck2, tabDeck, nbJoueur, k);
    printf("%d", a);
    for(i=a;i<=a;i++)
    {
        for(j=0; j<5 ;j++)
        {
            if(tabStock[i][j]%5 == 0 && tabStock[i][j]%10 != 0 && tabStock[i][j] != 55)
            {
                tabTransforme[a][0] = tabTransforme[a][0] + 2;
            }
            else if(tabStock[i][j]%5 == 0 && tabStock[i][j]%10 == 0 && tabStock[i][j] != 0)
            {
                tabTransforme[a][0] = tabTransforme[a][0] + 3;
            }
            else if(tabStock[i][j] == 11 || tabStock[i][j] == 22 || tabStock[i][j] == 33 || tabStock[i][j] == 44 || tabStock[i][j] == 66 || tabStock[i][j] == 77 || tabStock[i][j] == 88 || tabStock[i][j] == 99)
            {
                tabTransforme[a][0] = tabTransforme[a][0] + 5;
            }
            else if(tabStock[i][j] == 55)
            {
                tabTransforme[a][0] = tabTransforme[a][0] + 7;
            }
            else if(tabStock[i][j] == 0)
            {
                tabTransforme[a][0] = tabTransforme[a][0] + 0;
            }
            else
            {
                tabTransforme[a][0] = tabTransforme[a][0] + 1;
            }
        }
    }
}

