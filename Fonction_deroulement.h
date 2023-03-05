#ifndef FONCTION_DEROULEMENT_H
#define FONCTION_DEROULEMENT_H

void distribution(int** tabJoueur, int MAX, int MIN, int nbJoueur);
void choisirCarte(int** tabJoueur, int** tabTransforme, int* tabDeck, int* tabDeck2, int nbJoueur, int board[4][5], int board2[4][5], int l, int c , int IA);
void remplirBoard(int* tabDeck, int* tabDeck2, int* tabBoard, int* tabCompt, int** tabStock, int** tabTransforme, int board[4][5], int board2[4][5],  int l, int c, int nbJoueur, int IA);

#endif
