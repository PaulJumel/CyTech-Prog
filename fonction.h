#ifndef FONCTION_H
#define FONCTION_H
#include "Struct.h"

Processus creationProcessus();
Liste *initialisation();
void afficherListe(Liste *liste);
void ajout_bout_file(Liste *liste, Processus processus);
void ajout_activ(Liste *liste);
void step(Liste *liste);
void run(Liste *liste);

#endif