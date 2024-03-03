# CMJ
Challenge moteur de jeu

Le programme standalone se trouve dans le répertoire standalone et permet de jouer à deux joueur au jeu Avalam en ligne de commandes.

Le programme diag permet de faire des représentations du plateau grâce à une chaine FEN :
- u d t q c pour les jaunes
- U D T Q C pour les rouges
- b,m,B,M pour indiquer si la colonne précédente comporte un pion évolution (bonus ou malus) 
- 1 … n pour indiquer un nombre de colonnes vides

Problèmes connues :

- Pour diag, il y a un problème concernant la redirection. Tout le fichier JSON s'écrit correctement, du moins son contenu. Cependant, le nom du fichier s'écrit avec une extension avec un caractère en trop qui n'est pas réellement affiché.Celui-ci n'apparait uniquement lorsque l'input dans le fichier pour les notes est présent. J'ai tenté de le retirer en émettant la possibilité que c'était '\n' mais ce n'était pas le cas.

-on se pose la question sur l'horodotage du makefile nous jouent des tours. Puisque si l'ont make et sans sauvgarder
en faisant Ctrl+S et que l'ont fait make debug en suite il va prendre le fichier sans les printf0.


# Team Avalpierre (●´⌓`●)
