-- ============================================================
--    creation des donnees
-- ============================================================

-- Joueurs

insert into Joueurs(Nom, Prenom, Pseudonyme) values ( ''     , ''     , 'Supprimé'  ) ;
insert into Joueurs(Nom, Prenom, Pseudonyme) values ( 'Kisha'     , 'J. Murray'     , 'Parker'  ) ;
insert into Joueurs(Nom, Prenom, Pseudonyme) values ( 'Melusina'    , 'Potvin'    , 'Seymour'  ) ;
insert into Joueurs(Nom, Prenom, Pseudonyme) values ( 'Ferrau'    , 'Desforges'    , 'Gougeon'  ) ;
insert into Joueurs(Nom, Prenom, Pseudonyme) values ( 'Trinette'    , 'Tremblay'    , 'Sepulveda'  ) ;
insert into Joueurs(Nom, Prenom, Pseudonyme) values ( 'Louis'    , 'Chabot'    , 'Walnut'  ) ;
insert into Joueurs(Nom, Prenom, Pseudonyme) values ( 'Constance'    , 'Bisson'    , 'Lafond'  ) ;
insert into Joueurs(Nom, Prenom, Pseudonyme) values ( 'Fealty'    , 'L\'Angelier'    , 'Waldo'  ) ;
insert into Joueurs(Nom, Prenom, Pseudonyme) values ( 'Chandler'    , 'Audet'    , 'Paquin'  ) ;
insert into Joueurs(Nom, Prenom, Pseudonyme) values ( 'Constance'    , 'Lauzier'    , 'Arsenault'  ) ;
insert into Joueurs(Nom, Prenom, Pseudonyme) values ( 'Eliot'    , 'Lachapelle'    , 'Shearwood'  ) ;
insert into Joueurs(Nom, Prenom, Pseudonyme) values ( 'Donatien'    , 'Émond'    , 'Keyser'  ) ;
insert into Joueurs(Nom, Prenom, Pseudonyme) values ( 'Aubrey'    , 'Barrientos'    , 'Drainer'  ) ;
insert into Joueurs(Nom, Prenom, Pseudonyme) values ( 'Germain'    , 'Lebrun'    , 'Strother'  ) ;
insert into Joueurs(Nom, Prenom, Pseudonyme) values ( 'Peverell'    , 'Laramée'    , 'Polk'  ) ;
insert into Joueurs(Nom, Prenom, Pseudonyme) values ( 'Fanchon'    , 'Jobin'    , 'Broubtrall'  ) ;


commit ;

