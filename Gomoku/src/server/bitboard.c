/**
 * @file bitboard.c
 */

/* Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "time.h"
#include "bitboard.h"

/* Files */
#include "../players/list.h"
#include "move.h"

/* Macro functions */
#define MIN(a,b) ((a) < (b))?(a):(b)
#define MAX(a,b) ((a) > (b))?(a):(b)

/**
 * @brief Initialize the board
 * @param[in] size size given in argument during running : n
 * @return initialized board (allocated in the heap) with unsigned 128-bit int for all players of capacity n*n
 */
struct board * board__initialize(size_t size){
  struct board* board = malloc(sizeof(struct board));
  board->capacity = (size*size);

  /* Allocate boards for players */
  board->b_w = malloc(sizeof(__uint128_t));
  board->b_b = malloc(sizeof(__uint128_t));
  *board->b_w=0;*board->b_b=0;

  /* Init all not used bits at 1 */
  for(int i = 0; i<(128-board->capacity); i++){
    *board->b_w=*(board->b_w) << 1;
    *board->b_w+=1;
    *board->b_b=*(board->b_b) << 1;
    *board->b_b+=1;
  }

  /* Go at the first bit of the int */
  *board->b_w=*board->b_w<<(board->capacity);
  *board->b_b=*board->b_b<<(board->capacity);
  return board;
}

/**
 * @brief Return a copy of a board : useful for players in order to compare evaluated boards
 * @param[in] board source board that will be copied
 * @return a copy of the argument allocated in the heap
 */
struct board * board__copy(struct board* board){
  assert(board);

  struct board * new = malloc(sizeof(*new));
  new->capacity = board->capacity;
  new->b_w = malloc(sizeof(__uint128_t));
  new->b_b = malloc(sizeof(__uint128_t));
  *new->b_w = *board->b_w;
  *new->b_b = *board->b_b;

  return new;
}

/**
 * @brief Select the bit at position given in argument of an unsigned 128-bit int as unsigned int
 * @param[in] b unsigned 128-bit int
 * @param[in] pos position of the bit in the int
 * @return value of the bit at the position pos
 */
__uint128_t board__select_bit(__uint128_t* b, int pos){
  return(((*b) >> (pos-1))&1);
}

/**
 * @brief Return all possible moves on the board: useful for players
 * @param[in] board source board with pawns inside
 * @return a list of move_t with possible moves
 */
struct list * board__possible_moves(struct board* board){
  assert(board);

  size_t size = sqrt(board->capacity);
  struct list * l = list_generate();

  for (size_t i = 0; i < size; i++){
    for(size_t j = 0; j < size; j++){
      if (board__select_bit(board->b_w, i*size+j+1) == 0
	  && board__select_bit(board->b_b, i*size+j+1) == 0)
	list_add(l, i, j);
    }
  }
  return l;
}

/**
 * @brief Return only one possible move in a board (among all possible moves): useful for players (Montecarlo)
 * @param[in] board source board with pawns inside
 * @return a move_t with a possible move
 */
struct move_t board__possible_move(struct board* board){
  assert(board);

  struct list * l = board__possible_moves(board);

  /* Choose a random move inside all possible moves */
  int a = rand() % list_length(l);
  struct move_t mv = list_get(l, a);
  list_free(l);
  return mv;
}

/* -------------- Getters -------------- */
/**
 * @brief Get the board (unsigned 128-bit int) of the player given in argument
 * @param[in] board board full of pawns for all players
 * @param[in] p player chosen
 * @return board (unsigned 128-bit int) of the given player
 */
__uint128_t board__get_player_board(struct board* board, int p){
  assert(board);

  if(p==BLACK)
    return *board->b_b;

  return *board->b_w;
}

/**
 * @brief Get the all board (unsigned 128-bit int) with pawns of all players
 * @param[in] board board full of pawns for all players
 * @param[in] p player chosen
 * @return board (unsigned 128-bit int) of the given player
 */
__uint128_t board__all_pawns(struct board* board){
  return (*board->b_b)|(*board->b_w);
}

/**
 * @brief Check if the board is full. To do so, bitwise operations are used : if the bitboard is full, means (board black OR white board) == -1
 * @param[in] board board where are checked white pawns and black pawns
 * @return 1 if the board is full, 0 otherwise
 */
int board__is_full(struct board* board){
  assert(board);
  __uint128_t full = -1;
  return ((*board->b_w|*board->b_b)==full);
}

/**
 * @brief Give the position of the bit for a position i,j on the board
 * @param[in] size of the board
 * @param[in] i row of the board
 * @param[in] j column of the board
 * @return position of the bit for unsigned 128-bit int
 */
