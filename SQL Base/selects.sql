-- Cartes ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
---- classées par utilisation dans les decks -----------------------------------
SELECT Cartes.*, COUNT(*) as NbUses FROM ((Cartes NATURAL JOIN DeckComposition) NATURAL JOIN AvoirDeck) GROUP BY NoCarte ORDER BY NbUses DESC;
---- classées par nombres de possesseurs ---------------------------------------
SELECT Cartes.*, COUNT(*) as NbOwners FROM (Cartes NATURAL JOIN (Possessions NATURAL JOIN Obtentions)) GROUP BY NoCarte ORDER BY NbOwners DESC;
---- dans aucun deck -----------------------------------------------------------
SELECT T1.* FROM ((SELECT * FROM Cartes) as T1 LEFT JOIN
(SELECT Cartes.* FROM (Cartes NATURAL JOIN DeckComposition) WHERE NbExemplaires >= 0) as T2 ON (T1.NoCarte = T2.NoCarte)) WHERE T2.NoCarte IS NULL;
-- Joueurs +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
-- par parties ---------------------------------------------------------------
---- jouées ------------------------------------------------------------------
SELECT Joueurs.*, COUNT(*) as NbParties FROM (Joueurs NATURAL JOIN PartieParticipation) GROUP BY NoJoueur ORDER BY NbParties DESC;
---- gagnées -----------------------------------------------------------------
SELECT Joueurs.*, COUNT(*) as NbVictoires FROM (Parties LEFT JOIN PartieParticipation ON (PartieParticipation.NoJoueur = Parties.NoJoueurGagnant AND PartieParticipation.NoPartie = Parties.NoPartie) NATURAL JOIN Joueurs) GROUP BY Joueurs.NoJoueur ORDER BY NbVictoires DESC;
---- par collection ------------------------------------------------------------
---- valeur de celle-ci ------------------------------------------------------
SELECT Joueurs.*, SUM(T2.Valeur) as ValeurJoueur FROM (Joueurs NATURAL JOIN (SELECT *, Etat * Cote * NbExemplaires / 100 as Valeur FROM (VersionCartes NATURAL JOIN (Possessions NATURAL JOIN Obtentions))) as T2) GROUP BY NoJoueur ORDER BY ValeurJoueur DESC;
---- rareté de celle-ci ------------------------------------------------------
SELECT Joueurs.*, COUNT(*) as NbCartesRares FROM (Joueurs NATURAL JOIN((Possessions NATURAL JOIN Obtentions) NATURAL JOIN Versions)) WHERE Tirage < 100 OR DateImpression < '2000-01-01' GROUP BY NoJoueur ORDER BY NbCartesRares DESC;
---- nombre de cartes ----------------------------------------------------------
SELECT Joueurs.*, SUM(NbExemplaires) as NbCartes FROM (Joueurs NATURAL JOIN (Possessions NATURAL JOIN Obtentions)) GROUP BY NoJoueur ORDER BY NbCartes DESC;
---- collectionneurs (ceux qui ont fait 0 parties) -----------------------------
SELECT T1.* FROM
  ((SELECT * FROM Joueurs) as T1
LEFT JOIN
  (SELECT Joueurs.*, COUNT(*) as NbParties FROM
    (Joueurs NATURAL JOIN PartieParticipation)
    GROUP BY NoJoueur) as T2
ON (T1.NoJoueur = T2.NoJoueur)) WHERE T2.NoJoueur IS NULL;
-- Decks +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
---- par nombre de cartes ------------------------------------------------------
SELECT Decks.*, COUNT(*) as NbCartes FROM (Decks NATURAL JOIN DeckComposition) GROUP BY NoDeck ORDER BY NbCartes DESC;
---- par nombre d'utilisateurs -------------------------------------------------
SELECT Decks.*, COUNT(*) as NbUses FROM (Decks NATURAL JOIN AvoirDeck) GROUP BY NoDeck ORDER BY NbUses DESC;
