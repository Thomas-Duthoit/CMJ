/********* Moteur de tournoi : joueur ***************/
// BOB

#include <stdio.h>
#include <stdlib.h>
#include "avalam.h"
#include "moteur.h"


#include "modules/eval_isolation.h"
#include "modules/eval_superflu.h"
//#include "modules/eval_dualblinde.h"
#include "modules/eval_pile5.h"
#include "modules/eval_pile3.h"
#include "modules/eval_antiempil.h"
#include "modules/eval_antisabotage.h"


// Poids pour la fonction d'évaluation
#define WEIGHT_ANTIEMPIL -5
#define WEIGHT_ANTISABOTAGE -3


int coupNonDirect(T_Position currentPosition, T_ListeCoups listeCoups, octet maCouleur) {
	octet i = 0;
	octet o, d;
	int sum = 0;
	int bestSum=-999;  // valeur négative inateignable
	octet bestMove=0;  // coup par défaut: 0
	for (i=0; i<listeCoups.nb; i++) {
		// pas de coups direct: on utilise les différents facteurs pour choisir le meilleurs coups possible
		o = listeCoups.coups[i].origine;  // Récupération du coup à tester
		d = listeCoups.coups[i].destination;
		// Reset de la somme pondérée
		sum = 0;
		// Debut de l'évaluation
		sum += WEIGHT_ANTIEMPIL * eval_antiempil(currentPosition, o, d, maCouleur);  // Anti pile de 5
		sum += WEIGHT_ANTISABOTAGE * eval_antisabotage(currentPosition, o, d, maCouleur);  // Ne pas jouer sur nos pions

		// affichage de la somme pondérée évaluée
		printf("[%d] %d -> %d   SOMME=%d\n", i, o, d, sum);  // éviter de donner une pile de 4 
															 // empilable par l'adversaire
		if (sum > bestSum) {  // Le coup est meilleur ?
			bestSum = sum;
			bestMove = i;
			printf("=-*-=-*-=-*-=\nNOUVEAU MEILLEUR COUP NON DIRECT\n\tindex: %d\n\tcoup: %d->%d\n\teval:%d\n=-*-=-*-=-*-=\n", i, o, d, sum);
		}
	}
	ecrireIndexCoup(bestMove);
	printf("\n\nCoup non direct choisi :  %d->%d  [%d]\n\n",
		listeCoups.coups[bestMove].origine,
		listeCoups.coups[bestMove].destination,
		bestMove);
}

void choisirCoup(T_Position currentPosition, T_ListeCoups listeCoups) {
	octet i;
	octet o, d; 
	octet myColor = currentPosition.trait;

	if(listeCoups.coups[0].origine == listeCoups.coups[0].destination){	// Placement des jetons évolutions
		printf("Placement des jetons évolutions\n");
		printf("BonusJ:%zu\n", currentPosition.evolution.bonusJ);
		printf("BonusR:%zu\n", currentPosition.evolution.bonusR);
		printf("MalusJ:%zu\n", currentPosition.evolution.malusJ);
		printf("MalusR:%zu\n", currentPosition.evolution.malusR);
		if(currentPosition.evolution.bonusJ == 255){ 	// Cas où on doit placer le bonus J
			ecrireIndexCoup(7);
			return;
		}
		if(currentPosition.evolution.bonusR == 255)		// Cas où on doit placer le bonus R
		{
			ecrireIndexCoup((47-currentPosition.evolution.bonusJ)/2-1);
			return;
		}
		if (currentPosition.evolution.malusJ == 255)	// Cas où on doit placer le malus J
		{
			ecrireIndexCoup(currentPosition.evolution.bonusR/2+1);
			return;
		}
		ecrireIndexCoup(currentPosition.evolution.bonusJ/2-1);	// Le cas échéant, le malus R
		return;
	}

	
    for(i=0;i<listeCoups.nb; i++) {
        if (eval_pile5(currentPosition, listeCoups.coups[i].origine, listeCoups.coups[i].destination, myColor)
			&& !eval_superflu(currentPosition, listeCoups.coups[i].destination, myColor )) {
        	ecrireIndexCoup(i);
			printf("Coup direct trouvé: PILE DE 5\n");
			return;
		}
    }
    for(i=0;i<listeCoups.nb; i++) {
        if (eval_pile3(currentPosition, listeCoups.coups[i].origine, listeCoups.coups[i].destination, myColor)
			&& !eval_superflu(currentPosition, listeCoups.coups[i].destination, myColor )) {
        	ecrireIndexCoup(i);
			printf("Coup direct trouvé: PILE DE 3\n");
			return;
		}
    }
	for(i=0;i<listeCoups.nb; i++) {
        if (eval_isolation(currentPosition, listeCoups.coups[i].origine, listeCoups.coups[i].destination, myColor)) {
        	ecrireIndexCoup(i);
			printf("Coup direct trouvé: ISOLATION\n");
			return;
		}
    }
	
	printf("Pas de coup direct trouvé => Passage en évaluation approfondie\n");
	coupNonDirect(currentPosition, listeCoups, myColor);
}