-- Parties
insert into Parties(Lieu, DatePartie, Type, NoJoueurGagnant, NoJoueurPerdant ) values ( 'BORDEAUX'   , '2015-03-01' , 'NORMAL'  , 8 , 3) ;
insert into Parties(Lieu, DatePartie, Type, NoJoueurGagnant, NoJoueurPerdant ) values ( 'NANTES'   , '2011-01-06' , 'RANKED'  , 3 , 4) ;
insert into Parties(Lieu, DatePartie, Type, NoJoueurGagnant, NoJoueurPerdant ) values ( 'SAINT-DENIS'   , '2015-06-02' , 'DRAFT'  , 11 , 5) ;
insert into Parties(Lieu, DatePartie, Type, NoJoueurGagnant, NoJoueurPerdant ) values ( 'COGNAC'   , '2009-12-27' , 'NORMAL'  , 10 , 3) ;
insert into Parties(Lieu, DatePartie, Type, NoJoueurGagnant, NoJoueurPerdant ) values ( 'ORLÉANS'   , '2008-02-29' , 'DRAFT'  , 4 , 9) ;
insert into Parties(Lieu, DatePartie, Type, NoJoueurGagnant, NoJoueurPerdant ) values ( 'MILLAU'   , '2014-09-25' , 'RANKED'  , 12 , 3) ;
insert into Parties(Lieu, DatePartie, Type, NoJoueurGagnant, NoJoueurPerdant ) values ( 'MAISONS-LAFFITTE'   , '2019-07-13' , 'RANKED'  , 13 , 5) ;
insert into Parties(Lieu, DatePartie, Type, NoJoueurGagnant, NoJoueurPerdant ) values ( 'LA COURNEUVE'   , '2012-07-12' , 'RANKED'  , 3 , 2) ;
insert into Parties(Lieu, DatePartie, Type, NoJoueurGagnant, NoJoueurPerdant ) values ( 'ISSY-LES-MOULINEAUX'   , '2008-10-30' , 'NORMAL'  , 16 , 7) ;
insert into Parties(Lieu, DatePartie, Type, NoJoueurGagnant, NoJoueurPerdant ) values ( 'MONTAUBAN'   , '2018-05-28' , 'DRAFT'  , 11 , 8) ;
insert into Parties(Lieu, DatePartie, Type, NoJoueurGagnant, NoJoueurPerdant ) values ( 'LE PUY-EN-VELAY'   , '2007-07-08' , 'RANKED'  , 8 , 3) ;
insert into Parties(Lieu, DatePartie, Type, NoJoueurGagnant, NoJoueurPerdant ) values ( 'RENNES'   , '2008-04-25' , 'RANKED'  , 12 , 3) ;
insert into Parties(Lieu, DatePartie, Type, NoJoueurGagnant, NoJoueurPerdant ) values ( 'BOURGOIN-JALLIEU'   , '2008-02-28' , 'RANKED'  , 3 , 15) ;
insert into Parties(Lieu, DatePartie, Type, NoJoueurGagnant, NoJoueurPerdant ) values ( 'SAINT-JOSEPH'   , '2008-06-10' , 'NORMAL'  , 5 , 3) ;
insert into Parties(Lieu, DatePartie, Type, NoJoueurGagnant, NoJoueurPerdant ) values ( 'MONT-DE-MARSAN'   , '2009-10-20' , 'NORMAL'  , 9 , 3) ;
insert into Parties(Lieu, DatePartie, Type, NoJoueurGagnant, NoJoueurPerdant ) values ( 'BESANÇON'   , '2014-02-04' , 'RANKED'  , 2 , 3) ;
insert into Parties(Lieu, DatePartie, Type, NoJoueurGagnant, NoJoueurPerdant ) values ( 'ÉVREUX'   , '2013-07-20' , 'DRAFT'  , 15 , 2) ;
insert into Parties(Lieu, DatePartie, Type, NoJoueurGagnant, NoJoueurPerdant ) values ( 'NANTES'   , '2019-05-10' , 'RANKED'  , 3 , 13) ;
insert into Parties(Lieu, DatePartie, Type, NoJoueurGagnant, NoJoueurPerdant ) values ( 'VILLENEUVE-D\'ASCQ'   , '2016-01-23' , 'RANKED'  , 12 , 2) ;
insert into Parties(Lieu, DatePartie, Type, NoJoueurGagnant, NoJoueurPerdant ) values ( 'LES ULIS'   , '2008-06-12' , 'NORMAL'  , 4 , 3) ;
insert into Parties(Lieu, DatePartie, Type, NoJoueurGagnant, NoJoueurPerdant ) values ( 'LYON'   , '2011-05-16' , 'RANKED'  , 7 , 3) ;
insert into Parties(Lieu, DatePartie, Type, NoJoueurGagnant, NoJoueurPerdant ) values ( 'ISSY-LES-MOULINEAUX'   , '2008-10-30' , 'NORMAL'  , 7 , 16) ;
insert into Parties(Lieu, DatePartie, Type, NoJoueurGagnant, NoJoueurPerdant ) values ( 'BORDEAUX'   , '2015-04-02' , 'NORMAL'  , 2 , 8) ;
insert into Parties(Lieu, DatePartie, Type, NoJoueurGagnant, NoJoueurPerdant ) values ( 'MONTAUBAN'   , '2017-02-18' , 'RANKED'  , 4 , 2) ;
insert into Parties(Lieu, DatePartie, Type, NoJoueurGagnant, NoJoueurPerdant ) values ( 'BOURGOIN-JALLIEU'   , '2008-02-28' , 'DRAFT'  , 3 , 15) ;
insert into Parties(Lieu, DatePartie, Type, NoJoueurGagnant, NoJoueurPerdant ) values ( 'NANTES'   , '2008-06-01' , 'DRAFT'  , 5 , 6) ;
insert into Parties(Lieu, DatePartie, Type, NoJoueurGagnant, NoJoueurPerdant ) values ( 'TOULOUSE'   , '2008-05-12' , 'NORMAL'  , 5 , 12) ;
insert into Parties(Lieu, DatePartie, Type, NoJoueurGagnant, NoJoueurPerdant ) values ( 'PARIS'   , '2008-11-07' , 'NORMAL'  , 5 , 12) ;
insert into Parties(Lieu, DatePartie, Type, NoJoueurGagnant, NoJoueurPerdant ) values ( 'MONTAUBAN'   , '2018-02-11' , 'RANKED'  , 11 , 4) ;



commit ;

-- Versions
insert into Versions(DateImpression, Rendu, Tirage) values ( '1970-01-01' , '' , 0) ;

