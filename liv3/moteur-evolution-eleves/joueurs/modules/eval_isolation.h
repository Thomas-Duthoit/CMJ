

octet eval_isolation(T_position currentPosition, octet caseACheck) {
    
    //Renvoie -1 si il n’y a pas d’isolation possible
    //renvoie 0 si le pion est deja isole
    //Sinon renvoie la position du pion à déplacer
    //position: position de la case à analyser
    
    octet Pos=-1;
    T_Voisins voisins = getVoisins(caseACheck);
    if (!nbVoisins(caseACheck)){
            return 0;
        }  // ok
    for (int i=0;i<8;i++){
        
        if 
    }
    /*
        if (nbVoisins(caseACheck)==1){
            voisins=getVoisins(caseACheck);
            if(voisins[0].trait==currentPosition.trait)
            return Pos;
        }
        if (nbVoisins(caseACheck)==2){
            voisins=getVoisins(caseACheck);
            if(voisins[0].trait==currentPosition.trait && voisins[1].trait==currentPosition.trait)
                return Pos;
            else{
                if (voisins[0].trait==currentPosition.trait)
                    Pos=voisins[1];
                else
                    Pos=voisins[0];
            }
        }
        if (nbVoisins(caseACheck)==3){
            voisins=getVoisins(caseACheck);
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
        }
        if(nbVoisins(caseACheck)==4){
            voisins=getVoisins(caseACheck);
            if(voisins[0].trait==currentPosition.trait && voisins[1].trait==currentPosition.trait && voisins[2].trait==currentPosition.trait && voisins[3].trait==currentPosition.trait)
                return Pos;
            else{
                for (int i=0;i<4;i++){
                    if (voisins[i].trait!=currentPosition.trait)
                        Pos=voisins[i];
                }
            }
        }
        if(nbVoisins(caseACheck)==5){
            voisins=getVoisins(caseACheck);
            if(voisins[0].trait==currentPosition.trait && voisins[1].trait==currentPosition.trait && voisins[2].trait==currentPosition.trait && voisins[3].trait==currentPosition.trait && voisins[4].trait==currentPosition.trait)
                return Pos;
            else{
                for (int i=0;i<5;i++){
                    if (voisins[i].trait!=currentPosition.trait)
                        Pos=voisins[i];
                }
            }
        }
        if (nbVoisins(caseACheck)==6){
            voisins=getVoisins(caseACheck);
            if(voisins[0].trait==currentPosition.trait && voisins[1].trait==currentPosition.trait && voisins[2].trait==currentPosition.trait && voisins[3].trait==currentPosition.trait && voisins[4].trait==currentPosition.trait && voisins[5].trait==currentPosition.trait)
                return Pos;
            else{
                for (int i=0;i<6;i++){
                    if (voisins[i].trait!=currentPosition.trait)
                        Pos=voisins[i];
                }
            }
        }
        */
        
        
    return Pos;
}