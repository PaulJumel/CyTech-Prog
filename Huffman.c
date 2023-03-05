#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int X = 0;


typedef struct huffman{ // notre structure huffman
	char car; //caractère
	int nbOcc; // nombre d'occurence
	int nbBit; //nombre de bits
	int bit; // la valeur du bit
	struct huffman* fd;
	struct huffman* fg;
	}Huff;
typedef Huff* PHuff;


typedef struct node{
	PHuff huff;
	struct node* suivant;
}Node;
typedef Node* PNode;

typedef struct lst{
	PNode premier;
}Liste;
typedef Liste* PListe;



PHuff creerHuff(char c) //permet d'initialiser une structure huff
{
	PHuff a = malloc(sizeof(Huff));
	if(a == NULL) {
	    fprintf(stderr, "ERREUR ALLOCATION MEMOIRE");
	    exit(1);
	    }
	a->car = c;
	a->nbOcc = 1;
	a->nbBit = 8;
	a->bit = 0;
	a->fd = NULL;
	a->fg = NULL;
	return a;
}

int estFeuille(PHuff a) {     //Renvoie 1 si le noeud est une feuille, 0 sinon
	return !(a->fg || a->fd);
}

int lettreOccu(PHuff tab[], PHuff Huff, char *nomDuFichier){    //Permet de rentrer le nombre d'occurence de chaque caractèrere du fichier texte dans un tableau
    FILE* fichier = NULL;
    fichier = fopen(nomDuFichier, "r");

    int i;
    int x = 0;
    int v = 0;
    PHuff Huff1;
    int caracAtcuel;

    if (fichier != NULL)
    {
		while((caracAtcuel = fgetc(fichier)) != EOF){ // On parcour le fichier
			v = 0;
            for(i=0;i<x;i++)
            {
                if (tab[i]->car == caracAtcuel) // Dès que l'on rencontre un caractère déjà vu, on incrémente le nombre d'occurrence.
                {
                    tab[i]->nbOcc = tab[i]->nbOcc + 1;
                    v=1;
                }
            }
            if ( v == 0) // Sinon on crée la case du tableau pour la nouvelle lettre
            {
                Huff1 = creerHuff(caracAtcuel);
                tab[x] = Huff1;
                x++;
            }
        }
    }
    fclose(fichier);

    return x;
}

void affTab(PHuff tab[],int x)   //affiche le tableau Huff jusqu'à x
{
    int i;
    for(i=0;i<x;i++)
    {
        printf("caractere: %c, nb d'occurrence: %d, nb bits: %d, bit: %d\n", tab[i]->car,tab[i]->nbOcc,tab[i]->nbBit,tab[i]->bit);
    }
}


void trierHuff(PHuff tab[],int x)  // trie le tableau huff dans l'ordre décroissant , x représente le nombre de cases du tableau soit le nombre de caractère différent
{
	int posmin;
	PHuff temp;
	int i, j;

	for (i=0; i<255; i++) {
		posmin = i;
		for (j=i+1; j<x; j++) {
			if (tab[j]->nbOcc > tab[posmin]->nbOcc) { // si le nbr occurence du moment est inférieur au suivant alors posmin = j, puis on interverti les positions.
				posmin = j ;
			}
		}
		if (posmin != i) { // donc si le tableau n'est pas bien ordonné posmin est différent de i, alors on interverti les positions.
			temp = tab[posmin];
			tab[posmin] = tab[i];
			tab[i] = temp;
		}
	}
}

PListe initialisation()     //initialise la liste
{
    PListe liste = malloc(sizeof(liste));
    PNode element = malloc(sizeof(element));
    PHuff huff1 = creerHuff (0);

    if (liste == NULL || element == NULL)
    {
        exit(EXIT_FAILURE);
    }
	element->huff=huff1;
    element->huff->nbOcc = 0;

    element->suivant = NULL;
    liste->premier = element;

    return liste;
}

PListe insertion(PListe liste, PHuff nv)  //insert dans la liste
{
    PNode nouveau = malloc(sizeof(nouveau));
    if (liste == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }
    nouveau->huff = nv;
    nouveau->suivant = liste->premier;
    liste->premier = nouveau;
    return liste;
}