insert into Versions(DateImpression, Rendu, Tirage) values ( '2006-12-17' , 'BRILLANT'  , 1000 ) ;
insert into Versions(DateImpression, Rendu, Tirage) values ( '2006-12-17' , 'ARGENTE'  , 500 ) ;
insert into Versions(DateImpression, Rendu, Tirage) values ( '2006-12-17' , 'DORE'  , 200) ;

insert into Versions(DateImpression, Rendu, Tirage) values ( '2006-12-17' , 'NORMAL'  , 4000 ) ;
insert into Versions(DateImpression, Rendu, Tirage) values ( '2006-12-17' , 'BRILLANT'  , 800 ) ;
insert into Versions(DateImpression, Rendu, Tirage) values ( '2006-12-17' , 'ARGENTE'  , 380 ) ;

insert into Versions(DateImpression, Rendu, Tirage) values ( '2006-12-17' , 'NORMAL'  , 6700 ) ;
insert into Versions(DateImpression, Rendu, Tirage) values ( '2006-12-17' , 'BRILLANT'  , 1300 ) ;
insert into Versions(DateImpression, Rendu, Tirage) values ( '2006-12-17' , 'ARGENTE'  , 750 ) ;
insert into Versions(DateImpression, Rendu, Tirage) values ( '2006-12-17' , 'DORE'  , 10 ) ;

insert into Versions(DateImpression, Rendu, Tirage) values ( '2006-12-17' , 'NORMAL'  , 4500 ) ;
insert into Versions(DateImpression, Rendu, Tirage) values ( '2006-12-17' , 'BRILLANT'  , 1000 ) ;
insert into Versions(DateImpression, Rendu, Tirage) values ( '2006-12-17' , 'ARGENTE'  , 400 ) ;
insert into Versions(DateImpression, Rendu, Tirage) values ( '2006-12-17' , 'DORE'  , 200) ;

insert into Versions(DateImpression, Rendu, Tirage) values ( '2006-12-17' , 'NORMAL'  , 4500 ) ;
insert into Versions(DateImpression, Rendu, Tirage) values ( '2006-12-17' , 'BRILLANT'  , 1000 ) ;
insert into Versions(DateImpression, Rendu, Tirage) values ( '2006-12-17' , 'ARGENTE'  , 400 ) ;

insert into Versions(DateImpression, Rendu, Tirage) values ( '2006-12-17' , 'NORMAL'  , 6000 ) ;
insert into Versions(DateImpression, Rendu, Tirage) values ( '2006-12-17' , 'BRILLANT'  , 400 ) ;

insert into Versions(DateImpression, Rendu, Tirage) values ( '2009-01-15' , 'NORMAL'  , 1000 ) ;
insert into Versions(DateImpression, Rendu, Tirage) values ( '2009-01-15' , 'BRILLANT'  , 500 ) ;
insert into Versions(DateImpression, Rendu, Tirage) values ( '2009-01-15' , 'ARGENTE'  ,300 ) ;
insert into Versions(DateImpression, Rendu, Tirage) values ( '2009-01-15' , 'DORE'  , 10) ;

insert into Versions(DateImpression, Rendu, Tirage) values ( '2009-01-15' , 'NORMAL'  , 4000 ) ;
insert into Versions(DateImpression, Rendu, Tirage) values ( '2009-01-15' , 'BRILLANT'  , 80 ) ;
insert into Versions(DateImpression, Rendu, Tirage) values ( '2009-01-15' , 'ARGENTE'  ,50 ) ;
insert into Versions(DateImpression, Rendu, Tirage) values ( '2009-01-15' , 'DORE'  , 1) ;

insert into Versions(DateImpression, Rendu, Tirage) values ( '2009-01-15' , 'BRILLANT'  , 2000 ) ;
insert into Versions(DateImpression, Rendu, Tirage) values ( '2009-01-15' , 'ARGENTE'  ,400 ) ;

insert into Versions(DateImpression, Rendu, Tirage) values ( '2009-01-15' , 'NORMAL'  , 5000 ) ;
insert into Versions(DateImpression, Rendu, Tirage) values ( '2009-01-15' , 'BRILLANT'  , 100 ) ;

insert into Versions(DateImpression, Rendu, Tirage) values ( '2009-01-15' , 'NORMAL'  , 7000 ) ;

insert into Versions(DateImpression, Rendu, Tirage) values ( '2009-01-15' , 'DORE'  , 40 ) ;

insert into Versions(DateImpression, Rendu, Tirage) values ( '2019-10-13' , 'ARGENTE'  , 500 ) ;
insert into Versions(DateImpression, Rendu, Tirage) values ( '2019-10-13' , 'DORE'  , 200) ;

