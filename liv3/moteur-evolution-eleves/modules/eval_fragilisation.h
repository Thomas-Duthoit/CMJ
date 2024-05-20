/* - On vérifie si dans les voisins il y a une pile de 3 de la couleur adverse
   - On trouve alors dans les voisins si il y a un voisin de la même couleur 
   - On déplace le pion sur celui-ci et ainsi de suite pour rendre la tour adverse fragile
   
   - Renvoie 1 si ça fragilise la tour
   - Renvoie 0 sinon*/

octet eval_fragilisation(T_Position currentPosition, octet o, octet d, octet maCouleur) {
    T_Voisins voisins = getVoisins(o);  // Récup. des voisins
	octet i, j;  // indice de boucle

    if(currentPosition.cols[o].couleur != maCouleur)
        for (i = 0; i < voisins.nb; i++)
            if((currentPosition.cols[voisins.cases[i]].nb == 3) &&
                (currentPosition.cols[voisins.cases[i]].couleur != maCouleur) &&
                (currentPosition.cols[d].couleur != maCouleur) &&
                (currentPosition.cols[d].nb != 3))
                    return 1;
    return 0;
}