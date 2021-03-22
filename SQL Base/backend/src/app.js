const express = require('express');
const app = express();
const http = require('http').createServer(app);
const mysql = require('mysql');
const bodyParser = require('body-parser');
const cors = require('cors');
const PORT = process.env.PORT || 3000;
const requestBuilder = require('./sql_requests');

const connection = mysql.createConnection({
	host: 'localhost',
	user: 'root',
	password: 'password',
	database: 'canard'
});
connection.connect();
//Sécurité
app.use(cors());

// Polyfill --------------------------------------------------------------------
if (!String.prototype.splice) {
	/**
	 * {JSDoc}
	 *
	 * The splice() method changes the content of a string by removing a range of
	 * characters and/or adding new characters.
	 *
	 * @this {String}
	 * @param {number} start Index at which to start changing the string.
	 * @param {number} delCount An integer indicating the number of old chars to remove.
	 * @param {string} newSubStr The String that is spliced in.
	 * @return {string} A new string with the spliced substring.
	 */
	String.prototype.splice = function (start, delCount, newSubStr) {
		return this.slice(0, start) + newSubStr + this.slice(start + Math.abs(delCount));
	};
}



// Configuration parser body
app.use(bodyParser.json());
createGetRoutes("", requestBuilder.get || {});

// Creating route to add cards
app.post("/cards", function (req, res) {
	executeSQLQuery(requestBuilder.post.cards(req.body), function (err, result) {
		if (err)
			throw err;
		res.status(200).json(result);
	});
});

// Creating route to add players
app.post("/players", function (req, res) {
	executeSQLQuery(requestBuilder.post.players(req.body), function (err, result) {
		if (err)
			throw err;
		res.status(200).json(result);
	});
});

// Creating route to add decks
app.post("/decks", function (req, res) {
	executeSQLQuery(requestBuilder.post.decks(req.body), function (err, result) {
		if (err)
			throw err;
		res.status(200).json(result);
	});
});

// Creating route to a card in a specified deck
app.post("/cardInDeck", function (req, res) {
	executeSQLQuery(requestBuilder.post.cardInDeck(req.body), function (err, result) {
		if (err)
			throw err;
		res.status(200).json(result);
	});
});

// Creating route to add a card for a specified player
app.post("/cardForPlayer", function (req, res) {
	executeSQLQuery(requestBuilder.post.cardForPlayer(req.body), function (err, result) {
		if (err)
			throw err;
		res.status(200).json(result);
	});
});



http.listen(PORT, function () {
	console.log('[INFO][HTTP] Listening on *:' + PORT);
});

function createGetRoutes(path, object) {
	const keys = Object.keys(object);
	if (keys.length == 0) {
		const paramName = path.slice(path.lastIndexOf("/") + 1);
		const params = object.length;
		if (params > 0) {
			path = path + "/:" + paramName;
		}
		console.log("Created GET route " + path);
		app.get(path, function (req, res) {
			var query = "";
			if (params > 0) {
				query = object(req.params[paramName]);
			} else {
				query = object();
			}
			executeSQLQuery(query, function (err, result) {
				if (err)
					throw err;
				res.status(200).json(result);
			})
		});
	} else {
		for (var i = 0; i < keys.length; i++) {
			createGetRoutes(path + "/" + keys[i], object[keys[i]]);
		}
	}

}

function executeSQLQuery(query, callback) {
	console.log("Executing:----------------------------------------------------");
	console.log(query);
	connection.query(query, callback);
}

app.get("/", function (req, res) {
	res.send("Server is running");
});
