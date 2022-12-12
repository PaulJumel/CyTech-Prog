#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "Struct.h"
#include "fonction.h"

Processus creationProcessus()  // Fonction qu'on appelle à chaque nouveau processus créé
{
    Processus processus;
    printf("Quel est le nom du processus ? ");
    scanf("%s", processus.nom);
    printf("Quel est la duree du processus ? ");
    scanf("%d", &processus.duree);
    printf("Quel est la priorite du processus ? ");
    scanf("%d", &processus.priorite);
    return processus;
}

Liste *initialisation()  // On initialise la file de l'ordennanceur avec le premier processus
{
    Liste *liste = malloc(sizeof(*liste));
    Ordennanceur *Ordennanceur = malloc(sizeof(*Ordennanceur));

    if (liste == NULL || Ordennanceur == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Ordennanceur->processus = creationProcessus();
    Ordennanceur->suivant = NULL;
    liste->premier = Ordennanceur;

    return liste;
}


void ajout_bout_file(Liste *liste, Processus processus)    // Fonction appellé dans ajout_activ qui permet de mettre le processus au bout de la file
{
    Ordennanceur *nouveau = malloc(sizeof(*nouveau));
    Ordennanceur *actuel = liste->premier;
    Ordennanceur *tmp;

    nouveau->processus = processus;

    while(actuel->suivant != NULL)
    {
        actuel = actuel->suivant;
    }

    tmp = actuel->suivant;
    actuel->suivant = nouveau;
    nouveau->suivant = tmp;
    free(tmp);
}

void ajout_activ(Liste *liste)   // Fonction qui ajoute les proceuus dans la file de manière trié en fonction de la priorité et de la durée du processus
{
    /* Création du nouvel élément */
    Ordennanceur *nouveau = malloc(sizeof(*nouveau));
    Ordennanceur *actuel = liste->premier;
    Ordennanceur *tmp;

    int occurence = 0;

    if (liste == NULL || nouveau == NULL)    
    {
        exit(EXIT_FAILURE);
    }

    nouveau->processus = creationProcessus();

    if (nouveau->processus.priorite <= actuel->processus.priorite && nouveau->processus.duree < actuel->processus.duree)    // On recherche où inserer le processus dans la file
    {
        nouveau->suivant = liste->premier;
        liste->premier = nouveau;
    }
    else
    {
        while(actuel->suivant != NULL)
        {
            if(nouveau->processus.priorite <= actuel->suivant->processus.priorite && nouveau->processus.duree < actuel->suivant->processus.duree) 
            {
                occurence++;
                if(occurence == 1)
                {
                tmp = actuel->suivant;
                actuel->suivant = nouveau;
                nouveau->suivant = tmp;
                tmp = NULL;
                free(tmp);
                }
            }
            if(actuel->suivant != NULL)
            {
                actuel = actuel->suivant;
            }
        }
        if(occurence == 0)
        {
            ajout_bout_file(liste, nouveau->processus);
        }
    } 
}

void step(Liste *liste)    // Permet de défiler la file
{
    Ordennanceur *aSupprimer;

    if (liste->premier == NULL)
    {
        printf("La file est vide");
        exit(EXIT_FAILURE);
    }
    
 
    aSupprimer = liste->premier;
    liste->premier = liste->premier->suivant;
    printf("\nNom du processus : %s", aSupprimer->processus.nom);
    printf("\nDuree du processus : %d s\n", aSupprimer->processus.duree);
    sleep(aSupprimer->processus.duree);   // On attend la durée du processus
    free(aSupprimer);
}

void run(Liste *liste)  // Permet de réitérer step
{
    while (liste->premier)
    {
        step(liste);
    }
}