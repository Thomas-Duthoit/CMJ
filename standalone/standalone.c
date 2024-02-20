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

//int coup(T_Position *p);
void coupV2(T_Position *p);
void coupV3(T_Position *p);
int ecrireJSON(T_Position p);

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

    if (ecrireJSON(p)==0) {
        printf("erreur d'écriture du fichier json");
        return -1;
    }
    
    while (joue)
    {
        // MODE MANUEL
        system("clear");
        s = evaluerScore(p);
        afficherScore(s);
        
        printf("Trait aux %ss :\n", COLNAME(p.trait));

        // printf("Position actuelle:\n");
        // afficherPosition(p);  // affichage de l'état actuel du plateau
        coupV3(&p);  // Saisie du coup pour l'utilisateur
        ecrireJSON(p);

        
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


void coupV3(T_Position *p) {
    int depart, fin;
    printf("\tcaseO ? : ");
    scanf("%d", &depart);
    printf("\tcaseD ? : ");
    scanf("%d", &fin);  
    if (estValide(*p, depart, fin)) *p = jouerCoup(*p, depart, fin);
    else coupV3(p);
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
        printf("Voisins de la case '%d': ", depart);
        listerVoisins(depart);
    } else {
        printf("Voisins de la case '%d': ", depart);
        listerVoisins(depart);
    }
    
    printf("Où souhaitez vous la poser ? ");
    scanf("%d", &fin);  
    if (estValide(*p, depart, fin)) *p = jouerCoup(*p, depart, fin);
    else coupV2(p);
}



int ecrireJSON(T_Position p) {
    FILE *fichier;
    T_Score s = evaluerScore(p);
    int i;

    fichier = fopen("position.js", "w");
    if (fichier==NULL) return 0;
    // ecrire le json ici
    fprintf(fichier, "traiterJson({\n"); //  
    fprintf(fichier, "\t\"trait\":%d,\n", p.trait); // 

    fprintf(fichier, "\t\"scoreJ\":%d,\n", s.nbJ);  // Ecrit le score des jaunes
    fprintf(fichier, "\t\"scoreJ5\":%d,\n", s.nbJ5);  // Ecrit le nombre de colonnes 5 pieces des jaunes
    fprintf(fichier, "\t\"scoreR\":%d,\n", s.nbR);  // Eccrit le score des rouges
    fprintf(fichier, "\t\"scoreR5\":%d,\n", s.nbR5);  // Ecrit le nom de colonnes 5 pièces des rouges

    fprintf(fichier, "\t\"bonusJ\":%d,\n", p.evolution.bonusJ); // Ecrit la position du jeton evol Jaunes
    fprintf(fichier, "\t\"malusJ\":%d,\n", p.evolution.malusJ); //
    fprintf(fichier, "\t\"bonusR\":%d,\n", p.evolution.bonusR);
    fprintf(fichier, "\t\"malusR\":%d,\n", p.evolution.malusR);

    fprintf(fichier, "\t\"cols\":[\n");
    for (i = 0; i < NBCASES; i++)
    {
        fprintf(fichier, "\t\t{\"nb\":%d, \"couleur\":%d}", p.cols[i].nb, p.cols[i].couleur);
        if (i < NBCASES-1) fprintf(fichier, ",\n");
    }
    fprintf(fichier, "\n\t]\n");
    
    
    fprintf(fichier, "});");
    
    // fermer le fichier
    fclose(fichier);
    return 1;
}

// première version de la fonction pour jouer un coup (marche pas)
/*
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
*/