#ifndef FONCTION_IA_H
#define FONCTION_IA_H

int choisirCarte_IA(int** tabJoueur, int nbJoueur, int board[4][5], int board2[4][5], int l, int c, int deckIA);
void point_ligne(int* tabCompt, int board[4][5], int l, int c);
int valeurPlusProche(int* tabStock2, int tabBoard2[4], int board2[4][5], int l, int c);

#endif
