/**
 * @file moves.c
 * @version 1.1
 * @date 26 mars 2019
 *
 * Implementation of moves.h
 */

/* Libraries */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* Files */
#include "move.h"
#include "moves.h"
#include "board.h"
/**
 * ----------------------------------------------------
 * moves
 * ----------------------------------------------------
 */

/**
 * @brief Structure which implements an array of col_move_t of the last n moves
 */
//struct moves {
  /**
   * Array of last n moves
   */
// struct col_move_t* t;
  /**
   * Current size of the array
   */
  //size_t size;
//};

struct moves* moves__initialize(){
  struct moves* m = malloc(sizeof(struct moves));

  /* Initialize the size of moves */
  m->size = 0;

  /* Initialize moves */
  m->t = malloc(sizeof(struct col_move_t)*4);
  return m;
}

void moves__update(struct moves* moves, size_t size, struct col_move_t* cmv){
  moves->size = size;
  free(moves->t);
  moves->t = cmv;
}

int moves__add_board(struct board* board,struct col_move_t *m){
  if(board__is_valid_move(board,m[0].m)){
    board__add_move(board,m[0].m,m[0].c);
  }
  else{
    return 1;
  }
  if(board__is_valid_move(board,m[1].m)){
    board__add_move(board,m[1].m,m[1].c);
  }
  else{
    return 1;
  }
  if(board__is_valid_move(board,m[2].m)){
    board__add_move(board,m[2].m,m[2].c);
  }
  else{
    return 1;
  }
  return 0;
}

int moves__add_opening(struct col_move_t* m, struct moves* moves, struct board* board ){
  assert(m);
  assert(moves);
  if(moves__add_board(board,m)){
      return 1;
  }
  for(int i = 0; i < 3; i++)
    moves->t[i] = m[i];

  free(m);
  moves->size = 3;
  return 0;
}

void moves__enqueue(struct moves* moves,struct col_move_t* m){
  assert(m);
  assert(moves);

  switch(moves->size){
  case 4 :
    *(moves->t) = *(moves->t + 3);
    *(moves->t +1) = *m;
    moves->size = 2;
    break;
  /* When only the opening play has been played */
  case 3 :
    *(moves->t+3) = *m;
    moves->size = 4;
    break;
  /* When the first player only has played with no opening propose */
  case 0 :
    *(moves->t) = *m;
    moves->size = 1;
    break;
  case 1 :
    *(moves->t+1) = *m;
    moves->size = 2;
    break;
  default :
    *(moves->t) = *(moves->t+1);
    *(moves->t+1) = *m;
    moves->size = 2;
    break;
  }
}

struct col_move_t* moves__last_n(const struct moves* m){
  assert(m);
  return(m->t);
}

size_t moves__get_size(const struct moves* m){
  assert(m);
  return(m->size);
}

void moves__free(struct moves* m){
  free(m->t);
  free(m);
}
