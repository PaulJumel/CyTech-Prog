#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include"Fonctions_fin.h"

int fin(int **tabTransforme,int nbJoueur){

    int i,j;

    for(i=0; i<nbJoueur; i++){
        for(j=0;j<=0; j++){
            if(tabTransforme[i][j] >= 66)
                return 1;
        }
    }
    return 0;
}

int fin2(int **tabTransforme,int nbJoueur)
{
    int i, j;
    int a=1;

    for(i=0; i<nbJoueur; i++){
        for(j=0;j<=0; j++){
            if(tabTransforme[0][0]>tabTransforme[i][j]){
                a=i+1;
            }
        }
    }
    return a;
}
