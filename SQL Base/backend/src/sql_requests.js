function minus(table_a, table_b, join_condition, table_b_column_name) {;
	return "SELECT * FROM ((" +
		table_a + ") as T1 LEFT JOIN \n(" + table_b + ") as T2 ON (" + join_condition + ")) WHERE T2." + table_b_column_name + " IS NULL;";
}

const cards = {
	all: function () {
		return `SELECT * FROM Cartes WHERE Cartes.Titre != "Supprimé";`;
	},
	for: {
		no: function (no) {
			return `SELECT * FROM Cartes WHERE NoCarte = ${no};`;
		},
		name: function (name) {
			return `SELECT * FROM Cartes WHERE Titre=\'${name}\'`;
		},
		type: function (type) {
			return `SELECT * FROM Cartes WHERE Type=\'${type}\';`;
		},
		family: function (family) {
			return `SELECT * FROM Cartes WHERE Famille=\'${family}\';`;
		},
		deck: function (noDeck) {
			return `SELECT Cartes.*,NbExemplaires FROM (Cartes NATURAL JOIN DeckComposition) WHERE NoDeck = ${noDeck};`;
		},
		notInDeck: function (noDeck) {
			return `SELECT T1.* FROM Cartes as T1 LEFT JOIN (SELECT Cartes.* FROM Cartes NATURAL JOIN DeckComposition WHERE NoDeck = ${noDeck}) as T2 ON T1.NoCarte = T2.NoCarte WHERE T2.NoCarte IS NULL AND T1.Titre != "Supprimé";`
			/*return minus("SELECT * FROM Cartes", `SELECT Cartes.*,NbExemplaires FROM (Cartes NATURAL JOIN DeckComposition) WHERE NoDeck = ${noDeck}`, "T1.NoCarte = T2.NoCarte", "NoCarte");*/
		},
		notPossededBy: function (noPlayer) {
			return `SELECT T1.* FROM Cartes as T1 LEFT JOIN (SELECT Cartes.* FROM Cartes NATURAL JOIN (Possessions NATURAL JOIN Obtentions) WHERE NoJoueur = ${noPlayer}) as T2 ON T1.NoCarte = T2.NoCarte WHERE T2.NoCarte is NULL AND T1.Titre != "Supprimé";`
			/*return minus("SELECT * FROM Cartes", `SELECT Cartes.* FROM (Cartes NATURAL JOIN Obtentions) WHERE NoJoueur = ${noPlayer}`, "T1.NoCarte = T2.NoCarte", "NoCarte");*/
		},
		version: function (noCard) {
			return `SELECT Versions.* FROM VersionCartes NATURAL JOIN Versions WHERE NoCarte = ${noCard};`
		}
	},
	by: {
		uses: function () {
			return "SELECT Cartes.*, COUNT(*) as NbUses FROM ((Cartes NATURAL JOIN DeckComposition) NATURAL JOIN AvoirDeck) GROUP BY NoCarte ORDER BY NbUses DESC;";
		},
		owners: function () {
			return "SELECT Cartes.*, COUNT(*) as NbOwners FROM (Cartes NATURAL JOIN (Possessions NATURAL JOIN Obtentions)) GROUP BY NoCarte ORDER BY NbOwners DESC;";
		}
	},
	unused: function () {
		return minus("SELECT * FROM Cartes", "SELECT Cartes.* FROM (Cartes NATURAL JOIN DeckComposition) WHERE NbExemplaires >= 0", "T1.NoCarte = T2.NoCarte", "NoCarte");
	},
	compute: {
		owners: function (no) {
			return "SELECT COUNT(*) as NbOwners FROM (Possessions NATURAL JOIN Obtentions) WHERE NoCarte = " + no + ";";
		},
		uses: function (no) {
			return "SELECT C.*, COUNT(*) as NbUses FROM (((SELECT * FROM Cartes WHERE NoCarte = " + no + ") as C NATURAL JOIN DeckComposition) NATURAL JOIN AvoirDeck) GROUP BY NoCarte";
		}

	}
};
const players = {
	all: function () {
		return `SELECT * FROM Joueurs WHERE Pseudonyme != "Supprimé";`;
	},
	for: {
		no: function (no) {
			return `SELECT * FROM Joueurs WHERE NoJoueur = ${no};`;
		},
		name: function (name) {
			return `SELECT * FROM Joueurs WHERE Nom=\'${name}\'`;
		},
		pseudo: function (pseudo) {
			return `SELECT * FROM Joueurs WHERE Pseudonyme LIKE \'${pseudo}%\';`;
		}
	},
	by: {
		games: {
			played: function () {
				return "SELECT Joueurs.*, COUNT(*) as NbParties FROM (Joueurs NATURAL JOIN PartieParticipation) GROUP BY NoJoueur ORDER BY NbParties DESC;";
			},
			won: function () {
				return `SELECT Joueurs.*, COUNT(*) as NbVictoires FROM (Parties LEFT JOIN PartieParticipation ON (PartieParticipation.NoJoueur = Parties.NoJoueurGagnant AND PartieParticipation.NoPartie = Parties.NoPartie) LEFT JOIN Joueurs ON PartieParticipation.NoJoueur = Joueurs.NoJoueur) GROUP BY Joueurs.NoJoueur ORDER BY NbVictoires DESC;`;
			},
			neverWon: function () {
				return `SELECT Joueurs.*,COUNT(*) - 1 as NbVictoires FROM Joueurs WHERE NoJoueur NOT IN (SELECT NoJoueurGagnant
				FROM Parties)  AND Joueurs.Pseudonyme != "Supprimé" GROUP BY NoJoueur;`;
			}
		},
		collection: {
			value: function () {
				return "SELECT Joueurs.*, SUM(T2.Valeur) as ValeurJoueur FROM (Joueurs NATURAL JOIN (SELECT *, Etat * Cote * NbExemplaires / 100 as Valeur FROM (VersionCartes NATURAL JOIN (Possessions NATURAL JOIN Obtentions))) as T2) GROUP BY NoJoueur ORDER BY ValeurJoueur DESC;";
			},
			rarity: function () {
				return "SELECT Joueurs.*, COUNT(*) as NbCartesRares FROM (Joueurs NATURAL JOIN ((Possessions NATURAL JOIN Obtentions) NATURAL JOIN Versions)) WHERE Tirage < 100 OR DateImpression < \'2000-01-01\' GROUP BY NoJoueur ORDER BY NbCartesRares DESC;";
			}
		},
		cardsQuantity: function () {
			return "SELECT Joueurs.*, SUM(NbExemplaires) as NbCartes FROM (Joueurs NATURAL JOIN (Possessions NATURAL JOIN Obtentions)) GROUP BY NoJoueur ORDER BY NbCartes DESC;";
		}
	},
	collecters: function () {
		return minus("SELECT * FROM Joueurs", "SELECT Joueurs.*, COUNT(*) as NbParties FROM (Joueurs NATURAL JOIN PartieParticipation) GROUP BY NoJoueur", "T1.NoJoueur = T2.NoJoueur", "NoJoueur");
	},
	compute: {
		games: {
			played: function (no) {
				return "SELECT J.*, COUNT(*) as NbParties FROM ((SELECT * FROM Joueurs WHERE NoJoueur = " + no + ") as J NATURAL JOIN PartieParticipation);";
			},
			won: function (no) {
				return "SELECT J.*, COUNT(*) as NbVictoires FROM ((SELECT * FROM Joueurs WHERE NoJoueur = " + no + ") as J NATURAL JOIN (Parties LEFT JOIN PartieParticipation ON (PartieParticipation.NoJoueur = Parties.NoJoueurGagnant AND PartieParticipation.NoPartie = Parties.NoPartie)));";
			}
		},
		collection: {
			value: function (no) {
				return "SELECT J.*, SUM(T2.Valeur) as ValeurJoueur FROM ((SELECT * FROM Joueurs WHERE NoJoueur = " + no + ") as J NATURAL JOIN (SELECT *, Etat * Cote * NbExemplaires / 100 as Valeur FROM (VersionCartes NATURAL JOIN (Possessions NATURAL JOIN Obtentions))) as T2) GROUP BY NoJoueur ORDER BY ValeurJoueur DESC;";
			},
			rarity: function (no) {
				return "SELECT J.*, COUNT(*) as NbCartesRares FROM ((SELECT * FROM Joueurs WHERE NoJoueur = " + no + ") as J NATURAL JOIN ((Possessions NATURAL JOIN Obtentions) NATURAL JOIN Versions)) WHERE Tirage < 100 OR DateImpression < \'2000-01-01\' GROUP BY NoJoueur ORDER BY NbCartesRares DESC;";
			}
		},
		cards: {
			quantity: function (no) {
				return "SELECT T.*, SUM(NbExemplaires) as NbCartes FROM ((SELECT * FROM Joueurs WHERE NoJoueur = " + no + ") as T NATURAL JOIN (Possessions NATURAL JOIN Obtentions));";
			}
		}
	}
};

