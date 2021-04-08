# Création d'un compilateur 
Projet réalisé en 2019 avec Maxime ROSAY

## Ce qui a été implémenté dans ce projet:
- déclarations (int, float, struct, void, pointeurs)
- opérateurs (+,-,*) mais pas entre pointeurs
- affectations (int,float,struct)
- conditionnels (if, if else, while)
- structures (déclaration, affectation) (finalement pas vraiment, cf commentaires)
- return (pas de contrôle par rapport à la sortie de la fonction)
- fonction (cf commentaires)

Nous avons des tests unitaires, pour les lancer:
> ./test_script.sh [-d]
(le -d donne plus de détails sur les tests effectués)

Pour générer les fichiers .h et .c d'un fichier .myc:
> ./compil.sh [nom.myc]

Pour test le compilateur qui génère les .c et .h des .myc se trouvant dans
le dossier test:
> ./compil_test.sh

Pour des tests à la main sur le pseudo-compilateur:
> cd src/
> make
> ./lang

./lang ouvre l'interpréteur de code .myc.

Pour plus de clarté, nous avons écrit des fonctions annexes se trouvant dans
display.c majoritairement.

## Commentaires:
- Ayant mal compris comment le compilateur devait traiter les structures,
  c'est à dire par exemple renvoyer:
    char var[8]; pour struct var{int x, int y};
  Nous renvoyons la même structure qu'en C, ce qui est opposé à ce qu'il
  fallait faire
- Pour affecter une valeur à un attribut d'une structure, la grammaire ne
  semble pas le permettre.
  Pour cela nous avons ajouter la règle ligne 322 (exp ARR ID EQ exp) pour
  réaliser les affectations du genre:
    variable->attribut = qq chose;
  Mais cette dernière génère des warnings: 13 shift/reduce conflicts, dont
  on ne sait résoudre
  Actuellement, le code compile et fonctionne avec, cela ne semble pas être
  un problème, mais nous le spécifions quand même.
- L'affectation des champs d'une structure doit respecter strictement l'égalité
  des types (c'est seulement pour la structure, le cast explicite étant
  implémenté pour le reste)
- Les attributs locales définies dans les fonctions ne sont pas libérés lorsque
  l'on sort de ces dernières afin de pouvoir les réutilisées.


## Liste des choses non implémentées:
- Structures en code 3 adresses (implémenté en C ici)
- Vérification de la correspondance du type de retour d'une fonction
- Set de test pour les fonctions
