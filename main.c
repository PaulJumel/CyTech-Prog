#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "fonction.h"

int main ()
{
    Logement tab[7917]; // le tableau des logements

    double k = 0;
    double moyenne = 0;
    double somme = 0;

    printf ("Avec combien de logement voulez-vous comparer le votre ?\n");
    scanf("%lf", &k);

    //intialiser le logement x
    Logement x = initialiser(k);

    //lire le fichier csv
    FILE  *fic = NULL;
    fic=fopen("airbnb_donnees_propre.csv","r");

    if (fic != NULL)
    {
        creationTab(fic, x, tab);
        fclose(fic);
        randomiser(tab);
        trieTab(tab);
        afficherTab(tab);
        calculeMoy(tab, k, moyenne, somme);
    }
    else
    {
        printf("error");
        exit(1);
    }
}