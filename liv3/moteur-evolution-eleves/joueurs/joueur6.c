/********* Moteur de tournoi : joueur ***************/

#include <stdio.h>
#include <stdlib.h>
#include "avalam.h"
#include "moteur.h"


#include "modules/test.h"


void choisirCoup(T_Position currentPosition, T_ListeCoups listeCoups) {
	char i; // Astuce de Mr. Oxoby: un char est plus rapide car en incrémentant, on fait les calculs sur 1 octet et pas 4
	octet o, d; 
	octet myColor = currentPosition.trait; 
    printf("démarrage du bot !\n");
    getchar();
    printf("TEST MODULE: %s", TEST);
    printf("COLOR: %d\n", myColor);
    ecrireIndexCoup(0);

}