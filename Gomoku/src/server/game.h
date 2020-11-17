/**
  * @file game.h
  */

#ifndef GAME_H
#define GAME_H

/* Libraries */
#include <stdio.h>

/* Files */
#include "move.h"
#include "board.h"

/**
 * @brief Representation a the Gomoku board where positions are described with a matrix n*n of capacity n*n and size : the number of pawns on the board
 */
struct board{
  /**
   * Matrix b of int
   */
  int* b;
  /**
   * Total capacity of the board
   */
  size_t capacity;
  /**
   * Current size of the total panws on the board
   */
  size_t size;
  };

#endif
