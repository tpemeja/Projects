/**
 * @file game.c
 */

/* Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

/* Files */
#include "game.h"
#include "move.h"

#define MIN(a,b) ((a) < (b))?(a):(b)
#define MAX(a,b) ((a) > (b))?(a):(b)

struct board* board__initialize(size_t size){
  struct board* board = malloc(sizeof(struct board));
  board->capacity = (size*size);
  board->size = 0;
  board->b = malloc(sizeof(int) * size * size);
  for(size_t i = 0; i < board->capacity; i++){
    board->b[i] = -1;
  }
  return board;
}

void board__free(struct board* board){
  free(board->b);
  free(board);
}

int board__is_full(struct board* board){
  return (board->size>=board->capacity);
}

//Give the i-position of the board
int position(size_t size,int i,int j){
  return(i*size+j);
}

/* Test if the position is valid */
int is_valid_move(struct board* board, struct move_t move, int p){
  size_t size = sqrt(board->capacity);
  if(move.row<0 || move.col<0 || move.col>(size-1) || move.row>(size-1)){
    return 0;
  }
  if(board->b[position(size,move.row,move.col)]==-1){
    board->b[position(size,move.row,move.col)] = p;
    board->size+=1;
    return 1;
  }
  else{
    return 0;
  }
}

//Check if the previous four colors of the row  are identical to the color of the position
int winning_row(struct board* board,int i, int j){
  size_t size = sqrt(board->capacity);
  int pos = position(size,i,j);
  return (board->b[pos]!=-1
	  &&board->b[pos-4]==board->b[pos]
	  &&board->b[pos-3]==board->b[pos]
	  &&board->b[pos-2]==board->b[pos]
	  &&board->b[pos-1]==board->b[pos]);
}

//Check if the previous four colors of the column are identical to the color of the position
int winning_col(struct board* board,int i, int j){
  size_t size = sqrt(board->capacity);
  int pos = position(size,i,j);
  return (board->b[pos]!=-1
	  &&board->b[pos-4*size]==board->b[pos]
	  &&board->b[pos-3*size]==board->b[pos]
	  &&board->b[pos-2*size]==board->b[pos]
	  &&board->b[pos-1*size]==board->b[pos]);
}

//Check if the previous four colors of the North-West diagonal are identical to the color of the position
int winning_ldiag(struct board* board,int i, int j){
  size_t size = sqrt(board->capacity);
  int pos = position(size,i,j);
  return (board->b[pos]!=-1
	  &&board->b[pos-4*size-4]==board->b[pos]
	  &&board->b[pos-3*size-3]==board->b[pos]
	  &&board->b[pos-2*size-2]==board->b[pos]
	  &&board->b[pos-1*size-1]==board->b[pos]);
}

//Check if the previous four colors of the North-East diagonal are identical to the color of the position
int winning_rdiag(struct board* board,int i, int j){
  size_t size = sqrt(board->capacity);
  int pos = position(size,i,j);
  return (board->b[pos]!=-1
	  &&board->b[pos-4*size+4]==board->b[pos]
	  &&board->b[pos-3*size+3]==board->b[pos]
	  &&board->b[pos-2*size+2]==board->b[pos]
	  &&board->b[pos-1*size+1]==board->b[pos]);
}

int board__is_valid_move(struct board* board, struct move_t move){
  assert(board);

  size_t size = sqrt(board->capacity);

  /* Move is outside of the board */
  if(move.row<0 || move.col<0 || move.col>(size-1) || move.row>(size-1)){
    return 0;
  }
  /* There is a pawn: not valid move */
  if(board->b[position(size,move.row,move.col)]!=-1)
    return 0;

  /* No pawn and inside the board: valid move */
  return 1;
}

void board__add_move(struct board* board, struct move_t move, enum color_t i){
  assert(board);

  size_t size = sqrt(board->capacity);

  /* Add the move on the board */
  board->b[position(size,move.row,move.col)] = i;
  board->size+=1;
  return;
}


int board__won(struct board* board,struct move_t move){
  size_t size = sqrt(board->capacity);
  int row = move.row;
  int col = move.col;

  //Check if the previous four colors of the raw  are identical to the color of the position
  for(int j = col;j<(col+5);j++){
    if((j>=4)&&(j<size)){
      if(winning_row(board,row,j)){
	return 1;
      }
    }
  }

  //Check if the previous four colors of the column are identical to the color of the position
  for(int i = row;i<(row+5);i++){
    if((i>=4)&&(i<size)){
      if(winning_col(board,i,col)){
	return 1;
      }
    }
  }

  //Check if the previous four colors of the North-West diagonal are identical to the color of the position
  for(int k = 0;k<5;k++){
    if(((row-4+k)>=0)&&((col-4+k)>=0)&&(row+k<size)&&(col+k<size)){
      if(winning_ldiag(board,row+k,col+k)){
	return 1;
      }
    }
  }


  //Check if the previous four colors of the North-East diagonal are identical to the color of the position
  for(int k = 0;k<5;k++){
    if(((row-4+k)>=0)&&((col-k)>=0)&&(row+k<size)&&(col+4-k<size)){
      if(winning_rdiag(board,row+k,col-k)){
	return 1;
      }
    }
  }

  return 0;
}
