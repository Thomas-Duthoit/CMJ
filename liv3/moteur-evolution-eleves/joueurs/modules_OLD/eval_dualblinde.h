octet eval_dualblinde(T_Position currentPosition, octet o, octet d, octet quelJoueur) {
    T_Voisins voisins;
    octet j, check = 0;

    if ((currentPosition.cols[o].couleur == quelJoueur) &&  // Vérification des couleurs d'origine et destination     
        (currentPosition.cols[d].couleur != quelJoueur) &&
        (currentPosition.cols[o].nb + currentPosition.cols[d].nb == 2)){
            voisins = getVoisins(d);
            for (j = 0; j < voisins.nb; j++)
            {
                if((currentPosition.cols[voisins.cases[j]].couleur != quelJoueur) &&  // Vérification du danger (pile de 2 adverse autour de la case de destination)
                        (currentPosition.cols[voisins.cases[j]].nb == 3))
                        return 0;
                if((currentPosition.cols[voisins.cases[j]].couleur == quelJoueur) &&  // Vérification du danger (pile de 2 adverse autour de la case de destination)
                        (currentPosition.cols[voisins.cases[j]].nb == 2))
                        check=1;
            }
        if(check == 1) return 1;
        } 
    return 0;
    }  