insert into Versions(DateImpression, Rendu, Tirage) values ( '2019-10-13' , 'NORMAL'  , 4000 ) ;
insert into Versions(DateImpression, Rendu, Tirage) values ( '2019-10-13' , 'BRILLANT'  , 1000 ) ;

insert into Versions(DateImpression, Rendu, Tirage) values ( '2019-10-13' , 'NORMAL'  , 7000 ) ;
insert into Versions(DateImpression, Rendu, Tirage) values ( '2019-10-13' , 'BRILLANT'  , 500 ) ;
insert into Versions(DateImpression, Rendu, Tirage) values ( '2019-10-13' , 'ARGENTE'  , 100 ) ;
insert into Versions(DateImpression, Rendu, Tirage) values ( '2019-10-13' , 'DORE'  , 10) ;

insert into Versions(DateImpression, Rendu, Tirage) values ( '2019-10-13' , 'ARGENTE'  , 1500 ) ;
insert into Versions(DateImpression, Rendu, Tirage) values ( '2019-10-13' , 'DORE'  , 100) ;

insert into Versions(DateImpression, Rendu, Tirage) values ( '2019-10-13' , 'ARGENTE'  , 800) ;


commit ;

-- Cartes

insert into Cartes(Titre, Description, Type, Famille, Attaque, Defense) values ( 'Supprimé' , ' ' ,'' ,'', 0, 0 ) ;
insert into Cartes(Titre, Description, Type, Famille, Attaque, Defense) values ( 'Coin-Coin aux yeux bleus' , 'Je suis très méchant !' ,'Monstre' ,'Canard dragon', 3000, 2500 ) ;
insert into Cartes(Titre, Description, Type, Famille, Attaque, Defense) values ( 'Coin-Coin ultime aux yeux bleus' , 'Je suis encore plus méchant !' ,'Monstre évolution' ,'Canard dragon', 4500, 3000 ) ;
insert into Cartes(Titre, Description, Type, Famille, Attaque, Defense) values ( 'Inspecteur magret' , 'Le plus grand des canardtectives' ,'Monstre à effet' ,'Canard à lunettes', 1800, 1000 ) ;
insert into Cartes(Titre, Description, Type, Famille, Attaque, Defense) values ( 'Le vilain petit caneton' , 'Rejeté de tous, il saura revenir pour se venger' ,'Monstre' ,'Canard normal', 500, 300 ) ;
insert into Cartes(Titre, Description, Type, Famille, Attaque, Defense) values ( 'Canard Fresh Disc' , 'Plus fort que Harpic et Mr Propre' ,'Monstre à effet' ,'Canard toxique', 400, 2000 ) ;
insert into Cartes(Titre, Description, Type, Famille, Attaque, Defense) values ( 'La pêche au canard' , 'Beaucoup confondent ce fruit sucré avec l\'activité sportive' ,'Monstre' ,'Canard comestible', 1800, 1300 ) ;
insert into Cartes(Titre, Description, Type, Famille, Attaque, Defense) values ( 'Le jeu de l\'oie' , 'Un imposteur qui saura tromper les moins vigilants' ,'Monstre' ,'Canard à lunettes', 1350, 1900 ) ;
insert into Cartes(Titre, Description, Type, Famille, Attaque, Defense) values ( 'Supercanard' , 'On le confond souvent avec son homologue humain à cause son slip rouge' ,'Monstre' ,'Canard volant', 2200, 1700 ) ;
insert into Cartes(Titre, Description, Type, Famille, Attaque, Defense) values ( 'Riri' , 'Unis ils seront plus forts' ,'Monstre à effet' ,'Canard normal', 800, 500 ) ;
insert into Cartes(Titre, Description, Type, Famille, Attaque, Defense) values ( 'Fifi' , 'Unis ils seront plus forts' ,'Monstre à effet' ,'Canard normal', 800, 500 ) ;
insert into Cartes(Titre, Description, Type, Famille, Attaque, Defense) values ( 'Loulou' , 'Unis ils seront plus forts' ,'Monstre à effet' ,'Canard normal', 800, 500 ) ;
insert into Cartes(Titre, Description, Type, Famille, Attaque, Defense) values ( 'Riri, fifi, Loulou' , 'A deux on est plus fort alors imaginez à trois' ,'Monstre à effet' ,'Canard normal', 3400, 2500 ) ;


commit ;

-- Obtentions

