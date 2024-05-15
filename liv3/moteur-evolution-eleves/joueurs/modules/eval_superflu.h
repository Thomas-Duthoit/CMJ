octet eval_superflu(T_Position currentPosition, octet d, octet couleurJoueur) {
    //renvoie 0 si on est en position de superflu, renvoie 1 sinon
    T_Voisins voisins = getVoisins(d);
    for (int i=0; i < voisins.nb; i++)   //Pour chaque voisin de la position
        if ((currentPosition.cols[voisins.cases[i]].couleur != couleurJoueur) ||   //Vérifie si le pion voisin appartient à l'adversaire
            (currentPosition.cols[voisins.cases[i]].nb + currentPosition.cols[d].nb <=5))  //Vérifie si c'est possible d'empiler
            return 0;                                     
    return 1;
}