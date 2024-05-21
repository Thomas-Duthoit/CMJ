/********* Moteur de tournoi : joueur ***************/
// BOB

#include <stdio.h>
#include <stdlib.h>
#include "avalam.h"
#include "moteur.h"

// INCLUSION DES MODULES UTILISES POUR L'EVALUATION
#include "modules/eval_isolation.h"
#include "modules/eval_superflu.h"
//#include "modules/eval_num.h"  // pas une bonne stratégie
//#include "modules/eval_dualblinde.h"  // plus un hadicap qu'autre chose -> algorithme repris dans des tests d'autres modules
#include "modules/eval_pile5.h"
#include "modules/eval_pile3.h"
#include "modules/eval_antiempil.h"
#include "modules/eval_antisabotage.h"
#include "modules/eval_fragilisation.h"


// Poids pour la fonction d'évaluation
#define WEIGHT_ANTIEMPIL -5
#define WEIGHT_ANTISABOTAGE -3


int coupNonDirect(T_Position currentPosition, T_ListeCoups listeCoups, octet maCouleur) {
	octet i = 0;
	octet o, d;
	int sum = 0;
	int bestSum=-999;  // valeur négative inateignable
	octet bestMove=0;  // coup par défaut: 0
	/*int bestNum=-999;
	int num;*/
	printf("=-*-=-*-=-*-=\n");
	for (i=0; i<listeCoups.nb; i++) {
		// pas de coups direct: on utilise les différents facteurs pour choisir le meilleurs coups possible
		o = listeCoups.coups[i].origine;  // Récupération du coup à tester
		d = listeCoups.coups[i].destination;
		// Reset de la somme pondérée
		sum = 0;
		// Debut de l'évaluation
		sum += WEIGHT_ANTIEMPIL * eval_antiempil(currentPosition, o, d, maCouleur);  // Anti pile de 5
		sum += WEIGHT_ANTISABOTAGE * eval_antisabotage(currentPosition, o, d, maCouleur);  // Ne pas jouer sur nos pions
		//num = global_num(currentPosition, o, d, maCouleur);  // Avoir un bon avantage numérique

		// affichage de la somme pondérée évaluée
		//printf("[%d] %d -> %d   SOMME=%d\n", i, o, d, sum);  // éviter de donner une pile de 4 
														      // empilable par l'adversaire
		if (sum > bestSum) {  // Le coup est le meilleur pour l'instant ?
			bestSum = sum;
			//bestNum = num;
			bestMove = i;
			printf("NOUVEAU MEILLEUR COUP NON DIRECT\n\tindex: %d\n\tcoup: %d->%d\n\teval:%d\n", i, o, d, sum);
		}
		/*else if (sum == bestSum && num > bestNum) {  // Le coup est mieux au niveau avantage numérique ?
			bestSum = sum;
			bestNum = num;
			bestMove = i;
			printf("NOUVEAU MEILLEUR COUP NON DIRECT (avec eval_num)\n\tindex: %d\n\tcoup: %d->%d\n\teval:%d\n\t(eval_num:%d)\n", i, o, d, sum, num);
		}*/
	}
	printf("=-*-=-*-=-*-=\n");
	ecrireIndexCoup(bestMove);
	printf("\n\nCoup non direct choisi :  %d->%d  [%d]\n\n=-*-=-*-=-*-=\n",
		listeCoups.coups[bestMove].origine,
		listeCoups.coups[bestMove].destination,
		bestMove);
}

void choisirCoup(T_Position currentPosition, T_ListeCoups listeCoups) {
	octet i, j;
	octet o, d; 
	octet myColor = currentPosition.trait;
	T_Voisins voisins;

	if (listeCoups.coups[0].origine == listeCoups.coups[0].destination) {	// Placement des jetons évolutions
		printf("Placement des jetons évolutions\n");
		printf("BonusJ:%zu\n", currentPosition.evolution.bonusJ);
		printf("BonusR:%zu\n", currentPosition.evolution.bonusR);
		printf("MalusJ:%zu\n", currentPosition.evolution.malusJ);
		printf("MalusR:%zu\n", currentPosition.evolution.malusR);
		if(currentPosition.evolution.bonusJ == 255) { 	// Cas où on doit placer le bonus J
			ecrireIndexCoup(7); return; }
		if(currentPosition.evolution.bonusR == 255) { 	// Cas où on doit placer le bonus R
			ecrireIndexCoup((47-currentPosition.evolution.bonusJ)/2-1); return; }
		if (currentPosition.evolution.malusJ == 255)	// Cas où on doit placer le malus J
		{
			voisins = getVoisins(currentPosition.evolution.bonusR);
			for(i = 0; i < voisins.nb; i++)
				if(currentPosition.cols[voisins.cases[i]].couleur == myColor)
					for(j = currentPosition.evolution.bonusR/2; j < listeCoups.nb; j++)
						if(listeCoups.coups[j].destination == voisins.cases[i]){
							ecrireIndexCoup(j);	return; }
		}			
		voisins = getVoisins(currentPosition.evolution.bonusJ); // Le cas échant, placer le malus R
			for(i = 0; i < voisins.nb; i++)
				if(currentPosition.cols[voisins.cases[i]].couleur == myColor)
					for(j = currentPosition.evolution.bonusJ/2; j < listeCoups.nb; j++)
						if(listeCoups.coups[j].destination == voisins.cases[i]){
							ecrireIndexCoup(j);	return; }
		
	}

	
    for(i=0;i<listeCoups.nb; i++) {
        if (eval_pile5(currentPosition, listeCoups.coups[i].origine, listeCoups.coups[i].destination, myColor)
			&& !eval_superflu(currentPosition, listeCoups.coups[i].destination, myColor )) {
        	ecrireIndexCoup(i);
			printf("Coup direct trouvé: PILE DE 5\n\t%d->%d\n", listeCoups.coups[i].origine, listeCoups.coups[i].destination);
			return;
		}
    }
    for(i=0;i<listeCoups.nb; i++) {
        if (eval_pile3(currentPosition, listeCoups.coups[i].origine, listeCoups.coups[i].destination, myColor)
			&& !eval_superflu(currentPosition, listeCoups.coups[i].destination, myColor )) {
        	ecrireIndexCoup(i);
			printf("Coup direct trouvé: PILE DE 3\n\t%d->%d\n", listeCoups.coups[i].origine, listeCoups.coups[i].destination);
			return;
		}
    }
	for(i=0;i<listeCoups.nb; i++) {
        if (eval_isolation(currentPosition, listeCoups.coups[i].origine, listeCoups.coups[i].destination, myColor)) {
        	ecrireIndexCoup(i);
			printf("Coup direct trouvé: ISOLATION\n\t%d->%d\n", listeCoups.coups[i].origine, listeCoups.coups[i].destination);
			return;
		}
    }
	for(i=0;i<listeCoups.nb; i++) {
        if (eval_fragilisation(currentPosition, listeCoups.coups[i].origine, listeCoups.coups[i].destination, myColor)) {
        	ecrireIndexCoup(i);
			printf("Coup direct trouvé: FRAGILISATION\n\t%d->%d\n", listeCoups.coups[i].origine, listeCoups.coups[i].destination);
			return;
		}
    }

	printf("Pas de coup direct trouvé => Passage en évaluation approfondie\n");
	coupNonDirect(currentPosition, listeCoups, myColor);
 }