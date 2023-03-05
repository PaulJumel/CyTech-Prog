#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Fonction_deroulement.h"
#include "Fonction_IA.h"
#include "Random.h"
#include "fonction_test.h"
#include "fonctions_tri.h"
#include "fonction_initialiser.h"
#include "fonction_afficher.h"
#include "Remplir.h"
#include "Fonctions_transformer.h"
#include "Fonctions_Stock.h"
#include "Fonctions_fin.h"

#define clear() printf("\033[H\033[J")


int main()
{
    srand(time(NULL));
    int MAX = 104, MIN = 1;
    int nbJoueur;
    int nbJoueurValide = 0;
    int IA = 0;
    int choix;
    int ContinuePartie;
    int back = 1;

    int *tabCompt = malloc(nbJoueur * sizeof(int));
    int *tabDeck = malloc(nbJoueur * sizeof(int));
    int *tabDeck2 = malloc(nbJoueur * sizeof(int));
    int *tabBoard = malloc(20 * sizeof(int));

    int board[4][5] = {{0,0,0,0,0},
                       {0,0,0,0,0},
                       {0,0,0,0,0},
                       {0,0,0,0,0}};
    int board2[4][5] = {{0,0,0,0,0},
                       {0,0,0,0,0},
                       {0,0,0,0,0},
                       {0,0,0,0,0}};
    int l=4;
    int c=5;
    int j;

    int **tabTransforme = malloc(nbJoueur * sizeof(int*));
    for(j=0;j<nbJoueur;j++)
    {
        tabTransforme[j] = malloc(1 * sizeof(int));
    }

    int **tabJoueur = malloc(nbJoueur * sizeof(int*));
    for(j=0;j<nbJoueur;j++)
    {
        tabJoueur[j] = malloc(10 * sizeof(int));
    }



    int **tabStock = malloc(nbJoueur * sizeof(int*));
    for(j=0;j<nbJoueur;j++)
    {
        tabStock[j] = malloc(5 * sizeof(int));
    }



    while(back == 1)
    {

    printf ("=== Accueil ===\n\n");
    printf (" Pret pour une partie ?\n");
    printf (" 1. Jouer\n");
    printf (" 2. Regle du jeu\n");
    printf (" 3. Quitter\n");
    scanf ("%d", &choix);

    switch (choix) {
        case 1 :
        printf (" Vous avez choisi de jouer au jeu, c'est parti.\n");
        do {
        printf("Indiquez le nombre joueur ?\n");
        scanf("%d", &nbJoueur);
        while(nbJoueur > 10){
        printf("Le nombre de joueur est trop eleve, veuillez choisir un nomnbre inferieur ou egale a 10: ");
        scanf("%d", &nbJoueur);
        }
        nbJoueurValide = 10 - nbJoueur;
        printf("Indiquez le nombre IA?\n");
        scanf("%d", &IA);
        while(IA > nbJoueurValide){
        printf("Le nombre d'IA est trop eleve, veuillez choisir un nomnbre inferieur ou egale a %d: ", nbJoueurValide);
        scanf("%d", &IA);
        }
        nbJoueur = nbJoueur + IA;
        clear();

        iniTabJoueur(tabJoueur, nbJoueur, 10);
        iniTabJoueur(tabTransforme, nbJoueur, 1);
        iniTabJoueur(tabStock, nbJoueur, 4);
        distribution(tabJoueur, MAX, MIN, nbJoueur);
        initboard(board, tabJoueur, l, c, MAX, MIN);

            int k;
            for(k=0; k<10; k++) {
                choisirCarte(tabJoueur, tabTransforme, tabDeck, tabDeck2, nbJoueur, board, board2, l, c, IA);
                remplirBoard(tabDeck, tabDeck2, tabBoard, tabCompt, tabStock, tabTransforme, board, board2, l, c, nbJoueur, IA);
                if(fin(tabTransforme, nbJoueur) == 1){
                    printf("Le joueur %d a gagne\n", fin2(tabTransforme, nbJoueur));
                }
                clear();
            }
            printf("Le joueur %d a gagne\n",fin2(tabTransforme,nbJoueur));
            for(k=0; k<nbJoueur; k++) {
                printf("Le joueur %d a %d points\n", k+1, *tabTransforme[k]);
                }
            printf ("Voulez vous faire une autre partie (0 pour non, 1 pour oui)? ");
            scanf ("%d", &ContinuePartie);
            } while (ContinuePartie);
        break;
        case 2 :
        printf (" Regle du jeu :\n\n");
        printf("1) Mise en jeu des cartes :\n\n");
        printf("Tous les joueurs prennent une carte de leur jeu pour la deposer face cachee devant eux sur la table.\nQuand tout le monde a pose, on retourne les cartes.\nCelui qui a depose la carte la plus faible est le premier a jouer. Il pose alors sa carte dans la rangee de son choix.\nPuis vient le tour de celui ayant pose la 2e carte la plus faible jusqu'a ce que tout le monde ait pose.\nLes cartes d'une serie sont toujours deposees les unes a cote des autres.\nRepeter ce processus jusqu'a ce que les 10 cartes de chaque joueur soient epuisaes.\n");
        printf("Disposition des cartes :\n\n");
        printf("Chaque carte jouee ne peut convenir qu'a une seule serie :\nValeurs croissantes : Les cartes d'une serie doivent toujours se succeder dans l'ordre croissant de leurs valeurs. On pose donc toujours une carte de plus forte valeur que la precedente.\nLa plus petite difference : Si vous avez le choix entre plusieurs series : sachez qu'une carte doit toujours etre deposee dans la serie ou la difference entre la derniere carte deposee et la nouvelle est la plus faible.\nExemple : Vous avez un 22 : Vous devrez le poser apres le 20 (difference de 2) et non apres le 17 (difference de 5).\n");
        printf("\n2) Encaissement des cartes\n\nSerie terminee : Lorsqu'une serie est terminee (qu'elle comporte 5 cartes) : Alors, le joueur qui joue dans l'une de ces series doit ramasser les 5 cartes de la serie (sauf celle qu'il a posee qui forme le debut d�une nouvelle serie).\nCarte trop faible : Si un joueur possede une carte si faible qu'elle ne peut entrer dans aucune des series, alors il doit ramasser toutes les cartes d'une serie de son choix. Sa carte faible represente alors la premiere carte d'une nouvelle serie. (La serie ramassee sera celle ayant le moins de TdB. Ces tetes sont des points negatifs en fin de partie).\n");
        printf("\n3) Precisions sur les Tetes de Boeufs:\n\nLes Tetes de Boeufs (TdB) sont des points negatifs (le joueur qui en possede le moins gagne la partie).\nChaque carte, en plus de sa valeur presente un ou plusieurs symboles TdB. Chaque symbole TdB = 1 point negatif.\nLes cartes :\n    Qui finissent par 5 possedent 2 TdB\n   Qui finissent par 0 possedent 3 TdB\n   Formant un doublet (11, 22, etc.) possedent 5 TdB.\nCarte 55 du Six qui prend :Le nombre 55 est a la fois un doublet et un nombre 5, cette carte contient donc 7 TdB ! (La pire carte du jeu)\nPile de TdB : Doit etre posee devant vous sur la table. Les cartes ramassees iront dans cette pile et NE SONT PAS integrees a votre main !\n");
        printf("Fin de manche:\n\nLorsque les joueurs ont joue leurs 10 cartes (ils n'ont plus de cartes en main), la manche prend fin.\nChaque joueur compte alors ses points negatifs dans sa pile de TdB.\nOn note le resultat de chaque joueur sur une feuille de papier et on commence une nouvelle manche.\nOn joue plusieurs manches jusqu'a ce que l un des joueurs ait reuni en tout plus de 66 tetes de b�uf. Le vainqueur de la partie est alors le joueur qui a le moins de tetes de b�uf.\nAvant le debut du jeu, il est bien sur possible de convenir d'un autre total de points ou d'un nombre de manches maximum.\n\n");

            printf("Voulez vous retourner a l'accueil ? si oui tapez 1: ");
            scanf("%d", &back);

        break;
        case 3 :
            back = 0;
            break;
        default :
            printf("Votre choix n'est pas valable. Veuillez reesayer s'il vous plait.");
            break;
        }
    }
    return 0;
}

