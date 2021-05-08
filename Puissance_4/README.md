# Connect Four project
Personal project realized in 2021 to practice object-oriented programming, data generation and game visualization with [IPython](https://ipython.org/).

## Project description
The goal of the project is to reproduce the project of Goban but for the Connect Four game. This project is divided into four main parts :
- [x] Implement the Connect Four game with game visualization
- [x] Reduce the size of the board by using the bitboard 
- [x] Generate data to feed the neural network
- [ ] Define a neural network model for the heuristic
- [ ] Create a player for the game using the heuristic

The training of the network required too much information and was too time consuming with the data generated. The project has changed and now aims to determine an efficient neural network using a **genetic algorithm**.  
- [x] Implement the genetic algorithm
- [ ] Optimize the parameters using [Optuna](https://optuna.org/) 

[Connect Four](https://en.wikipedia.org/wiki/Connect_Four) is a **solved game**. It might be interesting to know if the player, based on a neural network trained with all possible games, will follow the strategy and force the victory.