insert into Obtentions(Date_Acquisition, Moyen_Acquisition, Prix_achat, NoJoueur) values ( '2016-04-02' , 'PACK PANINI'  , 250  , 2 ) ;
insert into Obtentions(Date_Acquisition, Moyen_Acquisition, Prix_achat, NoJoueur) values ( '2016-04-02' , 'PACK PANINI'  , 250  , 2 ) ;
insert into Obtentions(Date_Acquisition, Moyen_Acquisition, Prix_achat, NoJoueur) values ( '2017-05-04' , 'REVENTE'      , 250  , 3 ) ;
insert into Obtentions(Date_Acquisition, Moyen_Acquisition, Prix_achat, NoJoueur) values ( '2011-03-15' , 'PACK KFC'     , 1050 , 4 ) ;
insert into Obtentions(Date_Acquisition, Moyen_Acquisition, Prix_achat, NoJoueur) values ( '2019-11-10' , 'PACK PANINI'  , 250  , 4 ) ;
insert into Obtentions(Date_Acquisition, Moyen_Acquisition, Prix_achat, NoJoueur) values ( '2009-11-03' , 'PACK TOURNOI' , 0    , 5 ) ;
insert into Obtentions(Date_Acquisition, Moyen_Acquisition, Prix_achat, NoJoueur) values ( '2014-01-30' , 'PACK KFC'     , 1050 , 6 ) ;
insert into Obtentions(Date_Acquisition, Moyen_Acquisition, Prix_achat, NoJoueur) values ( '2007-02-20' , 'PACK PANINI'  , 250  , 7 ) ;
insert into Obtentions(Date_Acquisition, Moyen_Acquisition, Prix_achat, NoJoueur) values ( '2013-10-31' , 'PACK PANINI'  , 250  , 8 ) ;
insert into Obtentions(Date_Acquisition, Moyen_Acquisition, Prix_achat, NoJoueur) values ( '2013-10-31' , 'PACK PANINI'  , 250  , 8 ) ;
insert into Obtentions(Date_Acquisition, Moyen_Acquisition, Prix_achat, NoJoueur) values ( '2019-10-15' , 'PACK PANINI'  , 250  , 9 ) ;
insert into Obtentions(Date_Acquisition, Moyen_Acquisition, Prix_achat, NoJoueur) values ( '2008-04-25' , 'PACK TOURNOI' , 0    , 10) ;
insert into Obtentions(Date_Acquisition, Moyen_Acquisition, Prix_achat, NoJoueur) values ( '2019-07-04' , 'PACK TOURNOI' , 0    , 11) ;
insert into Obtentions(Date_Acquisition, Moyen_Acquisition, Prix_achat, NoJoueur) values ( '2014-06-10' , 'PACK PANINI'  , 250  , 13) ;
insert into Obtentions(Date_Acquisition, Moyen_Acquisition, Prix_achat, NoJoueur) values ( '2013-10-31' , 'PACK TOURNOI' , 0    , 14) ;
insert into Obtentions(Date_Acquisition, Moyen_Acquisition, Prix_achat, NoJoueur) values ( '2019-07-04' , 'REVENTE'      , 250  , 15) ;
insert into Obtentions(Date_Acquisition, Moyen_Acquisition, Prix_achat, NoJoueur) values ( '2016-02-21' , 'PACK KFC'     , 1050 , 16) ;
insert into Obtentions(Date_Acquisition, Moyen_Acquisition, Prix_achat, NoJoueur) values ( '2019-11-21' , 'REVENTE'      , 850  , 16) ;


commit ;

-- Possessions

