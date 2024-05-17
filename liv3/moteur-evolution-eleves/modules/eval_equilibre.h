octet EvaluerEquilibre(T_Position currentPosition, octet o, octet d, octet couleurJoueur){
    //Renvoie vrai si on est en situation d’équilibre
    //Renvoie faux sinon
    //declaration des variables
    octet Cpt = 0,Cpt_Ennemi = 0;
    T_Voisins voisins = getVoisins(d);
    if (currentPosition.nb==3){ //Vérifie si la tour sur la position est de taille 3 :
        for (octet i=0; i < voisins.nb; i++){ //Pour chaque voisin de la position
            if ((currentPosition.cols[voisins.cases[i]].couleur != couleurJoueur) &&   //Vérifie si le pion voisin appartient à l'adversaire
                (voisins[i].nb < 5))  { // Vérifie si la pile n'est pas pleine
                Cpt_Ennemi++;
                }
            if ((currentPosition.cols[voisins.cases[i]].couleur == couleurJoueur) && //Vérifie si le pion voisin est de le pion du joueur
                (voisins[i].nb < 5))  { // Vérifie si la pile n'est pas pleine
                Cpt++;
                }
        }   
    else{
        return 1;
    }
        
        
    }
}