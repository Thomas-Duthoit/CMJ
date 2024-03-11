#include <stdio.h>
#include <stdlib.h>
#include <avalam.h>
#include <topologie.h>

#define PSEUDO_PAR_DEFAUT_J1 "Jaunes"
#define PSEUDO_PAR_DEFAUT_J2 "Rouges"

#define CHEMIN_PAR_DEFAUT "./web/data/refresh-data.js"

typedef struct  // player structure
{
    int trait;
    char pseudo[21];  // pseudo variable (20 char max + '\0')
} T_Joueur;

// int coup(T_Position *p);
// void coupV2(T_Position *p);
int coupV3(T_Position *p);  // prototype for the last version of the function to move piles
int ecrireJSON(T_Position p, char *chemin);  // prototype of the function to write actual game state into a json file for avalam-refresh

int main(int argc, char *argv[]) {  // program entry point
    T_Joueur joueur1 = {1, PSEUDO_PAR_DEFAUT_J1};  //   / players creation
    T_Joueur joueur2 = {2, PSEUDO_PAR_DEFAUT_J2};  //  |

    T_Position p = getPositionInitiale();  // getting the initial game position
    T_ListeCoups l = getCoupsLegaux(p);  // and getting the list of legal moves from this position
    T_Score s = evaluerScore(p);  // and defining the score variable
    
    if (argc == 1) printf("Utilisation du fichier %s\n", CHEMIN_PAR_DEFAUT);  // if no path is specified, we use the default one
    else printf("Utilisation du fichier %s\n", argv[1]);  // else, we use the path specified as an argument
    printf("Continuer ?");
    getchar();  // we wait for the user to press 'enter' on his keyboard

    // initializing evolution bonus/malus to UNKNOWN:
    p.evolution.bonusJ = UNKNOWN;
    p.evolution.bonusR = UNKNOWN;    
    p.evolution.malusJ = UNKNOWN;
    p.evolution.malusR = UNKNOWN;

    // asking the players where they want to place their evolution pieces
    printf0("Demande aux joueurs où ils veulent placer leurs pièces d'évolution.\n");
    printf0("Demande au joueur jaune de placer le jeton bonus.\n");
    while (((0 <= p.evolution.bonusJ || p.evolution.bonusJ > NBCASES) && (p.evolution.bonusJ)%2 == 0) || p.evolution.bonusJ == UNKNOWN)
    {
        printf("\tbonusJ ? : ");
        scanf("%hhd", &(p.evolution.bonusJ));  // not %d but %hhd because we need bytes (warning and solution given by gcc)
    }        
    printf1("Le jeton bonus jaune a été placé à la case %hhd\n", p.evolution.bonusJ);
    printf0("Demande au joueur rouge de placer le jeton bonus.\n");
    while (((0 <= p.evolution.bonusR || p.evolution.bonusR > NBCASES) && (p.evolution.bonusR)%2) || p.evolution.bonusR == UNKNOWN)
    {
        printf("\tbonusR ? : ");
        scanf("%hhd", &(p.evolution.bonusR));  // not %d but %hhd because we need bytes (warning and solution given by gcc)
    }
    printf1("Le jeton bonus rouge a été placé à la case %hhd\n", p.evolution.bonusR);
    printf0("Demande au joueur jaune de placer le jeton malus.\n");
    while (((0 <= p.evolution.malusJ || p.evolution.malusJ > NBCASES) && (p.evolution.malusJ)%2 == 0) || p.evolution.malusJ == p.evolution.bonusJ || p.evolution.malusJ == UNKNOWN)
    {
        printf("\tmalusJ ? : ");
        scanf("%hhd", &(p.evolution.malusJ));  // not %d but %hhd because we need bytes (warning and solution given by gcc)
    }
    printf1("Le jeton malus jaune a été placé à la case %hhd\n", p.evolution.malusJ);
    printf0("Demande au joueur rouge de placer le jeton malus.\n");
    while (((0 <= p.evolution.malusR || p.evolution.malusR > NBCASES) && (p.evolution.malusR)%2) || p.evolution.malusR == p.evolution.bonusR || p.evolution.malusR == UNKNOWN)
    {
        printf("\tmalusR ? : ");
        scanf("%hhd", &(p.evolution.malusR));  // not %d but %hhd because we need bytes (warning and solution given by gcc)
    }
    printf1("Le jeton malus rouge a été placé à la case %hhd\n", p.evolution.malusR);
    // initializing the JSON file before we start the game so that avalam-refresh can display it
    printf0("Initialisation du fichier JSON...\n");
    if (argc == 1) ecrireJSON(p, CHEMIN_PAR_DEFAUT);  // if no path specified, we use the default one
    else ecrireJSON(p, argv[1]);  // else, we use the specified path

    // game loop:
    printf0("Début de la partie\n");
    while (l.nb)  // while there are legal moves, we play
    {
        system("clear");  // clearing the terminal
        s = evaluerScore(p);  // updating score from the position
        afficherScore(s);     // and displaying it
        printf("Trait aux %ss :\n", COLNAME(p.trait));  // telling which player needs to play
        while (coupV3(&p)) {  // while invalid moves are done  (coupV3 also apply move to position when the move is valid)
            system("clear");  // clearing the terminal
            s = evaluerScore(p);  // updating score
            afficherScore(s);     // to display it
            printf("Trait aux %ss :\n", COLNAME(p.trait));  // telling which player needs to play
        }
        printf("nb coups possibles : %d\n", l.nb);  // number of legal moves remaining
        // updating the JSON file after each move
        if (argc == 1) ecrireJSON(p, CHEMIN_PAR_DEFAUT);  // if no path specified, we use the default one
        else ecrireJSON(p, argv[1]);  // else, we use the specified path
        // updating the list of available legal moves
        l = getCoupsLegaux(p);
    }
    // the game is finished:
    printf("Partie finie !\nScore: ");
    afficherScore(s);  // displaying score
    if (s.nbJ > s.nbR) printf(" %s gagnent\n", joueur1.pseudo);  // player 1 wins
    else if (s.nbJ < s.nbR) printf(" %s gagnent\n", joueur2.pseudo);  // player 2 wins
    else if (s.nbJ == s.nbR) {
        if (s.nbJ5 > s.nbR5) printf(" %s gagnent\n", joueur1.pseudo);  // player 1 wins because he has more piles of 5
        else if (s.nbJ5 < s.nbR5) printf(" %s gagnent\n", joueur2.pseudo);  // player 2 wins because he has more piles of 5
        else printf(" Egalité\n");  // exact same scores
    }
    return 0;
}


