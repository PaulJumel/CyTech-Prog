#ifndef STRUCT_H
#define STRUCT_H

typedef struct 
{
    char nom[100];
    int duree;
    int priorite;
} Processus;

typedef struct Ordennanceur Ordennanceur;
struct Ordennanceur
{
    Processus processus;
    Ordennanceur *suivant;
};

typedef struct Liste Liste;
struct Liste
{
    Ordennanceur *premier;
};

#endif