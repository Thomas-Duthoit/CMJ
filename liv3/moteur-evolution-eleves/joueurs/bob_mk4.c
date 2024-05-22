/********* Moteur de tournoi : joueur ***************/
// BOB MK4

#include <stdio.h>
#include <stdlib.h>
#include "avalam.h"
#include "moteur.h"


// Poids pour la fonction d'évaluation
#define WEIGHT_ANTIEMPIL -5

octet eval_isolation(T_Position currentPosition, octet o, octet d, octet couleurJoueur) {
    
    //Renvoie -1 si il n’y a pas d’isolation possible
    //renvoie 0 si le pion est deja isole
    //Sinon renvoie la position du pion à déplacer
    //position: position de la case à analyser
    

    /* On veut faire une isolation
    - On regarde les voisins de la pile/jeton de destination
    - Si dans les voisins il n'y a que la pile/jeton qu'on veut jouer, 
      ou des piles/jeton qu'on ne peut pas empiler APRES avoir joué le coup,
      ou des pions/piles nous appartenant
      => alors on joue le coup. */
    T_Voisins voisins = getVoisins(d);//voisins de la destination
    octet i ;//nombre de voisins
    
    for (i = 0; i < voisins.nb; i++){ //pour chaque voisin
        if ((voisins.cases[i] != o) &&
            (currentPosition.cols[voisins.cases[i]].couleur != couleurJoueur) && //si le voisin appartient à l'adversaire
            (currentPosition.cols[o].nb + currentPosition.cols[d].nb + currentPosition.cols[voisins.cases[i]].nb <= 5))
            return 0;
    }
    return 1;
}

octet eval_superflu(T_Position currentPosition, octet d, octet couleurJoueur) {
    //renvoie 1 si on est en position de superflu, renvoie 0 sinon
    T_Voisins voisins = getVoisins(d);
    for (int i=0; i < voisins.nb; i++)   //Pour chaque voisin de la position
        if ((currentPosition.cols[voisins.cases[i]].couleur != couleurJoueur) ||   //Vérifie si le pion voisin appartient à l'adversaire
            (currentPosition.cols[voisins.cases[i]].nb + currentPosition.cols[d].nb <=5))  //Vérifie si c'est possible d'empiler
            return 0;                                     
    return 1;
}

octet eval_pile5(T_Position currentPosition, octet o, octet d, octet quelJoueur) {
    if  ((currentPosition.cols[o].couleur == quelJoueur) &&  // Vérification des couleurs d'origine et destination     
            (currentPosition.cols[d].couleur != quelJoueur) &&
            (currentPosition.cols[o].nb + currentPosition.cols[d].nb == 5))  // Vérification si pile de 5                                                    // Prise de pile pour former une pile de 5
                return 1;
    return 0;
}

octet eval_pile3(T_Position currentPosition, octet o, octet d, octet quelJoueur) {
    T_Voisins voisins;
    octet j, check=0;
    

    if ((currentPosition.cols[o].couleur == quelJoueur) &&  // Vérification des couleurs d'origine et destination     
        (currentPosition.cols[d].couleur != quelJoueur) &&
        (currentPosition.cols[o].nb + currentPosition.cols[d].nb == 3)){
        voisins = getVoisins(d);
            for (j = 0; j < voisins.nb; j++)
            {
                if((currentPosition.cols[voisins.cases[j]].couleur != quelJoueur) &&  // Vérification du danger (pile de 2 adverse autour de la case de destination)
                    (currentPosition.cols[voisins.cases[j]].nb == 2))
                    return 0;
                if((check!= 1) &&  // Vérification si ça ne va pas créer une "Tour Fragile"
                    (o != voisins.cases[j]) &&
                    (currentPosition.cols[voisins.cases[j]].couleur == quelJoueur) &&
                    (currentPosition.cols[voisins.cases[j]].nb == 1))
                    check=1;
            }
            if(check=1) return 1;
        } 
    return 0;
    }  

octet eval_antiempil(T_Position currentPosition, octet o, octet d, octet maCouleur) {
	// Si on peut empiler: renvoie 0
	// Sinon:              renvoie 1
    T_Voisins voisins = getVoisins(d);  // Récup. des voisins
	octet i;  // indice de boucle
	
    if ((currentPosition.cols[o].couleur == maCouleur) &&  // Vérification des couleurs d'origine et destination     
        (currentPosition.cols[d].couleur != maCouleur)) {   // pour ne pas jouer sur nous même
		for (i=0; i < voisins.nb; i++) // {  // Parcours de chaque voisins
			if((voisins.cases[i] != o) &&  // si le voisin vérifié n'est pas la case d'origine et...
			(currentPosition.cols[voisins.cases[i]].couleur != maCouleur) &&  // que le voisin vérifié appartient à l'adversaire
			(currentPosition.cols[o].nb + currentPosition.cols[d].nb + currentPosition.cols[voisins.cases[i]].nb == 5))  // et que ça garantit un point à l'adversaire
				return 1;
		// }
		return 0;
	}
    return 1;
}


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
		sum += WEIGHT_ANTIEMPIL * eval_antiempil(currentPosition, o, d, maCouleur);

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
			printf("Coup direct trouvé: PILE DE 5\n");
			return;
		}
    }
    for(i=0;i<listeCoups.nb; i++) {
        if (eval_pile3(currentPosition, listeCoups.coups[i].origine, listeCoups.coups[i].destination, myColor)) {
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