int board__position(size_t size,int i,int j){
  return(i*size+j);
}

/**
 * @brief Get the color of the pawn at the position i,j
 * @param[in] board board where the color of the pawn is found
 * @param[in] i position of the row
 * @param[in] j position of the column
 * @return BLACK,WHITE,<other color> if there is a pawn at the position i,j; -1 otherwise
 */
int board__get_color(struct board *board, int i, int j){
  assert(board);

  size_t s = sqrt(board->capacity);
  int pos = board__position(s,i,j);

  /* Get the bit at position pos for both players */
  __uint128_t pawn_w = board__select_bit(board->b_w,pos+1);
  __uint128_t pawn_b = board__select_bit(board->b_b,pos+1);

  /* No pawn at the position i,j for both black and white players */
  if(!pawn_w && !pawn_b)
    return -1;

  /* If there is a pawn for WHITE */
  if(pawn_w)
    return WHITE;

  /* Else, BLACK pawn */
  return BLACK;
}

/**
 * @brief Verify if the give move (at position i,j) is a valid move
 * @param[in] board board full of moves
 * @param[in] move given move at position i,j that needs to be validated
 * @param[in] p current player number
 * @return 1 if the move is valid, 0 otherwise
 */
int board__is_valid_move(struct board* board, struct move_t move){
  assert(board);

  size_t size = sqrt(board->capacity);
  /* Move is outside of the board */
  if(move.row<0 || move.col<0 || move.col>(size-1) || move.row>(size-1)){
    return 0;
  }

  /* Get position pos of the bit for the position of the move */
  int pos = board__position(size,move.row,move.col);

  /* If there is a pawn at the position : not a valid move */
  if(board__select_bit(board->b_w,pos+1) == 0
     && board__select_bit(board->b_b,pos+1) == 0){
    return 1;
  }

  /* Invalid move */
  return 0;
}

/**
 * @brief Add a pawn on the board. The precondition here is the move is valid and can be added to the board
 * @param[in/out] board board where the pawn has to be added
 * @param[in] move move to be added
 * @param[in] i color of the current player
 * @return board with the pawn on it
 */
void board__add_move(struct board * board, struct move_t move, enum color_t i){
  assert(board);

  /* Get position pos of the bit for the position of the move */
  __uint128_t bit = 0;
  bit++;
  bit = bit << board__position(sqrt(board->capacity),move.row,move.col);

  /* Add the pawn on the bitboard */
  if(i == WHITE)
    *board->b_w = *board->b_w | bit;
  else
    *board->b_b = *board->b_b | bit;

  return;
}


/**
 * @brief Remove a move on the board : useful for players that fill board a lot in order to find the best board possible
 * @param[in/out] board board where the move will be removed
 * @param[in] move positions for the move
 * @return 0 if the move was correctly removed from the board, 1 of there is no pawn for the move
 */
int board__remove_move(struct board *board, struct move_t move){
  assert(board);

  /* Verify that there is pawn at the position on the board */
  if(board__get_color(board,move.row,move.col)==-1){
    return 1;
  }

  /* Get position pos of the bit for the position of the move */
  __uint128_t bit = 0;
  bit++;
  bit = bit << board__position(sqrt(board->capacity),move.row,move.col);
  bit = ~bit;

  /* Remove the pawn on the bitboard */
  *board->b_w = *board->b_w & bit;
  *board->b_b = *board->b_b & bit;
  return 0;
}

/* -------------- Handling winning verifications -------------- */

/**
 * @brief Check if the previous four colors of the row are identical to the color of the position: check if there is a winning row
 * @param[in] board board where are verified positions
 * @param[in] mask mask of 5 following bits corresponding to the 4 previous positions and position added
 * @return 1 if either BLACK pawns or WHITE pawns have a winning row
 */
int board__winning_row(struct board* board, __uint128_t mask){
  assert(board);
  return(((*board->b_w & mask) == mask) || ((*board->b_b & mask) == mask));
}

/**
 * @brief Check if the previous four colors of the column are identical to the color of the position: check if there is a winning column
 * @param[in] board board where are verified positions
 * @param[in] mask mask of 5 following bits corresponding to the 4 previous positions and position added
 * @return 1 if either BLACK pawns or WHITE pawns have a winning column
 */
int board__winning_col(struct board* board, __uint128_t mask){
  assert(board);
  return(((*board->b_w & mask) == mask) || ((*board->b_b & mask) == mask));
}

