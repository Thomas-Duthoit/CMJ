/********* Moteur de tournoi : joueur ***************/

#include <stdio.h>
#include <stdlib.h>
#include "avalam.h"
#include "moteur.h"


void choisirCoup(T_Position currentPosition, T_ListeCoups listeCoups) {
	int i; 
	octet o, d; 
	octet myColor = currentPosition.trait; 

    afficherListeCoups(listeCoups);  // Display all possible moves.

}