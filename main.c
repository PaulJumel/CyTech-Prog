#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "Struct.h"
#include "fonction.h"


int main()
{
    int nbProcessus;
    int i=0;

    printf("Combien de processus avez-vous ? ");
    if (scanf("%d", &nbProcessus) == 1)
    {
        Liste *maListe = initialisation();

        for(i=0; i<nbProcessus-1; i++)   // On insére chaque processus dans la file
        {
             ajout_activ(maListe);   
        }

        run(maListe);     // On défile
        printf("\nLa file est vide\n");  
    } 
    else
        printf("Vous devez saisir un nombre !\n"); 

    return 0;
}