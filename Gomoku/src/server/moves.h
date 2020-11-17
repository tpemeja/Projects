/**
 * @file moves.h
 * @date { 20 mars 2019 Moves allocate in the heap }
 * @version 1.1
 *
 * Implementation of the moves. In fact, this structure implements the array of col_mov_t of last n moves and the current size of it
 */

#ifndef MOVES_H
#define MOVES_H

/* Files */
#include "move.h"
#include "board.h"

/**
 * ----------------------------------------------------
 * moves
 * ----------------------------------------------------
 */

/**
 * @brief Structure which implements an array of col_move_t of the last n moves
 */
struct moves {
  /**
   * Array of last n moves
   */
  struct col_move_t* t;
  /**
   * Current size of the array
   */
  size_t size;
};

/**
 * @brief Initialize an struct moves (allocate in the heap) and gives an empty array of size 0
 * @return initialized struct moves with an empty array of size 0
 */
struct moves* moves__initialize();

/**
 * @brief Add an opening (3 moves) and add it in the parameter moves
 * @return Struct moves given in parameter filled with 3 moves
 */
int moves__add_opening(struct col_move_t* m, struct moves* moves,struct board* board);

/**
 * @brief Add a specific col_mov_t in the moves
 * @return the given col_mov_t added struct moves with the array with the good size
 */
void moves__enqueue(struct moves* m, struct col_move_t* cmv);

/**
 * @brief Change the size and the table of col_move_t with the given parameters
 */
void moves__update(struct moves* moves, size_t size, struct col_move_t* cmv);

/**
 * @brief Return the last n moves : the array of the struct moves
 * @return Array of col_mov_t of the struct moves
 */
struct col_move_t* moves__last_n(const struct moves* m);

/**
 * @brief Give the size of the current array of col_mov_t of the struct moves
 * @return A size_t which is the current size of the array of last n moves
 */
size_t moves__get_size(const struct moves* m);

/**
 * @brief Free all moves in the struct and the structure itself
 * @return moves freed
 */
void moves__free(struct moves* moves);

#endif