int coupV3(T_Position *p) {  // function to make moves
    int depart, fin;  // decalring variables for the origin and end of the move
    printf0("Demande au joueur quelle pile il veut déplacer.\n");
    printf("\tcaseO ? : ");  // asking the player which pile to move
    scanf("%d", &depart);  // getting the value with scanf
    printf0("Demande au joueur où il veut déplacer la pile.\n");
    printf("\tcaseD ? : ");  // asking the player where to put that pile
    scanf("%d", &fin);  // getting the value with scanf
    if (estValide(*p, depart, fin)) *p = jouerCoup(*p, depart, fin);  // if the move is legal, we play it and we update the position variable
    else return 1;  // else, we return 1 so the condition of the while in the main loop is true
    printf("\tOn joue %d -> %d\n", depart, fin);  // printing which move was done
    return 0;  // returning 0 (=the move is valid)
}


int ecrireJSON(T_Position p, char *chemin) {  // function to write the game state into a json file
    FILE *fichier;  // declaring variables
    T_Score s = evaluerScore(p);  // getting the score from the position
    int i;

    fichier = fopen(chemin, "w");  // opening the file
    CHECK_IF(fichier, NULL, chemin);  // security check

    fprintf(fichier, "traiterJson({\n");  // write the start of the json file
    fprintf(fichier, "\t"STR_TURN":%d,\n", p.trait); // write which player needs to play

    fprintf(fichier, "\t"STR_SCORE_J":%d,\n", s.nbJ);  // write yellow's score
    fprintf(fichier, "\t"STR_SCORE_J5":%d,\n", s.nbJ5);  // write the number of pile of 5 of yellow
    fprintf(fichier, "\t"STR_SCORE_R":%d,\n", s.nbR);  // write red's score
    fprintf(fichier, "\t"STR_SCORE_R5":%d,\n", s.nbR5);  // write the number of pile of 5 of red

    fprintf(fichier, "\t"STR_BONUS_J":%d,\n", p.evolution.bonusJ);  // write the position of the yellow bonus piece
    fprintf(fichier, "\t"STR_MALUS_J":%d,\n", p.evolution.malusJ);  // write the position of the yellow malus piece
    fprintf(fichier, "\t"STR_BONUS_R":%d,\n", p.evolution.bonusR);  // write the position of the red bonus piece
    fprintf(fichier, "\t"STR_MALUS_R":%d,\n", p.evolution.malusR);  // write the position of the red malus piece

    fprintf(fichier, "\t"STR_COLS":[\n");  // write the columns state
    for (i = 0; i < NBCASES; i++)
    {
        fprintf(fichier, "\t\t{"STR_NB":%d, "STR_COULEUR":%d}", p.cols[i].nb, p.cols[i].couleur);
        if (i < NBCASES-1) fprintf(fichier, ",\n");
    }
    fprintf(fichier, "\n\t]\n");
    
    
    fprintf(fichier, "});");  // write the end of the json file
    
    // closing the file
    fclose(fichier);
    return 1;
}

// first version of the function to move pieces (not working)
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

// second version (working but needed a rework)
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