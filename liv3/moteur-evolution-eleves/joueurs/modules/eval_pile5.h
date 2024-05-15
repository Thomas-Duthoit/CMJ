octet eval_pile5(T_Position currentPosition, octet o, octet d, octet quelJoueur) {
    if  ((currentPosition.cols[o].couleur == quelJoueur) &&  // Vérification des couleurs d'origine et destination     
            (currentPosition.cols[d].couleur != quelJoueur) &&
            (currentPosition.cols[o].nb + currentPosition.cols[d].nb == 5))  // Vérification si pile de 5                                                    // Prise de pile pour former une pile de 5
                return 1;
    return 0;
}