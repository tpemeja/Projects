/**
 * @file bitboard.h
 */

#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include "move.h"
#include "board.h"

/**
 * @brief Representation a the Gomoku board where each position of the n*n board represents a game position or state
 */
struct board{
  /**
   * Unsigned 128-bit int for BLACK pawns (without separating bits)
   */
  __uint128_t* b_w;
  /**
   * Unsigned 128-bit int for WHITE pawns (without separating bits)
   */
  __uint128_t* b_b;
  /**
   * Total capacity of the board : defines the number of bits useless
   */
  size_t capacity;
  };

#endif
