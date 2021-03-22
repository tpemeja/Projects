DELIMITER $$

-- Enlève le lien Joueur-Deck pour tous les joueurs ne possèdant pas assez d'exemplaires de la carte passée en paramètre pour réaliser ce deck
CREATE PROCEDURE enleve_joueurs_possedant_pas_assez(In MyNoDeck INT,IN MyNoCarte INT, IN MyNbExemplaires INT)
BEGIN
  DELETE FROM AvoirDeck WHERE
    NoDeck = MyNoDeck AND
    NoJoueur IN
    (SELECT NoJoueur FROM
      (SELECT NoJoueur, SUM(NbExemplaires) as Possedes FROM
        (Obtentions NATURAL JOIN Possessions)
        WHERE NoCarte = MyNoCarte
        GROUP BY NoJoueur HAVING Possedes < MyNbExemplaires)
      as C);
END$$

-- Enlève le lien Joueur-Deck pour tous les decks demandant plus d'exemplaires de la carte passée en paramètre que le jouer possède
CREATE PROCEDURE enleve_incompatible_decks(In MyNoJoueur INT, IN MyNoCarte INT)
BEGIN
  DECLARE exemplaires INT;
  SET exemplaires = (SELECT SUM(NbExemplaires) FROM (Obtentions NATURAL JOIN Possessions) WHERE NoJoueur = MyNoJoueur and NoCarte = MyNoCarte);

  DELETE FROM AvoirDeck WHERE
    NoJoueur = MyNoJoueur AND
    NoDeck IN
    (SELECT NoDeck FROM
      ((Decks NATURAL JOIN
        (SELECT * FROM AvoirDeck WHERE NoJoueur = MyNoJoueur) as T1)
      NATURAL JOIN
        (SELECT * FROM DeckComposition WHERE NoCarte = MyNoCarte) as T2)
      WHERE NbExemplaires > exemplaires);
END$$


CREATE PROCEDURE joueur_a_pas_carte_decks(IN MyNoDeck INT, IN MyNoJoueur INT, OUT MyOutput INT)
BEGIN
  SELECT COUNT(*) INTO MyOutput FROM
    ((SELECT NoCarte, NbExemplaires FROM DeckComposition WHERE NoDeck = MyNoDeck) as T1
      LEFT JOIN
    (SELECT NoCarte, SUM(NbExemplaires) as Possedes FROM
      ((SELECT NoJoueur, NoObtention FROM Obtentions WHERE NoJoueur = MyNoJoueur) as T2
      NATURAL JOIN Possessions)
      GROUP BY NoCarte
    ) as T3
    ON (T1.NoCarte = T3.NoCarte))
    WHERE T3.NoCarte IS NULL OR NbExemplaires > Possedes;
END$$

DELIMITER ;