void supprimeFinSNC(PListe liste) {   //supprime 0 dans le cas ou il s'agit du dernier caractère de la liste, cette fonction est utilisé dans removefirst pour cet unique cas
	if(liste->premier != NULL) {
		PNode l = liste->premier;
		while(l->suivant->suivant != NULL) {
			l = l->suivant;
		}
		PNode p = l->suivant;
		l->suivant = NULL;
		free(p);
	}

}

void removefirst(PListe liste, int nbr) //supprime la premère apparition d'un nombre
{
    int occurrence = 0;
    PNode actuel = liste->premier;
    if (actuel->huff->nbOcc == nbr)
    {
        PNode tmp = actuel;
        liste->premier = actuel->suivant ;
        free(tmp);
    }
    else
    {
		while (actuel->suivant != NULL )
		{
			if (actuel->suivant->huff->nbOcc == nbr)
			{
				occurrence++;
				if (occurrence == 1)
				{
					PNode p2 = actuel->suivant;
					actuel->suivant = actuel->suivant->suivant ;
					free(p2);
				}
			}
			if (actuel->suivant != NULL)
			{
				actuel= actuel->suivant;
			}
		}
		if (actuel->huff->nbOcc == nbr) // cas où le nombre est à la fin
		{
			supprimeFinSNC(liste);
		}
    }
}


PListe insertionListe(PListe liste, PHuff tab[], int x) // insère le tableau de Huff dans la liste
{
	int i;
	for(i=0;i<x;i++)
	{
		insertion(liste, tab[i]); //insère tous les huff du tableau dans la liste
	}
	removefirst(liste, 0); //supprime le 0 créé automatiquement par l'initialisation de la liste
	return liste;
}


void afficherListe(PListe liste)  //utilisé pour debuger
{
    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    PNode actuel = liste->premier;

    while (actuel != NULL)
    {
        printf("%c:%d -> ",actuel->huff->car, actuel->huff->nbOcc);
        actuel = actuel->suivant;
    }
    printf("NULL\n");
}



PHuff creerNoeud (PHuff a, PHuff b){ // crée un noeud interne avec deux noeuds (les premiers de la liste)
	PHuff somme = creerHuff (0);
	somme->nbOcc = a->nbOcc + b->nbOcc;
	if (a->nbOcc > b->nbOcc){
		somme->fg = b;
		somme->fd = a;
	}
	else{
		somme->fg = a;
		somme->fd = b;
	}
	somme->car = '0';
	return somme;
}

PListe insertSomme (PListe liste){ // insère le noeud nouvellement créé dans la liste
	PNode actuel = liste->premier;
	PHuff somme = creerNoeud (actuel->huff,actuel->suivant->huff);
	while (actuel->suivant!=NULL){
		if (somme->nbOcc > actuel->suivant->huff->nbOcc){
		actuel=actuel->suivant; // on défile la liste jusqu'à insérer la somme au bon endroit
		}

		else{
			       PNode nouveau = malloc(sizeof(nouveau));
    if (liste == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }
    nouveau->huff=somme;
    nouveau->suivant=actuel->suivant; //on insère la somme
    actuel->suivant=nouveau;
	return liste;
        }

	}
	PNode nouveau = malloc(sizeof(nouveau));
    if (liste == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }
    nouveau->huff=somme;
    nouveau->suivant=actuel->suivant;
    actuel->suivant=nouveau;

	return liste;
}

PListe supprimeDeux (PListe liste){ //supprime les deux premiers noeuds de la liste
	PNode actuel = liste-> premier;
	liste->premier=actuel->suivant->suivant;
	free(actuel->suivant);
	free(actuel);

	return liste;
}

PListe ajusteListe (PListe liste) //créé l'arbre à partir de la liste
{
	while(liste->premier->suivant!=NULL){
		insertSomme (liste);
		supprimeDeux (liste);
	}
	return liste;
}

int estVide(PHuff a) {
	return (a == NULL);
}


void valBit(PHuff a, int h, int bit) // attribue à chaque noeud sa valeur en bit et son nombre de bits grâce à un parcours préfixe
{
	if (!estVide(a)){
		a->nbBit=h;
		a->bit=bit;
		valBit(a->fg,h+1,bit*2);
		valBit(a->fd,h+1,(bit*2)+1);
    }
}