/**
 * @brief Check if the previous four colors of the North-West diagonal are identical to the color of the position
 * @param[in] board board where are verified positions
 * @param[in] mask mask of 5 following bits corresponding to the 4 previous positions and position added
 * @return 1 if either BLACK pawns or WHITE pawns have a winning left diagonal
 */
int board__winning_ldiag(struct board* board, __uint128_t mask){
  assert(board);
  return(((*board->b_w & mask) == mask) || ((*board->b_b & mask) == mask));
}

/**
 * @brief Check if the previous four colors of the North-East diagonal are identical to the color of the position
 * @param[in] board board where are verified positions
 * @param[in] mask mask of 5 following bits corresponding to the 4 previous positions and position added
 * @return 1 if either BLACK pawns or WHITE pawns have a winning right diagonal
 */
int board__winning_rdiag(struct board* board, __uint128_t mask){
  assert(board);
  return(((*board->b_w & mask) == mask) || ((*board->b_b & mask) == mask));
}

/**
 * @brief Check if the previous four colors on the row are identical to the color of the position
 * @param[in] board board where are verified positions
 * @param[in] move move just added to the board that needs to be verified
 * @return 1 if the result of the move on the board is a winning situation, 0 otherwise
 */
int board__won_row(struct board* board, struct move_t move){
  size_t size = sqrt(board->capacity);
  int row = move.row;
  int col = move.col;

  /* Mask to verify 5 bits at 1 in a row : 11111 */
  __uint128_t mask_u = 31;

  /* Find the beginning where we start to search for a winning row (handle limits of the board */
  int deb_col = ((col-4>=0)?col-4:0);

  /* Positionning the mask at the beginning of the verification */
  __uint128_t mask_row = (mask_u << (row*size+deb_col));

  for(int j = deb_col;j<(deb_col+5);j++){
    if(j<size-4){
      if(board__winning_row(board,mask_row))
	return 1;
      mask_row = mask_row << 1;
    }
  }
  return 0;
}


/**
 * @brief Check if the previous four colors on the column are identical to the color of the position
 * @param[in] board board where are verified positions
 * @param[in] move move just added to the board that needs to be verified
 * @return 1 if the result of the move on the board is a winning situation, 0 otherwise
 */
int board__won_col(struct board* board, struct move_t move){
  size_t size = sqrt(board->capacity);
  int row = move.row;
  int col = move.col;

 /* Same principle for columns */
  __uint128_t mask_u = 1;
  int deb_row = ((row-4>=0)?row-4:0);
  mask_u = mask_u << (deb_row*size+col);
  __uint128_t mask_col = (mask_u << size) | mask_u;
  mask_col = (mask_col << size) | mask_u;
  mask_col = (mask_col << size) | mask_u;
  mask_col = (mask_col << size) | mask_u;

  for(int i = deb_row;i<(deb_row+5);i++){
    if(i<size-4){
      if(board__winning_col(board,mask_col)){
	return 1;
      }
      mask_col = mask_col << size;
    }
  }
  return 0;
}

/**
 * @brief Check if the previous four colors on the left diagonal are identical to the color of the position
 * @param[in] board board where are verified positions
 * @param[in] move move just added to the board that needs to be verified
 * @return 1 if the result of the move on the board is a winning situation, 0 otherwise
 */
int board__won_ldiag(struct board* board, struct move_t move){
  size_t size = sqrt(board->capacity);
  int row = move.row;
  int col = move.col;

  /* Same principle for the left diagonals */
  int deb_ldiag = MIN(((row-4>=0)?4:row),((col-4>=0)?4:col));
  __uint128_t mask_u = 1;
  mask_u = mask_u << ((row-deb_ldiag)*size+(col-deb_ldiag));
  __uint128_t mask_ldiag = (mask_u << (size+1)) | mask_u;
  mask_ldiag = (mask_ldiag << (size+1)) | mask_u;
  mask_ldiag = (mask_ldiag << (size+1)) | mask_u;
  mask_ldiag = (mask_ldiag << (size+1)) | mask_u;
  for(int k = 0;k<5;k++){
    if(((row-deb_ldiag+k)>=0)&&
       ((col-deb_ldiag+k)>=0)&&
       (row-deb_ldiag+4+k<size)&&
       (col-deb_ldiag+4+k<size)){
      if(board__winning_ldiag(board,mask_ldiag))
	return 1;
      mask_ldiag = mask_ldiag << (size+1);
    }
  }
  return 0;
}

