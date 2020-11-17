/* Libraries */
#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <assert.h>
#include <getopt.h>
#include <string.h>
#include <time.h>

/* Files */
#include "move.h"
#include "game.h"
#include "utils.h"
#include "moves.h"
#include "players.h"
#include "bitboard.h"
#include "evaluate_opening.h"

#define NB_EXP_OPENING 1
#define NB_OPENING 0
#define NB_EXP 5000000
#define NB_PLAYER 1
#define NB_EVALUATE 10 //Nombre de board différent
#define MAX_WORD_LENGTH 3
#define NB_MAX 35

#define MIN_VALUE 0
#define MAX_VALUE 50
size_t size_of_board = 7;
int opening = 0;

// this programs reads the next word of an opened file
void r_file(FILE* file,char word[]){
  int i=0;
  char ch = fgetc(file); //gets the next character
  while(ch==' '||ch=='\n'){ //in case there is a comma, then a space
    ch = fgetc(file);
  }
  while(ch!=' '&&ch!='\n'&&ch!=EOF){
    word[i]= ch; //put the character in the string "word"
    i++;
    ch = fgetc(file);
  }
  for(int j=i;j<MAX_WORD_LENGTH;j++){
    word[j]=' ';
  }
}

int generate_move(FILE* text,struct move_t* moves){ //Moves est doit être de la taille max de coups possibles
  char word[MAX_WORD_LENGTH];
  r_file(text,word);
  // printf("Value : %s\n",word);
  r_file(text,word);
  int length = atoi(word);
  struct move_t m;
  for(int i=0;i<length;i++){
    r_file(text,word);
    m.row=atoi(word);
    r_file(text,word);
    m.col=atoi(word);
    moves[i]=m;
  }
  return length;
}

int generate_moves(FILE* text,struct move_t* moves,int nb){
  int length;
  for(int i = 0; i<nb;i++){
    length = generate_move(text,moves);
    /* printf("--- %d ---\n",length);
    for(int i = 0; i < length ;i++){
      printf("%zd %zd\n",moves[i].row,moves[i].col);
      }*/
  }
  return length;
}

void create_path(char* path,int taille,int i){
  char staille[10]="";
  char svalue[4]="";
  char sp[1]="_";
  char end_path[]=".txt";
  strcpy(path,"../board_generated/board_generated_");
  sprintf(staille,"%d",taille);
  sprintf(svalue,"%d",i);
  strcat(path,staille);
  strcat(path,sp);
  strcat(path,end_path);
}

void free_all(struct board* board, struct player_t players[NB_PLAYER], struct moves* moves){
  players__free(players);
  board__free(board);
  moves__free(moves);
}

int make_them_play(struct board* board,struct moves* moves, struct player_t players[NB_PLAYER], struct current_player cp){
  void (*actualize)(struct col_move_t const previous_moves[], size_t n_moves) = dlsym(players[0].handle,"update_own_board");
  size_t siz = moves__get_size(moves);
  struct move_t m;
  int color = siz % 2;
  int win;
  actualize(moves__last_n(moves),siz);
  for(int i =0;i<siz ; i++){
    board__add_move(board,moves__last_n(moves)[i].m,moves__last_n(moves)[i].c);
  }
  while(1){
    /* Current player plays considering last n moves */
    m = players[0].play(moves__last_n(moves),moves__get_size(moves));
    /*printf("he played : %ld %ld\n", m.row, m.col);*/

    /* Verify if the move is_valid or not if it is it updates the board */
     if(!(board__is_valid_move(board,m))){

      printf("Le coup du joueur %s est un coup invalide (%ld %ld)\n",players[cp.number].get_player_name(), m.row, m.col);
      free_all(board,players,moves);
      return 0;
     }

    /* Add the move on the board */
    board__add_move(board,m,color);

    /* Verify if a player is winning */
    win = board__won(board,m);
    if(win || board__is_full(board)){
      if(win){
	return color;
      }
      else{
	return 2;
      }
    }
    color = (color + 1) % 2;
  }
  return -1;
}

struct moves * generate__list_of_moves(struct move_t* list_move,size_t length, size_t size ){
  struct col_move_t * list_of_moves = malloc(sizeof(struct col_move_t)*length);
  for (int i = 0 ;i<length ;i++){
    list_of_moves[i].m = list_move[i];
    list_of_moves[i].c = i % 2;
  }
  struct moves* move = moves__initialize();
  moves__update(move,length,list_of_moves);
  return move;
}
// 15

int main(int argc, char** argv){
  time_t t;
  srand((unsigned) time(&t));
  /* Parse the options */
  if(parse_opts(argc,argv) != 1){
    printf("Wrong usage of the function %s",argv[0]);
    return 1;
  }
  /* Initialize all structures for the game */
  struct current_player cp = current_player__initialize();
  struct player_t players[NB_PLAYER];
  players__initialize(argv,argc,players);
  int white = 0;
  int black = 0;
  int draw = 0;
  int test = 0;
  int nb_eval = NB_EVALUATE;
  int nb_exp = NB_EXP;
  FILE* text;
  char path[100]="";
  struct move_t list_move[NB_MAX];
  if(opening){
    nb_eval = NB_OPENING;
    nb_exp = NB_EXP_OPENING;
  }
  struct board* board;
  //struct moves* moves;
  size_t length;
  for(int i = MIN_VALUE; i<MAX_VALUE+1; i+=5){ //FORCEMENT DANS LE MAIN
    create_path(path,size_of_board,i);
    printf("*** %s ****\n",path);
    text=fopen(path,"r"); // FORCEMENT DANS LE MAIN
    for(int i = 0; i< nb_eval;i++){
      length=generate_move(text,list_move);
      board = board__initialize(size_of_board);
      struct moves* moves = moves__initialize();
      struct col_move_t* list_of_moves;
      size_t nb_move;
      if(opening){
	list_of_moves = generate_indirect_opening(size_of_board,i);
	moves__update(moves,nb_move,list_of_moves);
	nb_move = 3;
      }
      else{
	struct moves* moving = generate__list_of_moves(list_move,length,size_of_board);
	moves__update(moves,moves__get_size(moving),moves__last_n(moving));
	free(moving);
      }
      for(int j = 0; j<nb_exp;j++){
	if(j!=0){
	  board = board__initialize(size_of_board);
	}
	players[0].initialize(size_of_board,WHITE);
	test = make_them_play(board,moves,players,cp);
	if(test == 0){
	  black += 1;
	}
	if(test == 1){
	  white += 1;
	}
	if(test != 0 && test != 1){
	  draw += 1; 
	}
	players[0].finalize();
	board__free(board);
      }
    moves__free(moves);
    }
    printf("BLACK pour un heuristic de %d : ", i);
    printf("%d\n",black);
    black = 0;
    printf("WHITE pour un heuristic de %d : ", i);
    printf("%d\n",white);
    white = 0;
    printf("DRAW pour un heuristic de %d : ", i);
    printf("%d\n",draw);
    draw = 0;
  }
  dlclose(players[0].handle);
  return 0;
}
