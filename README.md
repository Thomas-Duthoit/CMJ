# CMJ
Challenge moteur de jeu

Le programme standalone se trouve dans le répertoire standalone et permet de jouer à deux joueur au jeu Avalam en ligne de commandes.

Le programme diag permet de faire des représentations du plateau grâce à une chaine FEN :
u d t q c pour les jaunes
U D T Q C pour les rouges
b,m,B,M pour indiquer si la colonne précédente comporte un pion évolution (bonus ou malus) 
1 … n pour indiquer un nombre de colonnes vides

Problèmes connues :

- Pour diag, il y a un problème concernant la redirection. Tout le fichier JSON s'écrit correctement, du moins son contenu. Cependant, le nom du fichier s'écrit avec une extension avec un caractère en trop qui n'est pas réellement affiché.Celui-ci n'apparait uniquement lorsque l'input dans le fichier pour les notes est présent. J'ai tenté de le retirer en émettant la possibilité que c'était '\n' mais ce n'était pas le cas.

- On se pose la question sur l'horodotage du makefile nous joue des tours. Puisque si on make, sans modifier le fichier
 et qu'on fait make debug en suite, il ne va pas recompiler le fichier, car il est considéré comme uptodate. En conclusion, le mode debug ne sera pas activer. Nous sommes obligés de passer par un make clean au préalable.


# Team Avalpierre (●´⌓`●)
