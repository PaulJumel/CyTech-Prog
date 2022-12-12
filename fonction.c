#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include "structure.h"

int compareDistance(const void *a, const void *b) //la fonction qu'on utilise dans qsort pour comparaer le tableau des logements en fonctions de la distance
{

    Logement *logA = (Logement *)a;
    Logement *logB = (Logement *)b;

    return logA->distance - logB->distance;
}


Logement initialiser(double k)
{
    Logement x;

    printf("entrer le nombre d'accomodates : \n");
    scanf("%lf", &x.accomadates);
    printf("entrer le nombre de bedrooms : \n");
    scanf("%lf", &x.bedrooms);
    printf("entrer le nombre de bathrooms :\n");
    scanf("%lf", &x.bathrooms);
    printf("entrer le nombre de beds : \n");
    scanf("%lf", &x.beds);
    printf("entrer le minimum nights : \n");
    scanf("%lf", &x.minimum_nights);
    printf("entrer le maximum nights : \n");
    scanf("%lf", &x.maximum_nights);
    printf("entrer le nombre of reviews : \n");
    scanf("%lf", &x.number_of_reviews);

    return x;
}

Logement calculeDistance(Logement app, Logement x, int i, Logement *tab)  // calculer la dsitance de chaque logement avec le logement x
{
    app.distance= sqrtf(pow(app.accomadates-x.accomadates,2)+pow(app.bedrooms-x.bedrooms,2)+pow(app.bathrooms-x.bathrooms,2)+pow(app.beds-x.beds,2)+pow(app.minimum_nights-x.minimum_nights,2)+pow(app.maximum_nights-x.maximum_nights,2)+pow(app.number_of_reviews-x.number_of_reviews,2));
    tab[i] = app;

    return tab[i];
}


Logement creationTab(FILE *fic, Logement x, Logement *tab)
{
    int i = 0;
    Logement app;

    //lire le fichier et crée le tableau
    char line [100];
    fgets(line, 100 , fic);
    for(i=0;i < 7917;i++)
    {
        fgets(line, 100, fic);
        app.log_nb = atof(strtok(line, ","));
        app.accomadates = atof(strtok(NULL, ","));
        app.bedrooms = atof(strtok(NULL, ","));
        app.bathrooms = atof(strtok(NULL, ","));
        app.beds = atof(strtok(NULL, ","));
        app.price = atof(strtok(NULL, ","));
        app.minimum_nights = atof(strtok(NULL, ","));
        app.maximum_nights = atof(strtok(NULL, ","));
        app.number_of_reviews = atof(strtok(NULL, ","));

        calculeDistance(app, x ,i, tab);
        
        //afficher toutes les informations des logements dans le tableau (non tri�)
        printf("hotel id = %lf  price = %lf distance = %.2f\n", tab[i].log_nb, tab[i].price, tab[i].distance);
    }
    return *tab;
}

void randomiser(Logement *tab)
{
    int nbAleatoire;
    Logement tmp;

    int nombre = 0;
    int MIN = 0;
    int MAX = 7916;

    srand(time(NULL));
    for(nbAleatoire=0;nbAleatoire<7916;nbAleatoire++)
    {
        nombre = (rand() % (MAX + 1 - MIN)) + MIN;
        tmp = tab[nbAleatoire];
        tab[nbAleatoire] = tab[nombre];
        tab[nombre] = tmp;
    }
}


void trieTab(Logement *tab)  // trier le tableau en fonction de la distance
{
    qsort(tab, 7916, sizeof(Logement), compareDistance);
}


void afficherTab(Logement *tab)
{
    for (int n = 0; n < 7916; n++) 
    {
        printf("hotel id = %lf  price = %lf distance = %.2f\n", tab[n].log_nb, tab[n].price, tab[n].distance);
    }
}

void calculeMoy(Logement *tab, double k, double moyenne, double somme)
{
    for (int j=0; j < k; j++)
    {
        somme += tab[j].price;
    }
    moyenne = somme / k;
    printf("\nle prix prédit pour votre logement : %lf\n",moyenne);
}