const decks = {
	all: function () {
		return `SELECT * FROM Decks WHERE Titre != "Supprimé"	;`;
	},
	allId: function () {
		return `SELECT NoDeck FROM Decks;`;
	},
	for: {
		no: function (no) {
			return `SELECT * FROM Decks WHERE NoDeck = ${no};`;
		},
		name: function (name) {
			return `SELECT * FROM Decks WHERE Titre=\'${name}\'`;
		},
		player: function (noPlayer) {
			return `SELECT Decks.* FROM (Decks NATURAL JOIN AvoirDeck) WHERE NoJoueur = ${noPlayer};`;
		}
	},
	cardsQuantity: function () {
		return "SELECT Decks.*, COUNT(*) as NbCartes FROM (Decks NATURAL JOIN DeckComposition) GROUP BY NoDeck ORDER BY NoDeck;"
	},
	by: {
		uses: function () {
			return "SELECT Decks.*, COUNT(*) as NbUses FROM (Decks NATURAL JOIN AvoirDeck) GROUP BY NoDeck ORDER BY NbUses DESC;";
		}
	},
	compute: {
		uses: function (no) {
			return "SELECT D.*, COUNT(*) as NbUses FROM ((SELECT * FROM Decks WHERE NoDeck = " + no + ") as D NATURAL JOIN AvoirDeck) GROUP BY NoDeck;";
		}
	}
};

