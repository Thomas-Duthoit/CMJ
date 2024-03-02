#include <stdio.h>
#include <stdlib.h>
#include <avalam.h>
#include <topologie.h>

#define CHEMIN_PAR_DEFAUT "./web/data/diag.js"
#define BREAK "<br />"

#define MAX_K 1000

typedef struct
{
    int trait;
    int num_diag;
    char* notes;
    char* fen;
} T_Diag;

int ecrireJSON(T_Position p, char *chemin, T_Diag d);
void format(char* ch);
void concat(char dest[], char src[]);

int main(int argc, char* argv[]) 
{
    T_Position p;
    T_Diag d;
    int i = 0, j = 0;
    int case_prise = 0;  // Sert à savoir où se trouve la dernière case "occupée"
    char chemin[MAX_K]= "";
    char description[MAX_K] = "";
    char temp[MAX_K] = "";
    char num[MAX_K] = "";

    if(argc != 3)  // Nombre d'argument insuffisant
    {
        printf("diag <numDiag> <fen>\n");
        return -1;
    }

    d.num_diag = atoi(argv[1]);  // Numéro de diagramme
    d.fen = argv[2];  // Chaine FEN

    printf("Diagramme %d\n", d.num_diag);
    printf("Fen : %s\n", d.fen);

    printf("Fichier (sera créé dans le répertoire ./web/data s'il existe) ? [diag.js] ");
    fgets(chemin, MAX_K, stdin); // Demande du chemin
    format(chemin);

    printf("Description (vous pouvez saisir du HTML, 1000 caractères max, Ctrl+D pour terminer) ? []\n");
    while(fgets(temp, MAX_K, stdin) != NULL)  // Description
    {
        format(temp);
        if(description[0] != '\0')
            concat(description, BREAK);
        concat(description, temp);
    }
    d.notes = description;
    printf("Description : %s", d.notes);

//  Initialise le tout avant l'interprétation de la chaine FEN
    p.trait = 0;
    p.evolution.bonusJ = UNKNOWN;
    p.evolution.bonusR = UNKNOWN;
    p.evolution.malusJ = UNKNOWN;
    p.evolution.malusR = UNKNOWN;
    for(i = 0; i < NBCASES; i++)
    {
        p.cols[i].couleur = 0;
        p.cols[i].nb = 0;
    }
    i = 0;

    while(d.fen[i] != '\0' && case_prise < NBCASES)
    {
        switch(d.fen[i])
        {
        case 'u':
            p.cols[case_prise].couleur = 1;
            p.cols[case_prise].nb = 1;
            case_prise++;
            break;

        case 'd':
            p.cols[case_prise].couleur = 1;
            p.cols[case_prise].nb = 2;
            case_prise++;
            break;

        case 't':
            p.cols[case_prise].couleur = 1;
            p.cols[case_prise].nb = 3;
            case_prise++;
            break;
        
        case 'q':
            p.cols[case_prise].couleur = 1;
            p.cols[case_prise].nb = 4;
            case_prise++;
            break;

        case 'c':
            p.cols[case_prise].couleur = 1;
            p.cols[case_prise].nb = 5;
            case_prise++;
            break;

        case 'U':
            p.cols[case_prise].couleur = 2;
            p.cols[case_prise].nb = 1;
            case_prise++;
            break;

        case 'D':
            p.cols[case_prise].couleur = 2;
            p.cols[case_prise].nb = 2;
            case_prise++;
            break;
        
        case 'T':
            p.cols[case_prise].couleur = 2;
            p.cols[case_prise].nb = 3;
            case_prise++;
            break;

        case 'Q':
            p.cols[case_prise].couleur = 2;
            p.cols[case_prise].nb = 4;
            case_prise++;
            break;

        case 'C':
            p.cols[case_prise].couleur = 2;
            p.cols[case_prise].nb = 5;
            case_prise++;
            break;
        
        case 'b':
            if(p.evolution.bonusJ == UNKNOWN && case_prise > 0)
                p.evolution.bonusJ = case_prise-1;
            break;

        case 'm':
            if(p.evolution.malusJ == UNKNOWN && case_prise > 0)
                p.evolution.malusJ = case_prise-1;
            break;

        case 'B':
            if(p.evolution.bonusR == UNKNOWN && case_prise > 0)
                p.evolution.bonusR = case_prise-1;
            break;

        case 'M':
            if(p.evolution.malusR == UNKNOWN && case_prise > 0)
                p.evolution.malusR = case_prise-1;
            break;

        case 'j':
            p.trait = 1;
            break;

        case 'r':
            p.trait = 2;
            break;
        
        default: 
            if('0' <= d.fen[i] && d.fen[i] <= '9')
            {
                while('0' <= d.fen[i] && d.fen[i] <= '9')
                {
                    num[j] = d.fen[i];
                    j++;
                    i++;
                }
                num[j] = '\0';
                j = 0;
                case_prise = case_prise + atoi(num);
                i--;
            }
            break;
        }
        i++;
    }
    
    if(chemin[0] == '\0')  // Ecriture au chemin par défaut ou défini par l'utilisateur
        ecrireJSON(p, CHEMIN_PAR_DEFAUT, d);
    else
        ecrireJSON(p, chemin, d);
    return 0;
}


int ecrireJSON(T_Position p, char *chemin, T_Diag d){
    FILE *fichier;
    T_Score s = evaluerScore(p);
    int i;
    fichier = fopen(chemin, "w+");
    CHECK_IF(fichier, NULL, chemin);
    printf("\nEnregistrement de %s\n", chemin);

    fprintf(fichier, "traiterJson({\n");  // Initialisation du fichier JSON
    fprintf(fichier, "\t"STR_TURN":%d,\n", p.trait); // Ecrit le trait (Savoir qui joue)
    fprintf(fichier, "\t"STR_NUMDIAG":%d,\n", d.num_diag);  // Ecrit le numéro de diagramme
    fprintf(fichier, "\t"STR_NOTES":\"%s\",\n", d.notes);  // Ecrit les notes
    fprintf(fichier, "\t"STR_FEN":\"%s\",\n", d.fen); // Ecrit la chaine fen


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
    CHECK_DIF(fichier, NULL, chemin);
}


void format(char ch[])  // Permet de retirer "\n" crée à cause du fgets. 
{
    int i = 0;
    while(ch[i] != '\0') i++;
    if(ch[i-1] == '\n') ch[i-1] = '\0';
}


void concat(char dest[], char src[])  // Permet de concaténer 2 chaines
{
    int i = 0, j = 0;
    while(dest[i] != '\0') i++;
    while(src[j] != '\0')
    {
        dest[i] = src[j];
        i++;
        j++;
    }
    dest[i] = '\0';
}
