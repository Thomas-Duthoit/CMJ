/********* Moteur de tournoi : joueur ***************/


#include <stdio.h>
#include <stdlib.h>
#include "avalam.h"
#include "moteur.h"


//#include "modules/eval_isolation.h";
#include "modules/eval_superflu.h"
#include "modules/eval_pile5.h"
#include "modules/eval_pile3.h"



void choisirCoup(T_Position currentPosition, T_ListeCoups listeCoups) {
	octet i;
	octet o, d; 
	octet myColor = currentPosition.trait; 

	
    for(i=0;i<listeCoups.nb; i++) {
        if (eval_pile5(currentPosition, listeCoups.coups[i].origine, listeCoups.coups[i].destination, myColor)) {
        	ecrireIndexCoup(i);
			return;
		}
    }
    for(i=0;i<listeCoups.nb; i++) {
        if (eval_pile3(currentPosition, listeCoups.coups[i].origine, listeCoups.coups[i].destination, myColor)) {
        	ecrireIndexCoup(i);
			return;
		}
    }       
}
