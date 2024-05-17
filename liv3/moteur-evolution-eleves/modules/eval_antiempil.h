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