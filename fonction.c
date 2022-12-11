#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "Struct.h"
#include "fonction.h"

Processus creationProcessus()
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

Liste *initialisation()
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

void afficherListe(Liste *liste)
{
    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Ordennanceur *actuel = liste->premier;

    while (actuel != NULL)
    {
        printf("%s -> ", actuel->processus.nom);
        actuel = actuel->suivant;
    }
    printf("NULL\n");
}


void ajout_bout_file(Liste *liste, Processus processus)
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

void ajout_activ(Liste *liste)
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

    if (nouveau->processus.priorite < actuel->processus.priorite && nouveau->processus.duree < actuel->processus.duree)
    {
        nouveau->suivant = liste->premier;
        liste->premier = nouveau;
    }
    else
    {
        while(actuel->suivant != NULL)
        {
            if(nouveau->processus.priorite < actuel->suivant->processus.priorite && nouveau->processus.duree < actuel->suivant->processus.duree) 
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

void step(Liste *liste)
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
    sleep(aSupprimer->processus.duree);
    free(aSupprimer);
}

void run(Liste *liste)
{
    while (liste->premier)
    {
        step(liste);
    }
}