#ifndef PARSER_H
#define PARSER_H

#include "data.h"
#include "silent.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum REQUETE_TYPE { ANNOUNCE, LOOK, GETFILE };
/* Différencier les types de requête */
enum RESPONSE_TYPE {
  REQUEST_SUCCESS,
  REQUEST_ERROR,
  ANNOUNCE_REQUEST,
  LOOK_REQUEST,
  GETFILE_REQUEST,
  UPDATE_REQUEST,
  QUIT_REQUEST
};
enum ANNOUNCE_MODE { LISTEN, SEED, LEECH };
enum SEED_ARG_TYPE { FILENAME, LENGTH, PIECESIZE, KEY };

#define NO_MODE_SELECTED -1

/* Redirige le parser vers la bonne sous-fonction */
int parser(char *buffer, char ip[]);

/* Sous fonctions de parsing
 * Si nécessaire, le champ "output" est rempli avec ce que doit retourner
 * le tracker au pair
 * Initialement ce champ contient l'adresse IP du pair en question
 * Chaque fonction retourne REQUEST_SUCCESS en cas de réussite ou
 * REQUEST_ERROR le cas échéant
 */
/* Parsing dédié à la commande announce */
int parser_announce(char *buffer, char output[]);
/* Parsing dédié à la commande update */
int parser_update(char *buffer, char output[]);
/* Parsing dédié à la commande look */
int parser_look(char *buffer, char output[]);
/* Parsing dédié à la commande getfile */
int parser_getfile(char *buffer, char output[]);
/* Parsing dédié à la commande quit */
int parser_quit(char *buffer, char output[]);

/* ********************************************** */

#endif
