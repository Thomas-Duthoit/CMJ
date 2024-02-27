#include <stdio.h>
#include <stdlib.h>
#include <avalam.h>
#include <topologie.h>

#define PSEUDO_PAR_DEFAUT_J1 "Jaunes"
#define PSEUDO_PAR_DEFAUT_J2 "Rouges"

#define CHEMIN_PAR_DEFAUT "./web/data/refresh-data.js"

typedef struct  //definie la structure d'un joueur
{
    int trait;
    char pseudo[20];  //pseudo de 20 caractères max
} T_joueur;

//int coup(T_Position *p);
//void coupV2(T_Position *p);
int coupV3(T_Position *p);
int ecrireJSON(T_Position p, char *chemin);

/*
TODO: finir le jeu: étape 1: le faire marcher, étape 2: s'ammuser
TODO: nom de fichiers avec argv/argc
TODO: check si les positions des jetons evolution sont valides
*/

int main(int argc, char *argv[]) {  // Point d'entré du programme

    T_joueur joueur1 = {1, PSEUDO_PAR_DEFAUT_J1};  //   / Création des joueurs et initialisation aux valeurs par défaut
    T_joueur joueur2 = {2, PSEUDO_PAR_DEFAUT_J2};  //  |

    T_Position p = getPositionInitiale();  // On récupére la position initiale du plateau
    T_ListeCoups l = getCoupsLegaux(p);
    T_Score s = {0, 0, 0, 0};  // Par défaut, les scores sont de 0 pour chaque joueurs
    

    if (argc == 1) printf("Utilisation du fichier %s\n", CHEMIN_PAR_DEFAUT);
    else printf("Utilisation du fichier %s\n", argv[1]);
    printf("Continuer ?");
    getchar();  // on attend que l'utilisateur appuie sur entré

    // bonus/malus:
    p.evolution.bonusJ = UNKNOWN;
    printf("%d\n", p.evolution.bonusJ%2);
    while (0 > p.evolution.bonusJ && p.evolution.bonusJ > NBCASES && (p.evolution.bonusJ)%2 == 1)
    {
        printf("\tbonusJ ? : ");
        scanf("%hhd", &(p.evolution.bonusJ));  // hhd plutot que d car on veut des octets
    }
    p.evolution.bonusR = UNKNOWN;
    printf("%d\n", p.evolution.bonusR%2);
    while (0 > p.evolution.bonusR && p.evolution.bonusR > NBCASES && (p.evolution.bonusR)%2)
    {
        printf("\tbonusR ? : ");
        scanf("%hhd", &(p.evolution.bonusR));
    }
    p.evolution.malusJ = UNKNOWN;
    printf("%d\n", p.evolution.malusJ%2);
    while (0 > p.evolution.malusJ && p.evolution.malusJ > NBCASES && !(p.evolution.malusJ)%2 && p.evolution.malusJ != p.evolution.bonusJ)
    {
        printf("\tmalusJ ? : ");
        scanf("%hhd", &(p.evolution.malusJ));
    }
    p.evolution.malusR = UNKNOWN;
    printf("%d\n", p.evolution.malusR%2);
    while (0 > p.evolution.malusR && p.evolution.malusR > NBCASES && (p.evolution.malusR)%2 && p.evolution.malusR != p.evolution.bonusR)
    {
        printf("\tmalusR ? : ");
        scanf("%hhd", &(p.evolution.malusR));
    }
    
    
    getchar();
    

    // on initialise le fichier json avant de commencer la partie 
    if (argc == 1) ecrireJSON(p, CHEMIN_PAR_DEFAUT);  
    else ecrireJSON(p, argv[1]);

    while (l.nb) // tant qu'il y a des coups légaux: on joue
    {
        system("clear");
        s = evaluerScore(p);
        afficherScore(s);
        printf("Trait aux %ss :\n", COLNAME(p.trait));
        while (coupV3(&p)) {
            system("clear");
            s = evaluerScore(p);
            afficherScore(s);
            printf("Trait aux %ss :\n", COLNAME(p.trait));
        }
        if (argc == 1) ecrireJSON(p, CHEMIN_PAR_DEFAUT);  
        else ecrireJSON(p, argv[1]);
        l = getCoupsLegaux(p);
    }
    printf("Partie finie !\nscore: ");
    afficherScore(s);
    if (s.nbJ > s.nbR) printf(" %s gagnent\n", joueur1.pseudo);
    else if (s.nbJ < s.nbR) printf(" %s gagnent\n", joueur2.pseudo);
    else if (s.nbJ == s.nbR) {
        if (s.nbJ5 > s.nbR5) printf(" %s gagnent\n", joueur1.pseudo);
        else if (s.nbJ5 < s.nbR5) printf(" %s gagnent\n", joueur2.pseudo);
        else printf("Egalité\n");
    }
    return 0;
}


int coupV3(T_Position *p) {
    int depart, fin;
    printf("\tcaseO ? : ");
    scanf("%d", &depart);
    printf("\tcaseD ? : ");
    scanf("%d", &fin);  
    if (estValide(*p, depart, fin)) *p = jouerCoup(*p, depart, fin);
    else return 1;
    return 0;
}


int ecrireJSON(T_Position p, char *chemin) {
    FILE *fichier;
    T_Score s = evaluerScore(p);
    int i;

    fichier = fopen(chemin, "w");
    if (fichier==NULL) return 0;
    fprintf(fichier, "traiterJson({\n");  // Initialisation du fichier JSON
    fprintf(fichier, "\t"STR_TURN":%d,\n", p.trait); // Trait (Savoir qui joue)

    fprintf(fichier, "\t"STR_SCORE_J":%d,\n", s.nbJ);  // Ecrit le score des jaunes
    fprintf(fichier, "\t"STR_SCORE_J5":%d,\n", s.nbJ5);  // Ecrit le nombre de colonnes 5 pieces des jaunes
    fprintf(fichier, "\t"STR_SCORE_R":%d,\n", s.nbR);  // Eccrit le score des rouges
    fprintf(fichier, "\t"STR_SCORE_R5":%d,\n", s.nbR5);  // Ecrit le nom de colonnes 5 pièces des rouges

    fprintf(fichier, "\t"STR_BONUS_J":%d,\n", p.evolution.bonusJ);  // Ecrit la position du jeton evol Jaunes
    fprintf(fichier, "\t"STR_MALUS_J":%d,\n", p.evolution.malusJ);  // Ecrit la position du jeton malus Jaunes
    fprintf(fichier, "\t"STR_BONUS_R":%d,\n", p.evolution.bonusR);  // Ecrit la position du jeton evol Rouges
    fprintf(fichier, "\t"STR_MALUS_R":%d,\n", p.evolution.malusR);  // Ecrit la position du jeton malus Rouges

    fprintf(fichier, "\t"STR_COLS":[\n");  // Ecrit l'état des colonnes
    for (i = 0; i < NBCASES; i++)
    {
        fprintf(fichier, "\t\t{"STR_NB":%d, "STR_COULEUR":%d}", p.cols[i].nb, p.cols[i].couleur);
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

/*
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
*/