module.exports = {
	get: {
		cards: cards,
		players: players,
		decks: decks
	},
	post: {
		cards: function (all) {
			return "INSERT INTO Cartes(Titre, Description, Type, Famille, Attaque, Defense) values ('" + all.title + "','" + all.description + "','" + all.type + "','" + all.family + "','" + all.attack + "','" + all.defense + "');"
		},
		players: function (all) {
			return "INSERT INTO Joueurs(Nom, Prenom, Pseudonyme) values ('" + all.surname + "','" + all.name + "','" + all.nickname + "');"
		},
		decks: function (all) {
			return "INSERT INTO Decks(Titre, Description) values ('" + all.Titre + "','" + all.Description + "');"
		},
		cardInDeck: function (all) {
			return "INSERT INTO DeckComposition(NoDeck, NoCarte, NbExemplaires) values ('" + all.NoDeck + "','" + all.NoCarte + "','" + all.NbExemplaires + "');"
		},
		cardForPlayer: function (all) {
			return "INSERT INTO Obtentions(Date_Acquisition,Moyen_Acquisition,Prix_achat,NoJoueur,NoCarte,NoVersion,Etat,NbExemplaires) values ('" + all.Date_Acquisition + "','" + all.Moyen_Acquisition + "','" + all.Prix + "','" + all.NoJoueur + "','" + all.NoCarte + "','" + all.NoVersion + "','" + all.Etat + "','" + all.NbExemplaires + "');"
		}
	}
};
