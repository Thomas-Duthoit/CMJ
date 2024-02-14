#include <stdio.h>
#include <stdlib.h>
#include <avalam.h>
#include <topologie.h>

typedef struct  //definie la structure d'un joueur
{
    T_Score score;  // définie le score du joueur 
    char pseudo[20];  //pseudo de 20 caractères max
} T_joueur;


int main() {  // Point d'entré du programme

    T_joueur joueur1;
    T_joueur joueur2;

    T_Position p = getPositionInitiale();  // On récupére la position initiale du plateau
    T_ListeCoups l = getCoupsLegaux(p);
	printf("Depuis la position initiale du jeu, il y a %d coups possibles\n", l.nb);

	printf("Depuis la position initiale du jeu, le trait est aux %ss\n", COLNAME(p.trait));
    return 0;
}