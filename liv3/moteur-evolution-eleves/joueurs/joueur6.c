/********* Moteur de tournoi : joueur ***************/

#include <stdio.h>
#include <stdlib.h>
#include "avalam.h"
#include "moteur.h"


#include "modules/test.h"


void choisirCoup(T_Position currentPosition, T_ListeCoups listeCoups) {
	int i, j, check = 0;
	octet o, d; 
	octet myColor = currentPosition.trait; 
    T_Voisins voisins;


	// afficherListeCoups(listeCoups);

	printf("Ma couleur : %s\n", COLNAME(currentPosition.trait));
	for(i=0;i<listeCoups.nb; i++) {
		o = listeCoups.coups[i].origine; 
		d = listeCoups.coups[i].destination;

        if  ((currentPosition.cols[o].couleur == myColor) &&                           // Vérification des couleurs d'origine et destination     
            (currentPosition.cols[d].couleur != myColor)){

                switch(currentPosition.cols[o].nb + currentPosition.cols[d].nb)
                {

                case 5:                                                               // Prise de pile pour former une pile de 5
                    ecrireIndexCoup(i);
                    break;
                

                case 3:                                                              // Prise de pile ou de jeton pour former une pile de 3
                    voisins = getVoisins(d);
                    j = voisins.nb;
                    check = 0;
                    do
                    {
                        if((currentPosition.cols[voisins.cases[j]].couleur != myColor) &&       // Vérification du danger (pile de 2 adverse autour de la case de destination)
                        (currentPosition.cols[voisins.cases[j]].nb == 2))
                            check += 1; 
                        j -= 1;
                    } while (j != 0 && check != 1);
                    if (check == 0){
                        ecrireIndexCoup(i);
                    }
                    break;


                default:                                                             // Utiliser pour limiter la "casse"                                                   
                    if(currentPosition.cols[o].nb + currentPosition.cols[d].nb != 4)
                        ecrireIndexCoup(i);
                    break;

            }
        }
            
    }
                            
}