/**
 * @brief Check if the previous four colors on the right diagonal are identical to the color of the position
 * @param[in] board board where are verified positions
 * @param[in] move move just added to the board that needs to be verified
 * @return 1 if the result of the move on the board is a winning situation, 0 otherwise
 */
int board__won_rdiag(struct board* board, struct move_t move){
  size_t size = sqrt(board->capacity);
  int row = move.row;
  int col = move.col;

  /* Same principle for the right diagonals */
  int deb_rdiag = MIN(((row-4>=0)?4:row),((col+4<=size)?4:(size-col-1)));
  __uint128_t mask_u = 1;
  mask_u = mask_u << ((row-deb_rdiag)*size+(col+deb_rdiag));
  __uint128_t mask_rdiag = (mask_u << (size-1)) | mask_u;
  mask_rdiag = (mask_rdiag << (size-1)) | mask_u;
  mask_rdiag = (mask_rdiag << (size-1)) | mask_u;
  mask_rdiag = (mask_rdiag << (size-1)) | mask_u;
  for(int k = 0;k<5;k++){
    if(((row-deb_rdiag+k)>=0)&&
       ((col+deb_rdiag-k)<size)&&
       (row-deb_rdiag+4+k<size)&&
       (col+deb_rdiag-4-k>=0)){
      if(board__winning_rdiag(board,mask_rdiag))
	return 1;
      mask_rdiag = mask_rdiag << (size-1);
    }
  }
  return 0;
}

/**
 * @brief Check if someone won (either BLACK or WHITE). Verifies if the move given in argument is in a winning situation: columns, rows, left diagonals or right diagonals
 * @param[in] board board where are verified positions
 * @param[in] move move just added to the board that needs to be verified
 * @return 1 if the result of the move on the board is a winning situation, 0 otherwise
 */
int board__won(struct board* board, struct move_t move){
  assert(board);
  /* Verify all winning cases : all directions, verify 5 following cells */
  /* No winning situations, not a win */
  return  (board__won_row(board,move)|\
	   board__won_col(board,move)|\
	   board__won_ldiag(board,move)|\
	   board__won_rdiag(board,move));
}

/* --------------------------------*/
/**
 * @brief Update the length of a box alignment of the same color and spacing
 * @param[in] board_player board of the player tested
 * @param[in] board current board
 * @param[in/out] shift_i mask use to check the length
 * @param[in] direction direction that we check
 * @param[in/out] max_length length of the largest alignment
 * @param[in/out] length length of the alignment
 * @param[in/out] occ number of shifting
 * @return update length, max_length and occ
 */
void board__cal_length(__uint128_t* board_player,__uint128_t* board,__uint128_t* shift_i,int direction,int* max_length,int* possible_length,int* length,int* occ){
  //print_128(*shift_i);
  if(*occ&&(*shift_i!=0)){
    if((*shift_i & *board_player)!=0){
      *length += (*length==*max_length);
      *possible_length += ((*possible_length==(*max_length))||(*possible_length==(*max_length-1)));
      *max_length += 1;
      if(direction>0){
	*shift_i = *shift_i << direction;
      }else{
	*shift_i = *shift_i >> -direction;
      }
    }else{
      if((*shift_i & *board) != 0){
	if(direction>0){
	  *shift_i = *shift_i << direction;
	}else{
	  *shift_i = *shift_i >> -direction;
	}
	*max_length+=1;
      }else{
	*shift_i = 0;
      }
    }
    *occ-=1;
  }else{
    *shift_i=0;
  }
}

/**
 * @brief Get the number of possible shift for one direction
 * @param[in/out] occ array which will contain the shift on each side of the position
 * @param[in] i row of the board
 * @param[in] j column of the board
 * @param[in] direction direction that we check
 * @param[in] size size of the board
 */
void board__cal_occ(int* occ,int i,int j,int direction,size_t size){
  if(direction==1){
    occ[0]=MIN(4,j);
    occ[1]=MIN(4,size-j-1);
  }else{
    if(direction==size){
      occ[0] = MIN(4,i);
      occ[1] = MIN(4,size-i-1);
    }else{
      if(direction==size+1){
	occ[0]=MIN(4,MIN(i,j));
	occ[1]=MIN(4,MIN(size-i-1,size-j-1));
      }else{
	occ[1]=MIN(4,MIN(i,(size-1-j)));
	occ[0]=MIN(4,MIN(size-i-1,j));
      }
    }
  }
}

// 0 = vertical
// 1 = diagonal north east
// 2 = horizontal
// 3 = diagonal north west

/**
 * @brief Update the occurence of different patterns
 * @param[in/out] pattern array which contains the occurence of different patterns
 * @param[in] length length of the alignement
 * @param[in] free number of spacing on each side of the alignment
 * @return the occurence of the pattern updated
 */
