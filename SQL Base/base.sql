-- ============================================================
--   Nom de la base   :  Cartes canard à collectionner
--   Nom de SGBD      :  ORACLE Version 7.0
--   Date de creation :  30/10/96  12:09
-- ============================================================
-- Parties(_NoPartie, Lieu, DatePartie, Type, #NoJoueurGagnant,
--         #NoJoueurPerdant)
-- PartieParticipation(_#NoPartie, _#NoJoueur, #NoDeck)
-- Joueurs(_NoJoueur, Nom, Prenom, Pseudonyme)
-- Obtentions(Date_Acquisition, Moyen_Acquisition, Prix_achat, #NoJoueur)
-- Possessions(_#NoObtention, _#NoCarte, _#NoVersion, _Etat, NbExemplaires)
-- Versions(_NoVersion, DateImpression, Rendu, Tirage)
-- Cartes(_NoCarte, Titre, Description, Type, Famille, Attaque,
--        Defense)
-- VersionCartes(_#NoCarte, _#NoVersion, Cote)
-- Decks(_NoDeck, Titre, Description, Type, Famille)
-- DeckComposition(_#NoDeck, _#NoCarte, NbExemplaires)
-- AvoirDeck(_#NoJoueur, _#NoDeck)

-- ============================================================
--   Table : Joueurs
-- ============================================================
create table Joueurs
(
    NoJoueur                        INT    PRIMARY KEY  AUTO_INCREMENT ,
    Nom                             VARCHAR(20)                        ,
    Prenom                          VARCHAR(20)                        ,
    Pseudonyme                      VARCHAR(20) UNIQUE
) ENGINE = InnoDB;

-- ============================================================
--   Table : Parties
-- ============================================================
create table Parties
(
    NoPartie                        INT    PRIMARY KEY  AUTO_INCREMENT ,
    Lieu                            VARCHAR(20)                       ,
    DatePartie                      DATE                              ,
    Type                            VARCHAR(20)                       ,
    NoJoueurGagnant                 INT                       NOT NULL,
    NoJoueurPerdant                 INT                       NOT NULL,
    foreign KEY(NoJoueurGagnant) references Joueurs(NoJoueur)         ,
    foreign KEY(NoJoueurPerdant) references Joueurs(NoJoueur)
) ENGINE = InnoDB;



-- ============================================================
--   Table : Versions
-- ============================================================
create table Versions
(
    NoVersion                       INT    PRIMARY KEY  AUTO_INCREMENT ,
    DateImpression                  DATE                              ,
    Rendu                           VARCHAR(20)                       ,
    Tirage                          INT
) ENGINE = InnoDB;

-- ============================================================
--   Table : Cartes
-- ============================================================
create table Cartes
(
    NoCarte                         INT  PRIMARY KEY    AUTO_INCREMENT ,
    Titre                           VARCHAR(50)                       ,
    Description                     VARCHAR(100)                       ,
    Type                            VARCHAR(20)                       ,
    Famille                         VARCHAR(20)                       ,
    Attaque                         INT                               ,
    Defense                         INT
) ENGINE = InnoDB;

-- ============================================================
--   Table : VersionCartes
-- ============================================================
create table VersionCartes
(
    NoCarte                         INT                       NOT NULL,
    NoVersion                       INT                       NOT NULL,
    Cote                            INT                               ,
    foreign KEY(NoCarte) references Cartes(NoCarte)                   ,
    foreign KEY(NoVersion) references Versions(NoVersion)             ,
    PRIMARY KEY (NoCarte, NoVersion)
) ENGINE = InnoDB;

-- ============================================================
--   Table : Obtentions
-- ============================================================
create table Obtentions
(
    NoObtention                     INT    PRIMARY KEY  AUTO_INCREMENT ,
    Date_Acquisition                DATE                              ,
    Moyen_Acquisition               VARCHAR(20)                       ,
    Prix_achat                      INT                               ,
    NoJoueur                        INT                       NOT NULL,
    foreign KEY(NoJoueur) references Joueurs(NoJoueur)
) ENGINE = InnoDB;


-- ============================================================
--   Table : Possessions
-- ============================================================
create table Possessions
(
    NoObtention                     INT                       NOT NULL,
    NoCarte                         INT                       NOT NULL,
    NoVersion                       INT                       NOT NULL,
    Etat                            INT                       NOT NULL,
    NbExemplaires                   INT                       NOT NULL,
    foreign KEY(NoObtention) references Obtentions(NoObtention)       ,
    foreign KEY(NoCarte) references Cartes(NoCarte)                   ,
    foreign KEY(NoVersion) references Versions(NoVersion)             ,
    PRIMARY KEY (NoObtention, NoCarte, NoVersion, Etat)
) ENGINE = InnoDB;

-- ============================================================
--   Table : Decks
-- ============================================================
create table Decks
(
    NoDeck                          INT   PRIMARY KEY  AUTO_INCREMENT  ,
    Titre                           VARCHAR(40)                       ,
    Description                     VARCHAR(40)
) ENGINE = InnoDB;

-- ============================================================
--   Table : DeckComposition
-- ============================================================
create table DeckComposition
(
    NoDeck                          INT                       NOT NULL,
    NoCarte                         INT                       NOT NULL,
    NbExemplaires                   INT                               ,
    foreign KEY(NoDeck) references Decks(NoDeck),
    foreign KEY(NoCarte) references Cartes(NoCarte),
    PRIMARY KEY (NoDeck, NoCarte)
) ENGINE = InnoDB;

-- ============================================================
--   Table : AvoirDeck
-- ============================================================
create table AvoirDeck
(
    NoJoueur                        INT                       NOT NULL,
    NoDeck                          INT                       NOT NULL,
    foreign KEY(NoJoueur) references Joueurs(NoJoueur)                ,
    foreign KEY(NoDeck) references Decks(NoDeck)                      ,
    PRIMARY KEY (NoJoueur, NoDeck)
) ENGINE = InnoDB;

-- ============================================================
--   Table : PartieParticipation
-- ============================================================
create table PartieParticipation
(
    NoPartie                   INT                            NOT NULL,
    NoJoueur                   INT                            NOT NULL,
    NoDeck                     INT                            NOT NULL,
    foreign KEY(NoPartie) references Parties(NoPartie)                ,
    foreign KEY(NoJoueur) references Joueurs(NoJoueur)                ,
    foreign KEY(NoDeck) references Decks(NoDeck)                      ,
    PRIMARY KEY (NoPartie, NoJoueur)
) ENGINE = InnoDB;
