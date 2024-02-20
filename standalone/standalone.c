#include <stdio.h>
#include <stdlib.h>
#include <avalam.h>
#include <topologie.h>

#define PSEUDO_PAR_DEFAUT_J1 "J1"
#define PSEUDO_PAR_DEFAUT_J2 "J2"

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
    printf("\tbonusJ ? : ");
    scanf("%hhd", &(p.evolution.bonusJ));  // hhd plutot que d car on veut des octets
    printf("\tbonusR ? : ");
    scanf("%hhd", &(p.evolution.bonusR));
    printf("\tmalusJ ? : ");
    scanf("%hhd", &(p.evolution.malusJ));
    printf("\tmalusR ? : ");
    scanf("%hhd", &(p.evolution.malusR));

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