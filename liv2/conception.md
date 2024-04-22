<<<<<<< Updated upstream
# DOCUMENT DE CONCEPTION DE STRATÉGIES

## première idée de fonction d'évalutation:

***MeanOpponentMoveScore mk1 (MOMS 1)***

1. On analyse les coups directs syle pile de 3, piles de 5, isolement, etc...
2. Pour chaque coup possible dans la liste des coups légaux, on mets à jour la position de sorte que ce coup soit joué.
Ensuite, on regarde si ce coup nous rapporte des points ou non (fonction EvaluerScore).
Si le deltaScore est en notre faveur, on calcule la moyenne des scores pour les coups légaux suivant de sorte à obtenir le coup avec le meilleur score de réponse moyen (en regardant avec la fonction EvaluerScore pour calculer le deltaScore pour chaque position puis le deltaScore moyen).
3. Ensuite, on joue ce coup moyen si les points apportés par le coup direct sont négligeable par rapport au points moyen

---

***MeanOpponentMoveScore mk2 (MOMS 2)***

Essayer de faire en sorte de modifier la fonction MOMS 1 en rajoutant un système dévaluation de la popsition après coup moyen, en faisant un parcours des coups possible, pour évaluer par exemple le nombre de coups où l'adversaire peu créer des piles de 3 ou de 5, ainsi que les différentes configuration analysées dans le recueil de stratégies, pour y assigner un poid positif ou négatif, puis on pourrait rééévaluer le deltaScore avec une formule du type suivant:

`dScoreFinal = dScore + poidsP3 + poidsP5 + ...`

=======
# DOCUMENT DE CONCEPTION DE STRATÉGIES

## première idée de fonction d'évalutation:

***MeanOpponentMoveScore mk1 (MOMS 1)***

1. On analyse les coups directs syle pile de 3, piles de 5, isolement, etc...
2. Pour chaque coup possible dans la liste des coups légaux, on mets à jour la position de sorte que ce coup soit joué.
Ensuite, on regarde si ce coup nous rapporte des points ou non (fonction EvaluerScore).
Si le deltaScore est en notre faveur, on calcule la moyenne des scores pour les coups légaux suivant de sorte à obtenir le coup avec le meilleur score de réponse moyen (en regardant avec la fonction EvaluerScore pour calculer le deltaScore pour chaque position puis le deltaScore moyen).
3. Ensuite, on joue ce coup moyen si les points apportés par le coup direct sont négligeable par rapport au points moyen

---

***MeanOpponentMoveScore mk2 (MOMS 2)***

Essayer de faire en sorte de modifier la fonction MOMS 1 en rajoutant un système dévaluation de la popsition après coup moyen, en faisant un parcours des coups possible, pour évaluer par exemple le nombre de coups où l'adversaire peu créer des piles de 3 ou de 5, ainsi que les différentes configuration analysées dans le recueil de stratégies, pour y assigner un poid positif ou négatif, puis on pourrait rééévaluer le deltaScore avec une formule du type suivant:

`dScoreFinal = dScore + poidsP3 + poidsP5 + ...`

>>>>>>> Stashed changes
ce qui pourrait permettre d'avoir une évaluation plus 'objective' de la position du joueur adverse pour chaque coup et donc de choisir un meilleur coup