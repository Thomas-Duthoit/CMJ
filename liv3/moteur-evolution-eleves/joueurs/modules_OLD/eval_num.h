octet eval_num(T_Position currentPosition, octet o, octet d, octet couleurJoueur) {
octet Avt = 1;
octet Avt_Ennemi = 0;
T_Voisins voisins = getVoisins(d);
for (int i=0; i < voisins.nb; i++){   //Pour chaque voisin de la position
    if ((currentPosition.cols[voisins.cases[i]].couleur != couleurJoueur) &&   //Vérifie si le pion voisin appartient à l'adversaire
    (voisins[i].nb < 5))  { // Vérifie si la pile n'est pas pleine
        Avt_Ennemi++;
    }
    if ((currentPosition.cols[voisins.cases[i]].couleur == couleurJoueur) && //Vérifie si le pion voisin est de le pion du joueur
    (voisins[i].nb < 5))  { // Vérifie si la pile n'est pas pleine
        Avt++;
    }
}
return Avt-Avt_Ennemi;
}                

int global_num(T_position currentPosition, octet o, octet d, octet maCouleur) {
    int avtInitial = 0;
    octet i = 0;
    for (i=0; i<48; i++);
    
}