insert into Possessions(NoObtention, NoCarte, NoVersion, Etat, NbExemplaires) values ( 1 , 4 , 6 , 100, 2) ;
insert into Possessions(NoObtention, NoCarte, NoVersion, Etat, NbExemplaires) values ( 2 , 5 , 33, 100, 1) ;
insert into Possessions(NoObtention, NoCarte, NoVersion, Etat, NbExemplaires) values ( 3 , 8 , 13, 14 , 1) ;
insert into Possessions(NoObtention, NoCarte, NoVersion, Etat, NbExemplaires) values ( 3 , 8 , 13, 37 , 1) ;
insert into Possessions(NoObtention, NoCarte, NoVersion, Etat, NbExemplaires) values ( 4 , 11, 20, 100, 2) ;
insert into Possessions(NoObtention, NoCarte, NoVersion, Etat, NbExemplaires) values ( 5 , 9 , 43, 100, 3) ;
insert into Possessions(NoObtention, NoCarte, NoVersion, Etat, NbExemplaires) values ( 6 , 5 , 33, 100, 1) ;
insert into Possessions(NoObtention, NoCarte, NoVersion, Etat, NbExemplaires) values ( 7 , 5 , 33, 100, 2) ;
insert into Possessions(NoObtention, NoCarte, NoVersion, Etat, NbExemplaires) values ( 8 , 12, 22, 100, 3) ;
insert into Possessions(NoObtention, NoCarte, NoVersion, Etat, NbExemplaires) values ( 9 , 4 , 5 , 100, 2) ;
insert into Possessions(NoObtention, NoCarte, NoVersion, Etat, NbExemplaires) values ( 10, 4 , 7 , 100, 1) ;
insert into Possessions(NoObtention, NoCarte, NoVersion, Etat, NbExemplaires) values ( 11, 9 , 44, 100, 1) ;
insert into Possessions(NoObtention, NoCarte, NoVersion, Etat, NbExemplaires) values ( 12, 2 , 2 , 100, 3) ;
insert into Possessions(NoObtention, NoCarte, NoVersion, Etat, NbExemplaires) values ( 13, 8 , 12, 100, 4) ;
insert into Possessions(NoObtention, NoCarte, NoVersion, Etat, NbExemplaires) values ( 14, 13, 28, 100, 1) ;
insert into Possessions(NoObtention, NoCarte, NoVersion, Etat, NbExemplaires) values ( 15, 10, 17, 100, 2) ;
insert into Possessions(NoObtention, NoCarte, NoVersion, Etat, NbExemplaires) values ( 16, 5 , 33, 12 , 1) ;
insert into Possessions(NoObtention, NoCarte, NoVersion, Etat, NbExemplaires) values ( 17, 2 , 30, 100, 2) ;
insert into Possessions(NoObtention, NoCarte, NoVersion, Etat, NbExemplaires) values ( 18, 9 , 44, 90 , 2) ;
insert into Possessions(NoObtention, NoCarte, NoVersion, Etat, NbExemplaires) values ( 18, 7 , 40, 84 , 1) ;


commit ;

-- VersionCartes

insert into VersionCartes(NoCarte, NoVersion, Cote) values ( 2  , 2  , 36 ) ;
insert into VersionCartes(NoCarte, NoVersion, Cote) values ( 2  , 3  , 80 ) ;
insert into VersionCartes(NoCarte, NoVersion, Cote) values ( 2  , 4  , 80 ) ;

insert into VersionCartes(NoCarte, NoVersion, Cote) values ( 4  , 5  , 4 ) ;
insert into VersionCartes(NoCarte, NoVersion, Cote) values ( 4  , 6  , 14 ) ;
insert into VersionCartes(NoCarte, NoVersion, Cote) values ( 4  , 7  , 29 ) ;

insert into VersionCartes(NoCarte, NoVersion, Cote) values ( 6  , 8  , 18 ) ;
insert into VersionCartes(NoCarte, NoVersion, Cote) values ( 6  , 9  , 27 ) ;
insert into VersionCartes(NoCarte, NoVersion, Cote) values ( 6  , 10 , 36 ) ;
insert into VersionCartes(NoCarte, NoVersion, Cote) values ( 6  , 11 , 77 ) ;

insert into VersionCartes(NoCarte, NoVersion, Cote) values ( 8  , 12 , 12 ) ;
insert into VersionCartes(NoCarte, NoVersion, Cote) values ( 8  , 13 , 17 ) ;
insert into VersionCartes(NoCarte, NoVersion, Cote) values ( 8  , 14 , 34 ) ;
insert into VersionCartes(NoCarte, NoVersion, Cote) values ( 8  , 15 , 67 ) ;

insert into VersionCartes(NoCarte, NoVersion, Cote) values ( 10 , 16 , 18 ) ;
insert into VersionCartes(NoCarte, NoVersion, Cote) values ( 10 , 17 , 33 ) ;
insert into VersionCartes(NoCarte, NoVersion, Cote) values ( 10 , 18 , 47 ) ;

insert into VersionCartes(NoCarte, NoVersion, Cote) values ( 11 , 19 , 36 ) ;
insert into VersionCartes(NoCarte, NoVersion, Cote) values ( 11 , 20 , 36 ) ;

insert into VersionCartes(NoCarte, NoVersion, Cote) values ( 12 , 21 , 36 ) ;
insert into VersionCartes(NoCarte, NoVersion, Cote) values ( 12 , 22 , 36 ) ;
insert into VersionCartes(NoCarte, NoVersion, Cote) values ( 12 , 23 , 36 ) ;
insert into VersionCartes(NoCarte, NoVersion, Cote) values ( 12 , 24 , 36 ) ;

insert into VersionCartes(NoCarte, NoVersion, Cote) values ( 13 , 25 , 17 ) ;
insert into VersionCartes(NoCarte, NoVersion, Cote) values ( 13 , 26 , 33 ) ;
insert into VersionCartes(NoCarte, NoVersion, Cote) values ( 13 , 27 , 52 ) ;
insert into VersionCartes(NoCarte, NoVersion, Cote) values ( 13 , 28 , 89 ) ;

