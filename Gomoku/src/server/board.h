/**
 * @file board.h
 */

#ifndef BOARD_H
#define BOARD_H

/* Libraries */
#include <stdio.h>

/* Files */
#include "move.h"

struct board;

/**
 * @brief Initialize the board
 * @param[in] size size given in argument during running : n
 * @return initialized board (allocated in the heap) with unsigned 128-bit int for all players of capacity n*n
 */
struct board* board__initialize(size_t size);


/**
 * @brief Return a copy of a board : useful for players in order to compare evaluated boards
 * @param[in] board source board that will be copied
 * @return a copy of the argument allocated in the heap
 */
struct board* board__copy(struct board * board);

/**
 * @brief Return all possible moves on the board: useful for players
 * @param[in] board source board with pawns inside
 * @return a list of move_t with possible moves
 */
struct list * board__possible_moves(struct board * board);

/**
 * @brief Return only one possible move in a board (among all possible moves): useful for players (Montecarlo)
 * @param[in] board source board with pawns inside
 * @return a move_t with a possible move
 */
struct move_t board__possible_move(struct board * board);

/**
 * @brief Check if the board is full. To do so, bitwise operations are used : if the bitboard is full, means (board black OR white board) == -1
 * @param[in] board board where are checked white pawns and black pawns
 * @return 1 if the board is full, 0 otherwise
 */
int board__is_full(struct board* board);

/**
 * @brief Get the color of the pawn at the position i,j
 * @param[in] board board where the color of the pawn is found
 * @param[in] i position of the row
 * @param[in] j position of the column
 * @return BLACK,WHITE,<other color> if there is a pawn at the position i,j; -1 otherwise
 */
int board__get_color(struct board* b, int i, int j);

/**
 * @brief Verify if the give move (at position i,j) is a valid move
 * @param[in] board board full of moves
 * @param[in] move given move at position i,j that needs to be validated
 * @param[in] p current player number
 * @return 1 if the move is valid, 0 otherwise
 */
 int board__is_valid_move(struct board* board, struct move_t move);

 /**
  * @brief Add a pawn on the board. The precondition here is the move is valid and can be added to the board
  * @param[in/out] board board where the pawn has to be added
  * @param[in] move move to be added
  * @param[in] i color of the current player
  * @return board has the pawn on it
  */
 void board__add_move(struct board *b, struct move_t move, enum color_t i);

 /**
  * @brief Remove a move on the board : useful for players that fill board a lot in order to find the best board possible
  * @param[in/out] board board where the move will be removed
  * @param[in] move positions for the move
  * @return 0 if the move was correctly removed from the board, 1 of there is no pawn for the move
  */
 int board__remove_move(struct board *b, struct move_t move);

 /**
  * @brief Check if someone won (either BLACK or WHITE). Verifies if the move given in argument is in a winning situation: columns, rows, left diagonals or right diagonals
  * @param[in] board board where are verified positions
  * @param[in] move move just added to the board that needs to be verified
  * @return 1 if the result of the move on the board is a winning situation, 0 otherwise
  */
 int board__won(struct board* board, struct move_t move);

/**
 * @brief Free the board given in argument
 * @param[in/out] board board that needs to be freed
 * @return freed board
 */
void board__free(struct board* board);


// return the "value" of a move for the heuristic
// it is the length of the line that would be made if we made the move (i,j)
// or zero if the line would be too short to make five
void board__explore_line(struct board* b, int i,int j,int shift_mask,int player,int* pattern);

//return 1 if there is a line of five for any color
//int detect_line_of_five(struct board *b);


#endif
