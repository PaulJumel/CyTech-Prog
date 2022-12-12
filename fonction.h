#ifndef FONCTION_H
#define FONCTION_H
#include "structure.h"
#include <stdio.h>


int compareDistance(const void *a, const void *b);
Logement initialiser(double k);
Logement calculeDistance(Logement app, Logement x, int i, Logement *tab);
Logement creationTab(FILE *fic, Logement x, Logement *tab);
void randomiser(Logement *tab);
void trieTab(Logement *tab);
void afficherTab(Logement *tab);
void calculeMoy(Logement *tab, double k, double moyenne, double somme);

#endif