insert into VersionCartes(NoCarte, NoVersion, Cote) values ( 2 , 29 , 24 ) ;
insert into VersionCartes(NoCarte, NoVersion, Cote) values ( 2 , 30 , 41 ) ;

insert into VersionCartes(NoCarte, NoVersion, Cote) values ( 7 , 31 , 13 ) ;
insert into VersionCartes(NoCarte, NoVersion, Cote) values ( 7 , 32 , 17 ) ;

insert into VersionCartes(NoCarte, NoVersion, Cote) values ( 5 , 33 , 7 ) ;

insert into VersionCartes(NoCarte, NoVersion, Cote) values ( 1 , 34 , 120 ) ;

insert into VersionCartes(NoCarte, NoVersion, Cote) values ( 3 , 35 , 75 ) ;
insert into VersionCartes(NoCarte, NoVersion, Cote) values ( 3 , 36 , 97 ) ;

insert into VersionCartes(NoCarte, NoVersion, Cote) values ( 6 , 37 , 15 ) ;
insert into VersionCartes(NoCarte, NoVersion, Cote) values ( 6 , 38 , 24 ) ;

insert into VersionCartes(NoCarte, NoVersion, Cote) values ( 7 , 39 , 11 ) ;
insert into VersionCartes(NoCarte, NoVersion, Cote) values ( 7 , 40 , 17 ) ;
insert into VersionCartes(NoCarte, NoVersion, Cote) values ( 7 , 41 , 29 ) ;
insert into VersionCartes(NoCarte, NoVersion, Cote) values ( 7 , 42 , 28 ) ;

insert into VersionCartes(NoCarte, NoVersion, Cote) values ( 9 , 43 , 25 ) ;
insert into VersionCartes(NoCarte, NoVersion, Cote) values ( 9 , 44 , 62 ) ;

insert into VersionCartes(NoCarte, NoVersion, Cote) values ( 13 , 45 , 44 ) ;


commit ;

-- Decks

insert into Decks(Titre, Description) values ( 'Supprimé' , '' ) ;
insert into Decks(Titre, Description) values ( 'Coin-coin ultime aux yeux bleus' , 'La puissance du canard à l\'état pur' ) ;
insert into Decks(Titre, Description) values ( 'Le canard laqué' , 'Schwarzkopf la qualité, pour vous !' ) ;
insert into Decks(Titre, Description) values ( 'Super canard !' , 'Un super canard qui en vaut deux' ) ;
insert into Decks(Titre, Description) values ( 'Le trio de choc' , 'Attention, ils arrivent !' ) ;


commit ;

-- DeckComposition

insert into DeckComposition( NoDeck, NoCarte, NbExemplaires ) values ( 2 , 2  , 5 ) ;
insert into DeckComposition( NoDeck, NoCarte, NbExemplaires ) values ( 2 , 3  , 1 ) ;
insert into DeckComposition( NoDeck, NoCarte, NbExemplaires ) values ( 2 , 8  , 2 ) ;

insert into DeckComposition( NoDeck, NoCarte, NbExemplaires ) values ( 3 , 4  , 4 ) ;
insert into DeckComposition( NoDeck, NoCarte, NbExemplaires ) values ( 3 , 5  , 4 ) ;
insert into DeckComposition( NoDeck, NoCarte, NbExemplaires ) values ( 3 , 8  , 3 ) ;

insert into DeckComposition( NoDeck, NoCarte, NbExemplaires ) values ( 4 , 7  , 5 ) ;
insert into DeckComposition( NoDeck, NoCarte, NbExemplaires ) values ( 4 , 9  , 3 ) ;

insert into DeckComposition( NoDeck, NoCarte, NbExemplaires ) values ( 5 , 10 , 4 ) ;
insert into DeckComposition( NoDeck, NoCarte, NbExemplaires ) values ( 5 , 11 , 4 ) ;
insert into DeckComposition( NoDeck, NoCarte, NbExemplaires ) values ( 5 , 12 , 4 ) ;
insert into DeckComposition( NoDeck, NoCarte, NbExemplaires ) values ( 5 , 13 , 2 ) ;


commit ;

-- AvoirDeck

insert into AvoirDeck( NoJoueur, NoDeck ) values ( 2  , 1 ) ;
insert into AvoirDeck( NoJoueur, NoDeck ) values ( 2  , 3 ) ;

insert into AvoirDeck( NoJoueur, NoDeck ) values ( 3  , 2 ) ;

