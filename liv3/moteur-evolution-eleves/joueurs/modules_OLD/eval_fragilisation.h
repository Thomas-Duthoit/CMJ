octet eval_fragilisation(T_Position currentPosition, octet o, octet d, octet maCouleur) {
    
    /* - On vérifie si dans les voisins il y a une pile de 3 de la couleur adverse
   - On trouve alors dans les voisins si il y a un voisin de la même couleur 
   - On déplace le pion sur celui-ci et ainsi de suite pour rendre la tour adverse fragile
   
   - Renvoie 1 si ça fragilise la tour et qu'on peut jouer le coup
   - Renvoie 0 sinon*/

    T_Voisins voisins = getVoisins(o);  // Récup. des voisins
	octet i, j;  // indice de boucle

    if(currentPosition.cols[o].couleur != maCouleur)  // si le pion à frgiliser ne nous appartient pas
        for (i = 0; i < voisins.nb; i++)
            if((currentPosition.cols[voisins.cases[i]].nb == 3) &&  // si un voisin est une pile de 3 ...
                (currentPosition.cols[voisins.cases[i]].couleur != maCouleur) &&  // ...qui ne m'appartient pas
                (currentPosition.cols[d].couleur != maCouleur) &&  // si le pion recouvert est adverse
                (currentPosition.cols[d].nb != 3))  // et que ça ne crée pas une pile de 3 à m'adversaire
                    return 1;  // on joue le coup
    return 0;
}