void board__update_pattern(int* pattern,int length,int possible_length_R,int possible_length_L, int free){
  enum pat { FIVE=0, FOUR_OPEN=1, FOUR_HALF=2,FOUR_SPACED = 3, THREE_OPEN=4, THREE_HALF=5, TWO_OPEN=6, TWO_HALF=7, ONE= 8};
  if (length>=5){
    pattern[FIVE]+=1;
  }else if((possible_length_R>=5)&&(possible_length_L>=5)){
    pattern[FOUR_SPACED]+=2;
  }else if(length==4){
    pattern[3-free]+=1;
  }else if(possible_length_R>=5){
    pattern[FOUR_SPACED]+=1;
  }else if(possible_length_L>=5){
    pattern[FOUR_SPACED]+=1;
  }else if(length==1){
    pattern[ONE]+=1;
  }else{
    pattern[(5-length)*2+(2-free)]+=1;
  }
}



/**
 * @brief Update the occurence of the pattern for a given direction
 * @param[in] board current board
 * @param[in] i row of the board
 * @param[in] j column of the board
 * @param[in] direction direction that we check
 * @param[in] color color of the player tested
 * @param[in/out] pattern array which contains the occurence of different patterns
 * @return pattern updated for the direction
 */
void board__explore_line(struct board* b, int i,int j,int direction,int color,int* pattern){
  size_t size = sqrt(b->capacity);
  //board__print(b);
  int directions[] = {size, -size+1, 1, size+1};
  enum shift_def { R=0, L=1 };
  int dir = directions[direction];
  __uint128_t board_player = board__get_player_board(b,color); //Board if compose of 1 if it's the player and 0 else
  __uint128_t board = ~board__all_pawns(b); //Board if compose of 1 if the position is empty and 0 else
  //print_128(board_player);
  //print_128(board);
  int max_length[2] = {0,0};
  int length[2] = {0,0};
  int possible_length[2] = {0,0};
  int occ[2];
  board__cal_occ(occ,i,j,dir,size);
  __uint128_t shift[2];
  shift[R] = 1;
  if(dir < 0){
    int swap = occ[R];
    occ[R] = occ[L];
    occ[L] = swap;
    dir=-dir;
  }
  shift[R] = shift[R] << (((board__position(size,i,j)-dir)>=0)?		\
			  (board__position(size,i,j)-dir):		\
			  board__position(size,i,j));
  shift[L] = shift[R] << (((board__position(size,i,j)-dir)>=0)?	\
			  (2*dir):				\
			  dir);
  while((shift[R]|shift[L])!=0){
    //print_128(shift[R]);
    //print_128(shift[L]);
    //printf("occ: %d %d / R: %d %d / L: %d %d\n",occ[R],occ[L],length[R],max_length[R],length[L],max_length[L]);
    board__cal_length(&board_player,&board, shift+R,-dir,max_length+R,possible_length+R,length+R,occ+R);
    board__cal_length(&board_player,&board,shift+L,dir,max_length+L,possible_length+L,length+L,occ+L);
  }
  int new_length = (max_length[R]+max_length[L])<4?0:length[R]+length[L]+1;
  int free = (length[R]!=max_length[R])+(length[L]!=max_length[L]);
  int new_possible_length_R = (max_length[R]+max_length[L])<4?\
    0:\
    possible_length[R]+length[L]+1;
  int new_possible_length_L = (max_length[R]+max_length[L])<4?\
    0:\
    length[R]+possible_length[L]+1;
  if(new_length!=0){
    board__update_pattern(pattern,new_length,new_possible_length_R	\
			  ,new_possible_length_L,free);
  }
}
/**
 * @brief Free the board given in argument
 * @param[in/out] board board that needs to be freed
 * @return freed board
 */
void board__free(struct board* board){
  assert(board);
  free(board->b_w);
  free(board->b_b);
  free(board);
}

/* ------------- DEBUG FUNCTIONS --------------- */
/**
 * @brief Print the int128 given in argument
 * @param[in/out] j int128 that needs to be printed
 * @return int128 printed
 */
void print_128(__uint128_t j){
  for(int i = 1; i<129; i++){
    printf("%d", board__select_bit(&j,i) == 1);
  }
  printf("\n");
}

/**
 * @brief Print the board given in argument
 * @param[in/out] board board that needs to be printed
 * @return board printed
 */
void board__print(struct board * board){
  print_128(*board->b_b);
  print_128(*board->b_w);
}
