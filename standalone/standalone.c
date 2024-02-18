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
void coupV2(T_Position *p);


int main() {  // Point d'entré du programme

    T_joueur joueur1 = {1, PSEUDO_PAR_DEFAUT_J1};  //   / Création des joueurs et initialisation aux valeurs par défaut
    T_joueur joueur2 = {2, PSEUDO_PAR_DEFAUT_J2};  //  |

    T_Position p = getPositionInitiale();  // On récupére la position initiale du plateau
    T_ListeCoups l = getCoupsLegaux(p);
    T_Score s = {0, 0, 0, 0};  // Par défaut, les scores sont de 0 pour chaque joueurs


    // TODO: retirer après les tests
    T_Coup coup_auto = l.coups[0];


    int joue = 1;  // booléen pour savoir si on joue ou non

    printf("----- A V A L A M   P A R   L A   T E A M   A V A L P I E R R E -----\n\n");


    printf("Nom Joueur 1: %s   -   Trait: %s\n", joueur1.pseudo, COLNAME(joueur1.trait));
    printf("Nom Joueur 2: %s   -   Trait: %s\n", joueur2.pseudo, COLNAME(joueur2.trait));


	printf("Depuis la position initiale du jeu, il y a %d coups possibles\n", l.nb);
	printf("Depuis la position initiale du jeu, le trait est aux %ss\n", COLNAME(p.trait));
    printf("Score actuel: ");
    afficherScore(s);
    // printf("\nListe des coups possibles:\n");
    // afficherListeCoups(l);
    // coup(&p);
    
    while (joue)
    {
        /*
        // -------------------------- //
        // MODE MANUEL
        printf("Position actuelle:\n");
        afficherPosition(p);  // affichage de l'état actuel du plateau
        coupV2(&p);  // Saisie du coup pour l'utilisateur
        // -------------------------- //
        */
        // -------------------------- //
        // MODE AUTOMATIQUE (on joue le premier coup légal automatiquement) aka STUPIDO_BOT
        printf("Coups légaux: %d\n", l.nb);
        coup_auto = l.coups[0];
        p = jouerCoup(p, coup_auto.origine, coup_auto.destination);
        // -------------------------- //
        s = evaluerScore(p);
        printf("Score actuel: ");
        afficherScore(s);
        l = getCoupsLegaux(p);
        if (l.nb == 0) {
            // Plus de coups légaux à jouer -> fin de la partie
            joue = 0;
        }
    }
    printf("\n\n----- F I N   D E   L A   P A R T I E -----\n\n");
    printf("Score final: ") ;
    afficherScore(s);
    if (s.nbJ > s.nbR) printf("%s a gagné !\n", joueur1.pseudo);
    else if (s.nbJ < s.nbR) printf("%s a gagné !\n", joueur2.pseudo);
    else if (s.nbJ == s.nbR) {
        if (s.nbJ5 > s.nbR5) printf("%s a gagné !\n", joueur1.pseudo);
        else if (s.nbJ5 < s.nbR5) printf("%s a gagné !\n", joueur2.pseudo);
        else printf("Egalité entre les deux joueurs !\n");
    }
    return 0;
}


void coupV2(T_Position *p) {
    int depart, fin;
    printf("Quel pile souhaitez vous utiliser ? [-1 pour afficher tous les coups légaux possibles] ");
    scanf("%d", &depart);
    if (depart == -1) {
        printf("Coups légaux:\n");
        afficherListeCoups(getCoupsLegaux(*p));
        printf("Quel pile souhaitez vous utiliser ? ");
        scanf("%d", &depart);
    } else {
        printf("Voisins de la case '%d': ", depart);
        listerVoisins(depart);
    }
    
    printf("Où souhaitez vous la poser ? ");
    scanf("%d", &fin);  
    if (estValide(*p, depart, fin)) *p = jouerCoup(*p, depart, fin);
    else coupV2(p);
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