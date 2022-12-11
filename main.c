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
    scanf("%d", &nbProcessus);

    Liste *maListe = initialisation();

    for(i=0; i<nbProcessus-1; i++)
    {
         ajout_activ(maListe);   
    }

    afficherListe(maListe);

    run(maListe);

    printf("La file est vide");    

    return 0;
}