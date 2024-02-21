#include <stdio.h>
#include <avalam.h>
#include <topologie.h>

#define CHEMIN_PAR_DEFAUT "./web/data"

int ecrireJSON(T_Position p, char *chemin);
void format(char* ch);

int main(int argc, char* argv[]) 
{
    T_Position p;
    T_Score s;
    int i = 0;
    char chemin[1000];
    if(argc != 3)
    {
        printf("diag <numDiag> <fen>\n");
        return -1;
    }
    printf("Diagramme %s\n", argv[1]);
    printf("Fen : %s\n", argv[2]);
    printf("Fichier (sera créé dans le répertoire ./web/data s'il existe) ? [diag.js] ");
    fgets(chemin, 1000, stdin);
    format(chemin);
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

void format(char ch[])
{
    int i = 0;
    while(ch[i] != '\0') i++;
    ch[i-1] = '\0';
}

// thomas was here :)