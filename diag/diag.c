#include <stdio.h>
#include <stdlib.h>
#include <avalam.h>
#include <topologie.h>

#define CHEMIN_PAR_DEFAUT "./web/data/diag.js"
#define BREAK "<br />"

#define MAX_K 1000

typedef struct
{
    int num_diag;  // Diag's number
    char* notes;  // Diag's notes 
    char* fen;  // Diag's FEN string.
} T_Diag;

int ecrireJSON(T_Position p, char *chemin, T_Diag d);
void format(char* ch);
void concat(char dest[], char src[]);

int main(int argc, char* argv[]) 
{
    T_Position p;
    T_Diag d;
    int i = 0, j = 0;
    int case_prise = 0;  // Var use to know where is the first case we can take
    char chemin[MAX_K]= "";
    char description[MAX_K] = "";
    char temp[MAX_K] = "";
    char num[MAX_K] = "";
    
    if(argc != 3)  // If arg's number are Insufficient
    {
        printf0("Le nombre d'argument est incorrect\n");
        printf("diag <numDiag> <fen>\n");
        return -1;
    }

    d.num_diag = atoi(argv[1]);  // Diag number
    d.fen = argv[2];  // FEN String

    printf("Diagramme %d\n", d.num_diag);
    printf("Fen : %s\n", d.fen);

    printf("Fichier (sera créé sous la forme %s si possible) ?", CHEMIN_PAR_DEFAUT);
    fgets(chemin, MAX_K, stdin); // Path's input
    format(chemin);

    printf("Description (vous pouvez saisir du HTML, %d caractères max, Ctrl+D pour terminer) ? []\n", MAX_K);
    while(fgets(temp, MAX_K, stdin) != NULL)  // Description's input
    {
        format(temp);
        if(description[0] != '\0')
            concat(description, BREAK);
        concat(description, temp);
    }
    d.notes = description;
    printf("\nDescription : \"%s\"\n", d.notes);

//  Initializing before FEN interpretation
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
    printf0("Début de l'interprétation de la FEN\n");
    while(d.fen[i] != '\0' && case_prise < NBCASES) // All possibles cases for the FEN interpretation
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

    if(p.trait == 0)  // Only if trait is undefined due to while condition if it's over NB_CASES.
    {
        printf0("Trait non défini, recherche dans la FEN\n");
        while(d.fen[i] != '\0')
        {
            if(d.fen[i] == 'j') 
            {
                p.trait = 1; 
                printf0("Le trait est aux jaunes\n");
            }
            if(d.fen[i] == 'r') 
            {
                p.trait = 2; 
                printf0("Le trait est aux rouges\n");
            }
            i++;
        }
    }
    if(chemin[0] == '\0')  // Creating and writing the file depending of the user's input.
    {
        printf0("Chemin non défini\n");
        ecrireJSON(p, CHEMIN_PAR_DEFAUT, d);
    }
    else
    {
        printf0("Chemin défini");
        ecrireJSON(p, chemin, d);
    }
    return 0;
}


int ecrireJSON(T_Position p, char *chemin, T_Diag d){  // Write the JSON file
    FILE *fichier;
    int i;
    fichier = fopen(chemin, "w+");
    CHECK_IF(fichier, NULL, chemin);
    printf("\nEnregistrement de %s\n", chemin);

    fprintf(fichier, "traiterJson({\n");  // Initializes JSON file
    fprintf(fichier, "\t"STR_TURN":%d,\n", p.trait); // Write the "trait"
    fprintf(fichier, "\t"STR_NUMDIAG":%d,\n", d.num_diag);  // Write diag's number
    fprintf(fichier, "\t"STR_NOTES":\"%s\",\n", d.notes);  // Write notes
    fprintf(fichier, "\t"STR_FEN":\"%s\",\n", d.fen); // Write the FEN string

    fprintf(fichier, "\t"STR_BONUS_J":%d,\n", p.evolution.bonusJ);  // Write the position of Yellow's bonus
    fprintf(fichier, "\t"STR_MALUS_J":%d,\n", p.evolution.malusJ);  // Write the position of Yellow's malus
    fprintf(fichier, "\t"STR_BONUS_R":%d,\n", p.evolution.bonusR);  // Write the position of Red's bonus
    fprintf(fichier, "\t"STR_MALUS_R":%d,\n", p.evolution.malusR);  // Write the position of Red's malus

    fprintf(fichier, "\t"STR_COLS":[\n");  // Write all column states
    for (i = 0; i < NBCASES; i++)
    {
        fprintf(fichier, "\t\t{"STR_NB":%d, "STR_COULEUR":%d}", p.cols[i].nb, p.cols[i].couleur);
        if (i < NBCASES-1) fprintf(fichier, ",\n");
    }
    fprintf(fichier, "\n\t]\n");

    fprintf(fichier, "});");

    // Close file
    fclose(fichier);
    return 0;
}


void format(char ch[])  // Remove '\n' due to fgets
{
    int i = 0;
    while(ch[i] != '\0') i++;
    if(ch[i-1] == '\n') ch[i-1] = '\0';
}


void concat(char dest[], char src[])  // Concatenate 2 strings (useful for notes)
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