void convert (int n, int result, int i, int h, PHuff tab2[], char a) //convertit valbit en binaire
{
	PHuff Huff1;
	int q = n/2; // quotient
	h = h - 1;
	int count = 0; // compteur
	int resteadd = n%2;
	while (count < i){ // pour pouvoir ajouter le 1 au nombre, on regarde à quel rang l'ajouter avec 'i'
		resteadd = resteadd*10;

		count++;
	}
	result = result + resteadd; // on ajoute le chiffre au reste
	i++; // on idente les tours


	if (q != 0)
		convert(q,result,i,h, tab2, a); // on recommence si le quotient n'est toujours pas égal à 0

	if (q == 0){
        Huff1 = creerHuff(a);
        tab2[X] = Huff1;
        tab2[X]->nbBit = h;      //nbBit vaut désormais le nombre de 0 avant le premier 1 en binaire
        tab2[X]->bit = result;   //bit vaut maintenant la conversion de  base 10 en base 2
	}
}



void convertTout(PHuff a, PHuff tab2[]) //réalise un parcours préfixe de l'arbre pour convertir dans un deuxieme tableau les valeur h et bit.
{
    if(!estVide(a)) {
        if(a->car != '0'){
            convert(a->bit,0,0,a->nbBit,tab2, a->car);
            X++;
        }
        convertTout(a->fg, tab2);
        convertTout(a->fd, tab2);
    }
}

int comptNbCar(char *nomDuFichier) // compte le nombre de caractère dans le texte
{
	FILE *fichier = NULL;
    fichier = fopen(nomDuFichier, "r");
    int caracAtcuel;
    int n = 0;
    while((caracAtcuel = fgetc(fichier)) != EOF){
		n++;
	}
	return n;
}

void creerFichierComp(PHuff tab2[], PHuff tab[], char *nomDuFichier) // créé le fichier compressé
{
    FILE *fichier = NULL;
    fichier = fopen(nomDuFichier, "r");
    int caracAtcuel;
    int i;
    int n = comptNbCar(nomDuFichier);

    FILE *P_FICHIER;
    char NOM_FICHIER[30];
    printf("Entrez le nom du fichier a creer : ");
    scanf("%s", NOM_FICHIER);
    P_FICHIER = fopen(NOM_FICHIER, "w");  /* write */
    if (fichier != NULL)
    {
		fprintf(P_FICHIER, "%d\n", n);  //Ecrit le nombre de caractère du fichier à compresser
		fprintf(P_FICHIER, "%d\n", X);  //Ecrit le nombre de caractère différent
		for(i=0;i<X;i++)
		{
			fprintf(P_FICHIER, "%d-nbOcc:%d-nbBit:%d-bit:%d\n", tab[i]->car,tab[i]->nbOcc,tab[i]->nbBit,tab[i]->bit);  //Ecrit le nombre d'occurrence des caractères, sur combien de bits ils sont codées et la valeur du bit
		}
		while((caracAtcuel = fgetc(fichier)) != EOF){  //On parcoure le fichier compresser
            for(i=0;i<X;i++)          // Permet de retrouver le caractère dans notre tab2
            {
                if(caracAtcuel == tab2[i]->car)  // Quand on trouvve on écrit les 0 significatif grâce à la variable h, puis on on écrit la valeur de bit (exemple avec h = 2 et bit = 101, cela nous donne 00101)
                {
                    int h = tab2[i]->nbBit;
                    while(h != 0)
                    {
                        fprintf(P_FICHIER, "0");
                        h--;
                    }
                    fprintf(P_FICHIER, "%d", tab2[i]->bit);
                }
            }
		}
    }
    fclose(P_FICHIER);
    fclose(fichier);
}

int creertab3(PHuff tab3[], char *nomDuFichier2)   // créé un tableau avec le nombre d'occurence des caractères
{
	 FILE *fichier = NULL;
	 fichier = fopen(nomDuFichier2, "r");
	 int recupNbLettre;
	 int recupNbLettreUnique;
	 int i,x,y,z,w;

	 fscanf(fichier,"%d", &recupNbLettre);
	 fscanf(fichier,"%d", &recupNbLettreUnique);

	 for(i=0;i<recupNbLettreUnique;i++)
	 {
		tab3[i] = creerHuff('\0');
		fscanf(fichier,"%d-nbOcc:%d-nbBit:%d-bit:%d\n",&x,&y,&z,&w);
		tab3[i]->car = x;
		tab3[i]->nbOcc = y;

	}
	fclose(fichier);
	return recupNbLettreUnique;
}



