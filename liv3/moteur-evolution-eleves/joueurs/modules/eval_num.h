octet eval_num(T_Position currentPosition, octet o, octet d, octet couleurJoueur) {
int Avt = 1;
int Avt_Ennemi = 0;
T_Voisins voisins = getVoisins(d);
for (int i=0; i < voisins.nb; i++){   //Pour chaque voisin de la position
    if (currentPosition.cols[voisins.cases[i]].couleur != couleurJoueur) ||   //Vérifie si le pion voisin appartient à l'adversaire
    (voisins[i].nb < 5)  { // Vérifie si la pile n'est pas pleine
        Avt_Ennemi++;
    }
    if (currentPosition.cols[voisins.cases[i]].couleur == couleurJoueur) || //Vérifie si le pion voisin est de le pion du joueur
    (voisins[i].nb < 5)  { // Vérifie si la pile n'est pas pleine
        Avt++;
    }
}
return Avt-Avt_Ennemi;
}                
