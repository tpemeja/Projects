#include <stdio.h>
#include <stdlib.h>
#include "move.h"
#include "evaluate_opening.h"

struct col_move_t * generate_direct_opening(size_t size, int i){
  int possible_i[26] = {-2,-2,-2,-1,-2,0,-2,1,-2,2,-1,0,-1,1,-1,2,0,1,0,2,1,1,1,2,2,2};
  struct col_move_t * cmv = malloc(sizeof(struct col_move_t)*3); 
  cmv[0].m.row = size/2;
  cmv[0].m.col = size/2;
  cmv[0].c = BLACK;
  cmv[1].m.row = size/2;
  cmv[1].m.col = size/2-1;
  cmv[1].c = WHITE;
  cmv[2].m.row = size/2 + possible_i[2*i];
  cmv[2].m.col = size/2 + possible_i[2*i+1];
  cmv[2].c = BLACK;
  return cmv;
}

 
struct col_move_t * generate_indirect_opening(size_t size, int i){
  int possible_d[26] = {0,-2,1,-2,2,-2,1,-1,2,-1,1,0,2,0,0,1,1,1,2,1,2,0,2,1,2,2};
  struct col_move_t * cmv = malloc(sizeof(struct col_move_t)*3);
  cmv[0].m.row = size/2;
  cmv[0].m.col = size/2;
  cmv[0].c = BLACK;
  cmv[1].m.row = size/2;
  cmv[1].m.col = size/2-1;
  cmv[1].c = WHITE;
  cmv[2].m.row = size/2 + possible_d[2*i] ;
  cmv[2].m.col = size/2 + possible_d[2*i+1];
  cmv[2].c = BLACK;
  return cmv;
} 

