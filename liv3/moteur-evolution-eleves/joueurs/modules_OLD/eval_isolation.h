octet eval_isolation(T_Position currentPosition, octet o, octet d, octet couleurJoueur) {
    
    //Renvoie -1 si il n’y a pas d’isolation possible
    //renvoie 0 si le pion est deja isole
    //Sinon renvoie la position du pion à déplacer
    //position: position de la case à analyser
    

    /* On veut faire une isolation
    - On regarde les voisins de la pile/jeton de destination
    - Si dans les voisins il n'y a que la pile/jeton qu'on veut jouer, 
      ou des piles/jeton qu'on ne peut pas empiler APRES avoir joué le coup,
      ou des pions/piles nous appartenant
      => alors on joue le coup. */
    T_Voisins voisins = getVoisins(d);//voisins de la destination
    octet i ;//nombre de voisins
    
    for (i = 0; i < voisins.nb; i++){ //pour chaque voisin
        if ((voisins.cases[i] != o) &&
            (currentPosition.cols[voisins.cases[i]].couleur != couleurJoueur) && //si le voisin appartient à l'adversaire
            (currentPosition.cols[o].nb + currentPosition.cols[d].nb + currentPosition.cols[voisins.cases[i]].nb <= 5))
            return 0;
    }
    return 1;
}
     /*
 
    int choix;
    choix=nbVoisins(d);
    T_Voisins voisins;
    switch (choix)
    {
    case 1:
        voisins=getVoisins(currentPosition);
            if(voisins[0].trait==currentPosition.trait)
            return Pos;
        break;
    case 2:
        voisins=getVoisins(currentPosition);
            if(voisins[0].trait==currentPosition.trait && voisins[1].trait==currentPosition.trait)
                return Pos;
            else{
                if (voisins[0].trait==currentPosition.trait)
                    Pos=voisins[1];
                else
                    Pos=voisins[0];
            }
        break;
    case 3:
        voisins=getVoisins(currentPosition);
            if(voisins[0].trait==currentPosition.trait && voisins[1].trait==currentPosition.trait && voisins[2].trait==currentPosition.trait)
                return Pos;
            else if{
                for (int i=1;i<3;i++){
                    if(voisins[i-1].trait!=currentPosition.trait && voisins[i].trait!=currentPosition.trait)
                        return Pos;
                    if (voisins[i].trait!=currentPosition.trait){
                        Pos=voisins[i];
                        return Pos;
                    }
                }
            }
        break;
    case 4:
        voisins=getVoisins(currentPosition);
            if(voisins[0].trait==currentPosition.trait && voisins[1].trait==currentPosition.trait && voisins[2].trait==currentPosition.trait && voisins[3].trait==currentPosition.trait)
                return Pos;
            else{
                for (int i=0;i<4;i++){
                    if (voisins[i].trait!=currentPosition.trait)
                        Pos=voisins[i];
                }
            }
        break;
    case 5:
        voisins=getVoisins(currentPosition);
            if(voisins[0].trait==currentPosition.trait && voisins[1].trait==currentPosition.trait && voisins[2].trait==currentPosition.trait && voisins[3].trait==currentPosition.trait && voisins[4].trait==currentPosition.trait)
                return Pos;
            else{
                for (int i=0;i<5;i++){
                    if (voisins[i].trait!=currentPosition.trait)
                        Pos=voisins[i];
                }
            }
        break;
    default:
    return 0;
        break;
    }
    return -1;
}*/