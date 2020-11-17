/**
 * @file players.h
 * @version { 1.3 Players are no longer an array of pointers }
 * @date 26 mars 2019
 *
 * This file describe how the struct players and player_t work. In fact, these structures implements the strategies (struct player) and store them in an array in order that the server has access to them.
 */

#ifndef PLAYERS_H
#define PLAYERS_H

#define NB_PLAYERS 1

/**
 * ----------------------------------------------------
 * player_t
 * ----------------------------------------------------
 */

/**
 * @brief Representation of a player for the server. It has all the same functions as player as function pointers. It will implement the abstraction of the struct player
 */
struct player_t {
  /**
   * Get the name of the player
   */
  char const* (*get_player_name)(void);
  /**
   * Propose a 3 move opening and return it
   */
  struct col_move_t* (*propose_opening)(size_t);
  /**
   * Validate or not the given opening
   */
  int (*accept_opening)(size_t,const struct col_move_t*);
  /**
   * Initialize the player with its color and the size of the board
   */
  void (*initialize)(size_t,enum color_t);
  /**
   * Make a move and return it
   */
  struct move_t (*play)(const struct col_move_t*,size_t);
  /**
   * Free its internal elements
   */
  void (*finalize)(void);
  /**
   * Pointer to the library of the player in order to free it (we must have access to it)
   */
  void* handle;
};

/**
 * @brief Initialize all players : link dynamic libraries to functions
 * @param[in] argv list of arguments (files)
 * @param[in] argc number of files
 * @param[in/out] players list of players
 * @return array players initialized with all player_t inside with all functions linked and their libraries linked (handle)
 */
void players__initialize(char** argv, int argc, struct player_t players[NB_PLAYERS]);

/**
 * @brief Free all players and all loaded libraries
 * @param[in/out] players players who will be freed with their function finalize
 * @return all libraries of player_t in players are freed (closed)
 */
void players__free(struct player_t players[NB_PLAYERS]);

/**
 * ----------------------------------------------------
 * current_player
 * ----------------------------------------------------
 */

/**
 * @brief Structure with informations for the current player
 */
struct current_player {
  /**
   * Position of the player (its number)
   */
  size_t number;
  /**
   * Color of the player
   */
  enum color_t color;
};

/**
 * @brief Initialize the current player : black, first position
 * @return current player initialized in black and with the first position
 */
struct current_player current_player__initialize();

/**
 * @brief Retrieve the color of the current player
 * @param[in] current_player current player who plays
 * @return Current color of the player
 */
enum color_t current_player__get_color(const struct current_player);

/**
 * @brief Change the current player
 * @param[in/out] cp current player who will let his turn to the next one (we give the adress because its in/out)
 * @return cp is now the next player
 */
void current_player__next(struct current_player *cp);

#endif
