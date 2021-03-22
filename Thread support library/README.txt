================= Mode ===================================================
Il est possible d'exécuter nos tests ayant que nos graphes en définissant des modes spécifiques.
Ces modes correspondent respectivement à :
  #  : notre bibliothèque
  # -pthread : la bibliothèque pthread
  # -premp : l'activation de la préemption dans notre bibliothèque
  # -head : notre bibliothèque avec une insertion des threads par la tête de la file

  Il est préférable d'utiliser ce dernier mode "-head" car il obtient les mêmes performances que notre librairie classique
  pour la plupart des opérations mais a de meilleur performance lors du calcul de fibonacci.

================= Tests ==================================================
  1) make check
  Permet de compiler, et d'exécuter tous les tests avec notre bibliothèque classique ainsi que la bibliothèque pthread

  2) make pthreads
  Permet de compiler, et d'exécuter tous les tests avec la bibliothèque pthread

  3) make [Nom du test] [MODE1=-pthread] [MODE2=]
  Permet de compiler et d'exécuter le test suivant les modes choisis.
  Par défaut les modes sont notre bibliothèque classique et pthread
  Si MODE1 = MODE2, alors on lance que un seul mode

================= Tests valgrind ==================================================
  1) make check
  Permet de compiler, et d'exécuter tous les tests avec notre bibliothèque classique sous valgrind.
  Les résultats des valgrinds sont stockés ./install/bin/Nom_du_test-valgrind.txt et on affiche uniquement
  SUCCESS ou FAILURE si toute la mémoire a été libéré et s'il n'y a pas d'erreur mémoire.

  2) make [Nom du test]-valgrind [MODE1=]
  Permet de compiler et d'exécuter le test sous valgrind suivant les modes choisis.
  Par défaut le mode est notre bibliothèque classique.
  De la même manière que pour make check le résultat du test valgrind est stocké dans un fichier texte
  comme indiqué si dessus et seules SUCCESS ou FAILURE s'affiche.

================= Graphes ==================================================
  1) make graphs
  Permet de compiler, de réaliser nos graphes pour tous les tests avec notre bibliothèque classique ainsi que la bibliothèque pthread

  2) make [Nom du test]-graph [MODE1=-pthread] [MODE2=] [MODE3=] [MODE4=]
  Permet de compiler, de réaliser le graphe pour notre test avec les modes choisis
  Par défaut les modes sont notre bibliothèque classique et pthread
