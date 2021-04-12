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

## Player

Each player has only 5 minutes for the entire game. This time limit makes it difficult to explore the possibility tree. This is why we did not implement an Alpha-beta pruning but only a Min-Max and we focused on improving the prediction of the neural network. The player is implemented in [myPlayer.py](GO/myPlayer.py) and uses the neural network model saved in [myplayer_model.h5](GO/myplayer_model.h5).

The exploration of possibilities depends on the time left to the player. 
- Less than 4 minutes : *Minimize the opponent's win rate*
- Between 4:00 and 4:55 : *Maximize our win rate*
- After 4:55 and up to 5:00 : *Play the first legal move*

## Improvement
To improve our player, here are some possibilities:
- **Generate more data to train the neural network** indeed we realized at the end that the data provided with our project was not valid with the defined Go rules
- **Improve the network by modifying the hyperparameters** to increase the prediction accuracy and/or to make it faster in order to go deeper into the decision tree
- **Try other types of neural networks** like the [CNN](https://en.wikipedia.org/wiki/Convolutional_neural_network)
- **Use more complex search algorithms** such as [Alpha-beta pruning](https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning) or [Monte Carlo](https://en.wikipedia.org/wiki/Monte_Carlo_tree_search)
- **Develop more complex strategies** based on the time left to the player