void decompresser(PListe liste, char *nomDuFichier2) // la fonction décompresse
{
	FILE *fichier = NULL;
	fichier = fopen(nomDuFichier2, "r");

	FILE *P_FICHIER; // pointeur sur FILE
    char NOM_FICHIER[30];
    printf("Entrez le nom du fichier a creer : ");
    scanf("%s", NOM_FICHIER);
    P_FICHIER = fopen(NOM_FICHIER, "w");  /* write */


	int recupNbLettre;
	int recupNbLettreUnique;
	int i,y,x,z,w;
	int ecritfichier =0;
	PHuff a = liste->premier->huff;
	fscanf(fichier,"%d", &recupNbLettre);
	fscanf(fichier,"%d", &recupNbLettreUnique);

	for(i=0;i<recupNbLettreUnique;i++)
	{
		fscanf(fichier,"%d-nbOcc:%d-nbBit:%d-bit:%d\n", &x,&y,&z,&w);       //on passe les affichages "pratiques" du début du fichier
	}
	int recupNombre;
	while((recupNombre = fgetc(fichier)) != EOF) //recupNombre avance dans le texte à chaque répétition de la boucle et lit le caractère (0 ou 1)
	{

		if (ecritfichier==0){
			if(recupNombre == 48){  //Si le caractère lu est 0, on descend à gauche dans l'arbre
			a = a->fg;
				}
			else if (recupNombre == 49){ //Si c'est 1, on va à droite
			a = a->fd;
			}
			if(estFeuille(a)){    //Lorsqu'on arrive sur une feuille, on écrit dans le nouveau fichier le caractère contenu dans la feuille
				fprintf(P_FICHIER, "%c", a->car);
				ecritfichier =1;
			}
		}
		if(ecritfichier == 1){  //si on vient d'écrire dans le fichier, on remonte en haut de l'arbre
			ecritfichier = 0;
			a = liste->premier->huff;
		}
	}
}


int main(int argc, char *argv[])
{
    int choix = 0;

    printf ("=== Accueil ===\n\n");
    printf (" Tapez 1 si vous voulez compresser.\n");
    printf (" Tapez 2 si vous voulez decompresser.\n");
    printf (" Tapez 3 si vous voulez voir le manuel.\n");
    printf (" Entrez votre choix: ");
    scanf ("%d", &choix);

	switch (choix) {
		case 1 :
        printf ("\nVous avez choisi de compresser\n");
        char nomDuFichier1[30];
        printf ("Quel est le nom de votre fichier a compresser: ");
        scanf ("%s", nomDuFichier1);
        PHuff tab[255] = {0};
        PHuff Huff;
        Huff = creerHuff('c');
        int x = lettreOccu(tab, Huff, nomDuFichier1);
        trierHuff(tab, x);
        PListe liste = initialisation();
        liste = insertionListe(liste, tab, x);
        ajusteListe(liste);
        valBit(liste->premier->huff,0,0);
        PHuff tab2[255] = {0};
        convertTout(liste->premier->huff, tab2);
        creerFichierComp(tab2, tab, nomDuFichier1);
        break;

        case 2 :
        printf ("\nVous avez choisi de decompresser\n");
        char nomDuFichier2[30];
        printf ("Quel est le nom de votre fichier a decompresser: ");
	    	scanf ("%s", nomDuFichier2);
		    PHuff tab3[255] = {0};
        int recupNbLettreUnique = creertab3(tab3, nomDuFichier2);
        PListe liste2 = initialisation();
        liste2 = insertionListe(liste2, tab3, recupNbLettreUnique);
        ajusteListe(liste2);
        decompresser(liste2, nomDuFichier2);
        break;

        case 3 :
        printf("Vous etes dans le manuel d'emploi");
        printf("Pour utiliser les fonctionnalites compressees et decompressees,\nil faut que les fichiers soient dans le meme dossier, sous le format txt et sans accent.\n");
        printf("Quand on vous demande de rentrer le nom du fichier a compresser il faut bien rentrer le format du fichier.");
        printf("\nPar exemple: test.txt");
        break;

        default :
            printf("Votre choix n'est pas valable. Veuillez réessayer s'il vous plait.");
        break;
        }
    return 0;
}
