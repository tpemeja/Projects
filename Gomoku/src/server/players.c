/**
 * @file players.c
 * @date 20 mars 2019
 * @version 1.1
 *
 * This file is the code implementation of struct player_t and struct current_player
 */

/* Libraries */
#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <assert.h>

/* Files */
#include "move.h"
#include "moves.h"
#include "players.h"

/* Size of board */
extern int size_of_board;

/**
 * ----------------------------------------------------
 * player_t
 * ----------------------------------------------------
 */

/**
 * @brief Initialize a specific player with its functions
 * @param[in/out] p pointer to a loaded library
 * @return Player initialized with all functions linked to libraries
 */
static struct player_t players__initialize_player(void* p){
  assert(p);

  struct player_t pt;

  /* Link pointers function to real functions */
  pt.get_player_name = dlsym(p,"get_player_name");
  pt.propose_opening = dlsym(p,"propose_opening");
  pt.accept_opening = dlsym(p,"accept_opening");
  pt.initialize = dlsym(p,"initialize");
  pt.play = dlsym(p,"play");
  pt.finalize = dlsym(p,"finalize");
  pt.handle = p;
  return pt;
}

void players__initialize(char** argv, int argc, struct player_t players[NB_PLAYERS]){
  assert(players);

  /* Buffer */
  char s1[100];
  /* Temporary library */
  void* p = NULL;

  for(int i = 0; i < NB_PLAYERS; i ++){
    strcpy(s1,"./");
    strcat(s1,argv[argc-i-1]);
    p = dlopen(s1,RTLD_LAZY);

    /* Verify the library is loaded */
    assert(p);

    /* Initialize a specific player with the loaded library */
    players[i] = players__initialize_player(p);
  }
}

void players__free(struct player_t players[NB_PLAYERS]){
  assert(players);
  /* Free each players of the array */
  for(int i = 0; i < NB_PLAYERS; i++){
    players[i].finalize();
    dlclose(players[i].handle);
  }
}

/**
 * ----------------------------------------------------
 * current_player
 * ----------------------------------------------------
 */

struct current_player current_player__initialize(){
  struct current_player cp = { 0, BLACK };
  return cp;
}

enum color_t current_player__get_color(const struct current_player cp){
  return cp.color;
}

void current_player__next(struct current_player *cp){
  assert(cp);

  /* Compute next player */
  cp->number = (cp->number + 1) % NB_PLAYERS;
  /*Compute the next color*/
  cp->color = (cp->color + 1) % NB_PLAYERS;
}
