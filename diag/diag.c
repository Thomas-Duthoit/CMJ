#include <stdio.h>
#include <avalam.h>
#include <topologie.h>

#define CHEMIN_PAR_DEFAUT "./web/data/diag.js"

int ecrireJSON(T_Position p, char *chemin);
void format(char* ch);

int main(int argc, char* argv[]) 
{
    T_Position p;
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
    fgets(chemin, 1000, stdin); // OK
    format(chemin);
    if(chemin[0] == '\0')
        ecrireJSON(p, CHEMIN_PAR_DEFAUT);
    else
        ecrireJSON(p, chemin);
    return 0;
}

int ecrireJSON(T_Position p, char *chemin) {
    FILE *fichier;
    T_Score s = evaluerScore(p);
    int i;
    fichier = fopen(chemin, "w+");
    if (fichier==NULL) 
        return 0;
    fprintf(fichier, "traiterJson({\n");
    /*TODO: Reste du fichier JSON*/ 
    
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