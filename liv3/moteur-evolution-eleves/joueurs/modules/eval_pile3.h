octet eval_pile3(T_Position currentPosition, octet o, octet d, octet quelJoueur) {
    T_Voisins voisins;
    int j;
    

    if ((currentPosition.cols[o].couleur == quelJoueur) &&  // Vérification des couleurs d'origine et destination     
        (currentPosition.cols[d].couleur != quelJoueur) &&
        (currentPosition.cols[o].nb + currentPosition.cols[d].nb == 3)){
        voisins = getVoisins(d);
        j = voisins.nb;
            do
            {
                if((currentPosition.cols[voisins.cases[j]].couleur != quelJoueur) &&  // Vérification du danger (pile de 2 adverse autour de la case de destination)
                    (currentPosition.cols[voisins.cases[j]].nb == 2))
                    return 0;
                j--;
            } while (j != 0);
            return 1;
        } 
    return 0;
    }  
         