insert into AvoirDeck( NoJoueur, NoDeck ) values ( 4  , 2 ) ;
insert into AvoirDeck( NoJoueur, NoDeck ) values ( 4  , 3 ) ;
insert into AvoirDeck( NoJoueur, NoDeck ) values ( 4  , 4 ) ;
insert into AvoirDeck( NoJoueur, NoDeck ) values ( 4  , 5 ) ;

insert into AvoirDeck( NoJoueur, NoDeck ) values ( 5  , 3 ) ;

insert into AvoirDeck( NoJoueur, NoDeck ) values ( 6  , 3 ) ;

insert into AvoirDeck( NoJoueur, NoDeck ) values ( 7  , 5 ) ;

insert into AvoirDeck( NoJoueur, NoDeck ) values ( 8  , 2 ) ;
insert into AvoirDeck( NoJoueur, NoDeck ) values ( 8  , 3 ) ;
insert into AvoirDeck( NoJoueur, NoDeck ) values ( 8  , 5 ) ;

insert into AvoirDeck( NoJoueur, NoDeck ) values ( 9  , 4 ) ;

insert into AvoirDeck( NoJoueur, NoDeck ) values ( 10 , 2 ) ;

insert into AvoirDeck( NoJoueur, NoDeck ) values ( 11 , 3 ) ;

insert into AvoirDeck( NoJoueur, NoDeck ) values ( 12 , 2 ) ;
insert into AvoirDeck( NoJoueur, NoDeck ) values ( 12 , 4 ) ;

insert into AvoirDeck( NoJoueur, NoDeck ) values ( 13 , 5 ) ;

insert into AvoirDeck( NoJoueur, NoDeck ) values ( 15 , 2 ) ;

insert into AvoirDeck( NoJoueur, NoDeck ) values ( 16 , 4 ) ;


commit ;

-- PartieParticipation


insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 1 , 8 , 3 ) ;
insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 1 , 3 , 2 ) ;

insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 2 , 3 , 2 ) ;
insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 2 , 4 , 5 ) ;

insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 3 , 11 , 3 ) ;
insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 3 , 5 , 3 ) ;

insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 4 , 10 , 2 ) ;
insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 4 , 3 , 2 ) ;

insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 5 , 4 , 5 ) ;
insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 5 , 9 , 4 ) ;

insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 6 , 12 , 2 ) ;
insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 6 , 3 , 2 ) ;

insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 7 , 13 , 5 ) ;
insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 7 , 5 , 3 ) ;

insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 8 , 2 , 3 ) ;
insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 8 , 3 , 2 ) ;

insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 9 , 16 , 4 ) ;
insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 9 , 7 , 5 ) ;

insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 10 , 11 , 3 ) ;
insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 10 , 8 , 5 ) ;

insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 11 , 8 , 3 ) ;
insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 11 , 3 , 2 ) ;

insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 12 , 12 , 4 ) ;
insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 12 , 3 , 2 ) ;

insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 13 , 15 , 2 ) ;
insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 13 , 3 , 2 ) ;

insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 14, 5 , 3 ) ;
insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 14 , 3 , 2 ) ;

insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 15 , 9 , 4 ) ;
insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 15 , 3 , 2 ) ;

insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 16 , 2 , 1 ) ;
insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 16 , 3 , 2 ) ;

insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 17 , 2 , 3 ) ;
insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 17 , 15 , 2 ) ;

insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 18 , 13, 5 ) ;
insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 18 , 3 , 2 ) ;

insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 19 , 2 , 3 ) ;
insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 19 , 12 , 4 ) ;

insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 20 , 4 , 4 ) ;
insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 20 , 3 , 2 ) ;

insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 21 , 7 , 5 ) ;
insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 21 , 3 , 2 ) ;

insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 22 , 7 , 5 ) ;
insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 22 , 16 , 4 ) ;

insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 23 , 2 , 1 ) ;
insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 23 , 8 , 3 ) ;

insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 24 , 2 , 3 ) ;
insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 24 , 4 , 5 ) ;

insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 25 , 3 , 2 ) ;
insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 25 , 15 , 1 ) ;

insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 26 , 5 , 3 ) ;
insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 26 , 6 , 3 ) ;

insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 27 , 5 , 3 ) ;
insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 27 , 12 , 2 ) ;

insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 28 , 5 , 3 ) ;
insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 28 , 12 , 4 ) ;

insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 29 , 4 , 5 ) ;
insert into PartieParticipation( NoPartie, NoJoueur, NoDeck ) values ( 29 , 11 , 3 ) ;


commit ;
