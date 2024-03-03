# CMJ
Challenge moteur de jeu

Problèmes connues :

- Pour diag, il y a un problème concernant la redirection. Tout le fichier JSON s'écrit correctement, du moins son contenu. Cependant, le nom du fichier s'écrit avec une extension avec un caractère en trop qui n'est pas réellement affiché.Celui-ci n'apparait uniquement lorsque l'input dans le fichier pour les notes est présent. J'ai tenté de le retirer en émettant la possibilité que c'était '\n' mais ce n'était pas le cas.

- Pour le mode debug en général, en utilisant les define dans avalam.h, se printent quand même dans tous les cas, même quand le mode débug n'est pas défini et que donc, cela ne devrait rien envoyer. Ces tests ont été effectués en faisant des jeux d'essaies et en printant des variables crées spécialement pour faire des essaies (qui n'avait donc aucune incidence sur le programme).

# Team Avalpierre (●´⌓`●)
