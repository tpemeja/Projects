const mysql = require('mysql');
const requestBuilder = require('../src/sql_requests');

const connection = mysql.createConnection({
	host: 'localhost',
	user: 'root',
	password: '',
	database: 'canard'
});
connection.connect();

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

testQueries("", requestBuilder.get || {});

var success = 0;
var failed = 0;
var ongoing = 0;

function testQueries(path, object) {
	const keys = Object.keys(object);
	if (keys.length == 0) {
		const paramName = path.slice(path.lastIndexOf("/") + 1);
		const params = object.length;
		var query;
		if (params > 0) {
			path = path + "/:" + paramName;
			query = object(0);
		} else {
			query = object();
		}
		ongoing++;
		executeSQLQuery(query, function (err, result) {
			if (err) {
				failed++;
				console.error("[FAILED] " + path);
				console.error(err);
			} else {
				success++;
				console.log("[SUCCESS] " + path);
			}
			ongoing--;
		});
	} else {
		for (var i = 0; i < keys.length; i++) {
			testQueries(path + "/" + keys[i], object[keys[i]]);
		}
	}
}

function executeSQLQuery(query, callback) {
	connection.query(query, callback);
}

const interval = setInterval(printResult, 100);

function printResult() {
	if ((failed + success) <= 0 || ongoing > 0) {
		return;
	}

	if (failed > 0) {
		console.error("[FAILED] TEST " + success + " / " + (failed + success));
	} else {
		console.log("[SUCCESS] TEST " + success + " / " + success);
	}
	clearInterval(interval);
	process.exit(0);
}