#include <stdio.h>
#include <stdlib.h>
#include <avalam.h>
#include <topologie.h>

#define PSEUDO_PAR_DEFAUT_J1 "J1"
#define PSEUDO_PAR_DEFAUT_J2 "J2"

typedef struct  //definie la structure d'un joueur
{
    int trait;
    char pseudo[20];  //pseudo de 20 caractères max
} T_joueur;

int coup(T_Position *p);


int main() {  // Point d'entré du programme

    T_joueur joueur1 = {1, PSEUDO_PAR_DEFAUT_J1};  //   / Création des joueurs et initialisation aux valeurs par défaut
    T_joueur joueur2 = {2, PSEUDO_PAR_DEFAUT_J2};  //  |

    T_Position p = getPositionInitiale();  // On récupére la position initiale du plateau
    T_ListeCoups l = getCoupsLegaux(p);


    printf("Nom Joueur 1: %s   -   Trait: %s\n", joueur1.pseudo, COLNAME(joueur1.trait));
    printf("Nom Joueur 2: %s   -   Trait: %s\n", joueur2.pseudo, COLNAME(joueur2.trait));


	printf("Depuis la position initiale du jeu, il y a %d coups possibles\n", l.nb);
	printf("Depuis la position initiale du jeu, le trait est aux %ss\n", COLNAME(p.trait));
    coup(&p);
    return 0;
}

int coup(T_Position *p){
    T_ListeCoups listecoup = getCoupsLegaux(*p);
    int depart, fin;
    printf("Quel pion souhaitez vous prendre ? ");
    scanf("%d", &depart);
    printf("Où souhaitez vous le poser ? ");
    scanf("%d", &fin);    
    if (estValide(*p, depart, fin)) {
        jouerCoup(*p, depart, fin);
        return 1;
    }
    else return coup(p);
}
