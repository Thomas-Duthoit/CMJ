#include <stdio.h>
#include <stdlib.h>
#include <avalam.h>
#include <topologie.h>

#define CHEMIN_PAR_DEFAUT "./web/data/diag.js"

typedef struct
{
    int trait;
    int num_diag;
    char* notes;
    char* fen;
} T_Diag;

int ecrireJSON(T_Position p, char *chemin, T_Diag d);
void format(char* ch);

int main(int argc, char* argv[]) 
{
    T_Position p;
    T_Diag d;
    int i = 0;
    char chemin[1000];

    if(argc != 3)
    {
        printf("diag <numDiag> <fen>\n");
        return -1;
    }

    d.num_diag = atoi(argv[1]);
    d.fen = argv[2];

    /*TODO: POSSIBILITE FAIRE DES NOTES*/

    printf("Diagramme %d\n", d.num_diag);
    printf("Fen : %s\n", d.fen);
    printf("Fichier (sera créé dans le répertoire ./web/data s'il existe) ? [diag.js] ");
    fgets(chemin, 1000, stdin);
    format(chemin);
    if(chemin[0] == '\0')
        ecrireJSON(p, CHEMIN_PAR_DEFAUT, d);
    else
        ecrireJSON(p, chemin, d);
    return 0;
}

int ecrireJSON(T_Position p, char *chemin, T_Diag d){
    FILE *fichier;
    int i;
    fichier = fopen(chemin, "w+");
    if (fichier==NULL) 
        return 0;

    /*TODO: INTERPREATION CHAINE FEN*/

    fprintf(fichier, "traiterJson({\n");  // Initialisation du fichier JSON
    fprintf(fichier, "\t"STR_TURN":\n"); // Ecrit le trait (Savoir qui joue)
    fprintf(fichier, "\t"STR_NUMDIAG":%d,\n", d.num_diag);  // Ecrit le numéro de diagramme
    fprintf(fichier, "\t"STR_NOTES":\n");
    fprintf(fichier, "\t"STR_FEN":%s,\n", d.fen); // Ecrit la chaine fen


    fprintf(fichier, "\t"STR_SCORE_J":\n");  // Ecrit le score des jaunes
    fprintf(fichier, "\t"STR_SCORE_J5":\n");  // Ecrit le nombre de colonnes 5 pieces des jaunes
    fprintf(fichier, "\t"STR_SCORE_R":\n");  // Eccrit le score des rouges
    fprintf(fichier, "\t"STR_SCORE_R5":\n");  // Ecrit le nom de colonnes 5 pièces des rouges

    fprintf(fichier, "\t"STR_BONUS_J":\n");  // Ecrit la position du jeton evol Jaunes
    fprintf(fichier, "\t"STR_MALUS_J":\n");  // Ecrit la position du jeton malus Jaunes
    fprintf(fichier, "\t"STR_BONUS_R":\n");  // Ecrit la position du jeton evol Rouges
    fprintf(fichier, "\t"STR_MALUS_R":\n");  // Ecrit la position du jeton malus Rouges

    fprintf(fichier, "});");

    // fermer le fichier
    fclose(fichier);
    return 1;
}

void format(char ch[])  // Permet de retirer "\n" crée à cause du fgets. 
{
    int i = 0;
    while(ch[i] != '\0') i++;
    ch[i-1] = '\0';
}

// thomas was here :)