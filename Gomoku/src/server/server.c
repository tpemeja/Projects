/**
 * @file server.c
 * @version 1.3
 * @date { 26 mars 2019 Shorter version and cleaned version of main }
 *
 * This file is the main application of the code. In this file, the game will be played and this server will handle the game.
 * It creates the board, players, and handle the progress of the game.
 */

/* Libraries */
#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <assert.h>
#include <getopt.h>
#include <string.h>

/* Files */
#include "move.h"
#include "game.h"
#include "utils.h"
#include "moves.h"
#include "players.h"
#include "bitboard.h"

/* Variables in order to determine the conditions of the game */
int opening = 0;
size_t size_of_board = 7;

/**
 * @brief Free all structures allocated dynamically in the server
 * @param[in/out] board Board with the pieces
 * @param[in/out] players all players with linked functions and libraries inside
 * @param[in/out] moves structure with the array of moves
 */
void free_all(struct board* board, struct player_t players[NB_PLAYERS], struct moves* moves){
  players__free(players);
  board__free(board);
  moves__free(moves);
}

/*Debugging function */
void print_moves(struct moves* moves){
  size_t l = moves__get_size(moves);
  for(int i = 0; i < l; i++){
    printf("le coup numéro %d stocké est le coup joué en : %ld %ld \n",i,moves__last_n(moves)[i].m.row,moves__last_n(moves)[i].m.col);
  }
}


/**
 * @brief Check the swap, if so, propose opening and add moves in the moves, then swap players order if the opening is accepted
 * @param[in] players[NB_PLAYERS] players who will play
 * @param[in] swap flag which indicate if the first player want to propose opening
 * @param[in/out] moves structure filled with the array of moves and the size
 * @return first player player to play with array moves filled or not (depending if the opening was accepted)
 */
struct current_player play_opening(struct player_t players[NB_PLAYERS], int opening, struct moves* moves,struct board * board){
  assert(moves);

  /* First player who will be returned */
  struct current_player p;

  if(opening){
    struct col_move_t *m = players[0].propose_opening(size_of_board);
    int i = moves__add_opening(m,moves,board);
    if(i){
	printf("invalid opening\n");
	exit(1);
    }
    /* When the player accept there's no swap */
    if(players[1].accept_opening(size_of_board,moves__last_n(moves))){
      players[0].initialize(size_of_board,BLACK);
      players[1].initialize(size_of_board,WHITE);
      p.number = 1;
    }
    /* Else the other player accept the opening */
    else {
      players[0].initialize(size_of_board,WHITE);
      players[1].initialize(size_of_board,BLACK);
      p.number = 0;
    }
    p.color = WHITE;
  }
  /* If there is no opening indicated */
  else {
    players[0].initialize(size_of_board,BLACK);
    players[1].initialize(size_of_board,WHITE);
    p.number = 0;
    p.color = BLACK;
  }

  return p;
}

/* -------------------------------- */
int main(int argc, char** argv){

  /* Parse the options */
  if(parse_opts(argc,argv) < NB_PLAYERS){
    printf("Wrong usage of the function %s",argv[0]);
    return 1;
  }

  /* Initialize all structures for the game */
  struct current_player cp = current_player__initialize();
  struct player_t players[NB_PLAYERS];
  players__initialize(argv,argc,players);
  struct board* board = board__initialize(size_of_board);
  struct moves* moves = moves__initialize();

  /* Handle swap situation */
  cp = play_opening(players,opening,moves,board);
  /* Current move done */
  struct move_t m;
  /* Col_move_t that will be added to the moves structure */
  struct col_move_t current_cmv;

  int win = 0;
  int count = 1;

  /* ------------------ Game loop -------------------- */
  while(1){
    printf("Play turn number %d : %s, ",count,players[cp.number].get_player_name());
    count += 1;

    /* Current player plays considering last n moves */
    m = players[cp.number].play(moves__last_n(moves),moves__get_size(moves));
    printf("he played : %ld %ld\n", m.row, m.col);
    current_cmv.m = m;
    current_cmv.c = current_player__get_color(cp);

    /* Verify if the move is_valid or not if it is it updates the board */
    if(!(board__is_valid_move(board,m))){

      printf("Le coup du joueur %s est un coup invalide (%ld %ld)\n",players[cp.number].get_player_name(), m.row, m.col);
      free_all(board,players,moves);
      return 1;
    }

    /* Add the move on the board */
    board__add_move(board,m,cp.color);

    /* Verify if a player is winning */
    win = board__won(board,m);
    if(win || board__is_full(board)){
      if(win)
	printf("le joueur %s a gagné en %d coups\n",players[cp.number].get_player_name(), count);
      else
	printf("Egalité entre %s et %s : le plateau de jeu est rempli\n", players[0].get_player_name(), players[1].get_player_name());
      free_all(board,players,moves);
      return 0;
    }

    /* Add the current move to the array of moves */
    moves__enqueue(moves,&current_cmv);
    
    current_player__next(&cp);
  }

  free_all(board,players,moves);
  return 0;
}
