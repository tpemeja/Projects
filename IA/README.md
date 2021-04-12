# GO Player
Project realized in 2019 with Maxime ROSAY.

## Project description
The goal of the project is to implement a player able to play GO in real time (basic rules). 

This project is divided into two main parts:
* Develop an heuristic to evaluate the board
* Create a player able to play and choose the best move


## Heuristic

A database has been provided relating a table to a win rate. This database is generated from games played by [Gnugo](https://en.wikipedia.org/wiki/GNU_Go) against himself in Go for a size **9x9**. The heuristic is based on a neural network capable of predicting the win rate of a board. 

Using symmetries, a board can be associated to 8 boards with the same win rate. This technique is used to produce more data for training the neural network but also to improve prediction. Indeed, to evaluate the win rate of a board, we use the symmetric boards to produce 8 values. The prediction of the original board is the median of these 8 values. The median, instead of the average, ignores large prediction errors and therefore improves the accuracy of the network.
