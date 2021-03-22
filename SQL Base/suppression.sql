-- ============================================================
--   Nom de la base   :  Cartes canard à collectionner
--   Nom de SGBD      :  ORACLE Version 7.0
--   Date de creation :  30/10/96  12:09
-- ============================================================

-- Suppression des procedures
DROP PROCEDURE IF EXISTS enleve_joueurs_possedant_pas_assez;
DROP PROCEDURE IF EXISTS enleve_incompatible_decks;

-- Suppression des triggers
DROP TRIGGER IF EXISTS obtention_suppression;
DROP TRIGGER IF EXISTS version_suppression;
DROP TRIGGER IF EXISTS carte_suppression;
DROP TRIGGER IF EXISTS deck_suppression;
DROP TRIGGER IF EXISTS joueur_suppression;
DROP TRIGGER IF EXISTS partie_suppression;
DROP TRIGGER IF EXISTS carte_ajout_deck;
DROP TRIGGER IF EXISTS carte_qte_maj_deck;
DROP TRIGGER IF EXISTS carte_qte_maj_joueur;
DROP TRIGGER IF EXISTS possession_suppression;
DROP TRIGGER IF EXISTS new_possession;
DROP TRIGGER IF EXISTS new_avoir_deck;
DROP TRIGGER IF EXISTS upd_avoir_deck;

-- Suppression des tables

SET FOREIGN_KEY_CHECKS = 0;

DROP TABLE IF EXISTS Parties cascade;

DROP TABLE IF EXISTS PartieParticipation cascade;

DROP TABLE IF EXISTS Joueurs cascade;

DROP TABLE IF EXISTS Obtentions cascade;

DROP TABLE IF EXISTS Possessions cascade;

DROP TABLE IF EXISTS Versions cascade;

DROP TABLE IF EXISTS Cartes cascade;

DROP TABLE IF EXISTS VersionCartes cascade;

DROP TABLE IF EXISTS Decks cascade;

DROP TABLE IF EXISTS DeckComposition cascade;

DROP TABLE IF EXISTS AvoirDeck cascade;

SET FOREIGN_KEY_CHECKS = 1;
