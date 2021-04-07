# GO Player

The goal of the projet was to implemented a player able to play at real time GO (basic rules). 
This projet have been divided in two main parts :
	* Develop an heuristic to evaluate the board
	* Create a player able to play and choose the best move


## Heuristic

A database has been provided relating a board to a percentage of win. This database is generated from game played by [gnugo](https://en.wikipedia.org/wiki/GNU_Go) against itself in the game of Go for a size 9x9. 
The goal of this part was to build a neural network able to predict the percentage of win based on the board. 

Using the symmetries of the board, we can generate 8 inputs from one and they correspond to the same winning percentage. After training with the board as input and the win percentage as output, we can now predict a win percentage for any board. To increase our prediction, we again use symmetries to generate 8 boards based on the one we want to predict. Using our network on these 8 boards, we predict 8 values and take the median of these 8 values for our predicted percentage. A median value is better than a mean value because if the network makes a huge error on the prediction of one of the 8 boards, it has no impact on the final result.
