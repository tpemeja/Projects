DELIMITER $$

-- Suppression d'une version ------------------------------------------------
CREATE TRIGGER obtention_suppression
BEFORE DELETE
ON Obtentions FOR EACH ROW
BEGIN
  -- On supprime les liens avec Possessions
  DELETE FROM Possessions WHERE NoObtention = OLD.NoObtention;
END$$

-- Suppression d'une version ------------------------------------------------
CREATE TRIGGER version_suppression
BEFORE DELETE
ON Versions FOR EACH ROW
BEGIN
  -- On met à jour Possessions
  UPDATE Possessions SET
      NoVersion = 1
  WHERE NoVersion = OLD.NoVersion;
  -- On met à jour VersionCartes
  UPDATE VersionCartes SET
      NoVersion = 1
  WHERE NoVersion = OLD.NoVersion;
END$$

-- Suppression d'une carte ------------------------------------------------
CREATE TRIGGER carte_suppression
BEFORE DELETE
ON Cartes FOR EACH ROW
BEGIN
  -- On supprime les liens avec VersionObtentions
  DELETE FROM VersionCartes WHERE NoCarte = OLD.NoCarte;
  -- On supprime les liens avec DeckComposition
  DELETE FROM DeckComposition WHERE NoCarte = OLD.NoCarte;
  -- On met à jour Possessions
  UPDATE Possessions SET
      NoCarte = 1
  WHERE NoCarte = OLD.NoCarte;
END$$

-- Suppression d'un deck -------------------------------------------------
CREATE TRIGGER deck_suppression
BEFORE DELETE
ON Decks FOR EACH ROW
BEGIN
  -- On supprime les liens avec AvoirDeck
  DELETE FROM AvoirDeck WHERE NoDeck = OLD.NoDeck;
  -- On supprime les liens avec DeckComposition
  DELETE FROM DeckComposition WHERE NoDeck = OLD.NoDeck;
  -- On met à jour le lien dans PartieParticipation
  UPDATE PartieParticipation SET
      NoDeck = 1
  WHERE NoDeck = OLD.NoDeck;
END$$

-- Suppression d'un joueur -----------------------------------------------------
CREATE TRIGGER joueur_suppression
BEFORE DELETE
ON Joueurs FOR EACH ROW
BEGIN
  -- On met à jour Parties
  UPDATE Parties SET
      NoJoueurGagnant = 1
  WHERE NoJoueurGagnant = OLD.NoJoueur;
  UPDATE Parties SET
      NoJoueurPerdant = 1
  WHERE NoJoueurPerdant = OLD.NoJoueur;
  -- On met à jour PartieParticipation
  UPDATE PartieParticipation SET
    NoJoueur = 1
  WHERE NoJoueur = OLD.NoJoueur;
  -- On supprime les liens avec les decks
  DELETE FROM AvoirDeck WHERE NoJoueur = OLD.NoJoueur;
  -- On supprime les liens avec obtentions
  DELETE FROM Obtentions WHERE NoJoueur = OLD.NoJoueur;
END$$

-- Suppression d'une partie ------------------------------------------------
CREATE TRIGGER partie_suppression
BEFORE DELETE
ON Parties FOR EACH ROW
BEGIN
  -- On supprime les liens avec PartieParticipation
  DELETE FROM PartieParticipation WHERE NoPartie = OLD.NoPartie;
END$$

-- Ajout d'une carte à un deck ------------------------------------------------
CREATE TRIGGER carte_ajout_deck
BEFORE INSERT
ON DeckComposition FOR EACH ROW
BEGIN
  CALL enleve_joueurs_possedant_pas_assez(NEW.NoDeck, NEW.NoCarte, NEW.NbExemplaires);
END$$

-- Mise a jour de la quantité d'une carte dans un deck -------------------------
CREATE TRIGGER carte_qte_maj_deck
BEFORE UPDATE
ON DeckComposition FOR EACH ROW
BEGIN
  CALL enleve_joueurs_possedant_pas_assez(NEW.NoDeck, NEW.NoCarte, NEW.NbExemplaires);
END$$

-- Mise a jour de la quantité d'une carte d'un joueur --------------------------
CREATE TRIGGER carte_qte_maj_joueur
BEFORE UPDATE
ON Possessions FOR EACH ROW
BEGIN
  DECLARE MyNoJoueur INT;
  SET MyNoJoueur = (SELECT NoJoueur FROM Obtentions WHERE NoObtention = OLD.NoObtention);
  CALL enleve_incompatible_decks(MyNoJoueur, OLD.NoCarte);
END$$

-- Mise a jour de la quantité d'une carte  d'un joueur -------------------------
CREATE TRIGGER possession_suppression
BEFORE DELETE
ON Possessions FOR EACH ROW
BEGIN
  DECLARE MyNoJoueur INT;
  SET MyNoJoueur = (SELECT NoJoueur FROM Obtentions WHERE NoObtention = OLD.NoObtention);
  CALL enleve_incompatible_decks(MyNoJoueur, OLD.NoCarte);
END$$

-- Nouvelle obtention ----------------------------------------------------------
CREATE TRIGGER new_possession
BEFORE INSERT
ON Possessions FOR EACH ROW
BEGIN
  DECLARE exist INT;
  SET exist = (SELECT COUNT(*) FROM VersionCartes WHERE NoCarte = NEW.NoCarte AND NoVersion = New.NoVersion);
  IF exist <= 0 THEN
    signal sqlstate '45000';
  END IF;
END$$


-- Nouveau deck ----------------------------------------------------------------
CREATE TRIGGER new_avoir_deck
BEFORE INSERT
ON AvoirDeck FOR EACH ROW
BEGIN
  DECLARE exist INT;
  CALL joueur_a_pas_carte_decks(New.NoDeck, New.NoJoueur, @exist);
  IF exist > 0 THEN
    signal sqlstate '45000';
  END IF;
END$$

-- Nouveau deck ----------------------------------------------------------------
CREATE TRIGGER upd_avoir_deck
BEFORE UPDATE
ON AvoirDeck FOR EACH ROW
BEGIN
  DECLARE exist INT;
  CALL joueur_a_pas_carte_decks(New.NoDeck, New.NoJoueur, @exist);
  IF exist > 0 THEN
    signal sqlstate '45000';
  END IF;
END$$


DELIMITER ;
