#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Fonction_deroulement.h"
#include "Random.h"
#include "fonction_test.h"
#include "fonctions_tri.h"
#include "fonction_initialiser.h"
#include "fonction_afficher.h"
#include "Remplir.h"
#include "Fonctions_transformer.h"
#include "Fonctions_Stock.h"
#include "Fonction_IA.h"

#define clear() printf("\033[H\033[J")

void distribution(int** tabJoueur, int MAX, int MIN, int nbJoueur)
{
    int i,j;
    int a;
    int b;
    for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            while(tabJoueur[i][j] == 0) {
                a = nbRandom(MAX, MIN);
                b = test(tabJoueur, a);
                if(b == 1)
                tabJoueur[i][j] = a;
            }
        }
    }
    tri_selection(tabJoueur, nbJoueur);
}


void choisirCarte(int** tabJoueur, int** tabTransforme, int* tabDeck, int* tabDeck2, int nbJoueur, int board[4][5], int board2[4][5], int l, int c , int IA)
{
    int i,j;
    int joueur = 1;
    int carte;
    int deck = 0;
    int carte_IA;
    int confirm = 0;
    iniTabDeck(tabDeck, nbJoueur);
    iniTabDeck(tabDeck2, nbJoueur);
    for(i=0;i<nbJoueur-IA;i++)
    {
        printf("Joueur %d, tapez 1 si vous etes la: ", joueur);
        scanf("%d", &confirm);
        while(confirm != 1){
        printf("Joueur 1 tapez 1: ");
        scanf("%d", &confirm);
        }
        clear();
        if(confirm == 1){
        printf("--------Joueur %d--------\nVoici vos cartes :\n", joueur);
        afficherDeck(tabJoueur, deck);
        printf("\nVoici vos points : %d\n\n", tabTransforme[joueur-1][0]);
        printf("Voici le board :\n");
        afficherBoard(board, l, c);
        printf("Veuillez choisir une carte parmi les votres : ");
        scanf("%d", &carte);
        tabDeck[i] = testValide(tabJoueur, deck, carte);
        tabDeck2[i] = tabDeck[i];
        remplacer(tabJoueur, tabDeck, deck, i);

        deck++;
        joueur++;
        clear();
        }
    }

    for(i=nbJoueur-IA;i<nbJoueur;i++)
    {
    carte_IA = choisirCarte_IA(tabJoueur, nbJoueur, board, board2, l, c, i);
    printf("%d", carte_IA);
    tabDeck[i] = carte_IA;
    tabDeck2[i] = tabDeck[i];
    remplacer(tabJoueur, tabDeck, i, i);
    }

    tri_Deck(tabDeck, nbJoueur);
}


void remplirBoard(int* tabDeck, int* tabDeck2, int* tabBoard, int* tabCompt, int** tabStock, int** tabTransforme, int board[4][5], int board2[4][5],  int l, int c, int nbJoueur, int IA)
{
    int i,j,k, p;
    int a;
    int b;
    int valeurPrise;
    int valLigne;
    int valColonne;
    for(k=0;k<nbJoueur;k++)
    {
        a = 0;
        p = 0;
        iniTabDeck(tabBoard, p);
        valLigne = 0;
        valColonne = 0;
        iniTabJoueur(tabStock, nbJoueur, 5);
        duplique(board,board2,l,c);

        for(i=0;i<l;i++)
        {
            for(j=0;j<c;j++)
            {
                if(tabDeck[k] > board2[i][j] && board2[i][j] != 0) {
                    tabBoard[p] = board2[i][j];
                    p++;
                    a = 1;
                }
            }
        }

        tri_Deck(tabBoard, p);
        for(i=0;i<l;i++)
        {
            for(j=0;j<c;j++)
            {
                if(tabBoard[p-1] == board2[i][j]) {
                    valLigne = i;
                    valColonne = j;
                }
            }
        }

        if(a == 0) {
            b = stock(tabDeck2, nbJoueur);
            if(b > nbJoueur-IA)
            {
                point_ligne(tabCompt, board, l, c);
                valeurPrise = stock(tabCompt, nbJoueur)-1;
                for(i = valeurPrise; i<= valeurPrise;i++)
                {
                    for(j=0;j<c;j++)
                    {
                        tabStock[stock(tabDeck2, nbJoueur)-1][j] = board[i][j];
                        board[i][j] = 0;
                    }
                    board[valeurPrise][0] = tabDeck[k];
                }
                transforme(tabStock, tabTransforme, tabDeck2, nbJoueur);
            }
            else {
                afficherBoard(board, l, c);
                printf("\nJoueur %d : Veuillez choisir une ligne a prendre : ", stock(tabDeck2, nbJoueur));
                scanf("%d", &valeurPrise);
                for(i = valeurPrise; i<= valeurPrise;i++)
                {
                    for(j=0;j<c;j++)
                    {
                        tabStock[stock(tabDeck2, nbJoueur)-1][j] = board[i][j];
                        board[i][j] = 0;
                    }
                    board[valeurPrise][0] = tabDeck[k];
                }
                transforme(tabStock, tabTransforme, tabDeck2, nbJoueur);
            }
        }

        else if(valColonne == 4) {
            for(i=valLigne;i<=valLigne;i++)
            {
                for(j=0;j<c;j++)
                {
                   tabStock[stock2(tabDeck2, tabDeck, nbJoueur, k)][j] = board[valLigne][j];
                }
            }
            for(i=valLigne;i<=valLigne;i++)
            {
                for(j=1;j<c;j++)
                {
                   board[valLigne][j] = 0;
                }
            }
            board[valLigne][0] = tabDeck[k];
            afficherTableau(tabStock, nbJoueur, 5);
            transforme2(tabStock, tabTransforme, tabDeck2, tabDeck, nbJoueur, k);
        }

        else
        board[valLigne][valColonne+1] = tabDeck[k];
    }
}

