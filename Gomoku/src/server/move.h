/**
 * @file move.h
 * 
 * Implements the notion of position on a board
 */

#ifndef _BITBOARD_MOVE_H_
#define _BITBOARD_MOVE_H_

/* Libraries */
#include <stddef.h>

/* Players */
enum color_t { BLACK=0, WHITE=1, RED=2, BLUE=3 };

/**
 * @brief Describe a position on a board
 */
struct move_t {
  /**
   * A row and column coordinate
   */
  size_t row,col; };

/**
 * @brief Describe a position but with a color associated
 */
struct col_move_t {
  /**
   * A position on the board
   */
  struct move_t m;
  /**
   * Color
   */
  enum color_t c;
};

#endif // _BITBOARD_MOVE_H_
