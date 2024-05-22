octet eval_antisabotage(T_Position currentPosition, octet o, octet d, octet maCouleur) {
    // Si on joue sur notre pion : renvoie 1
    // Sinon :                     renvoie 0
	return currentPosition.cols[o].couleur == currentPosition.cols[d].couleur == maCouleur;
}
