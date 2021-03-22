#ifndef DATA_H
#define DATA_H
#include "silent.h"
#include <arpa/inet.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <string.h>

/* Différentes valeurs globales pour une meilleure compréhension du code */
#define MAX 256
#define SEM_NUMBER 2
#define EMPTY 0
#define FILLED 1
#define NO_FREE_SPACE -1
#define PEER_TAB 0
#define SEED_TAB 1
#define SEED_NOT_FOUND -1
#define OWNER_NOT_FOUND -1
#define PEER_NOT_FOUND -1
#define FILENAME_NOT_FOUND -1

enum SEM_TYPE { ADD_PEER, ADD_SEED };
/* ************************************************ */
/* Structure des fichiers (seed) */
struct seed {
  char filename[MAX]; // nom du fichier
  int len;            // longueur du fichier
  int piece_size;     // taille du découpage du fichier
  char key[MAX];      // clé du fichier
  int status;         // indique si la seed est utilisée
  int owners[MAX];    // liste des pairs possédants cette seed
  int owners_count;   // nombre de pairs posssédants cette seed
};
/* Structure des pairs (peer) */
struct peer {
  char client_ip[INET_ADDRSTRLEN]; // @ IP
  int port;                        // port d'écoute
  int files[MAX];                  // fichiers possédés par index
  int files_count;                 // nombre de fichiers possédés
  int leechs[MAX];                 // clés des fichiers qu'il veut
  int leechs_count;                // nombre de fichiers qu'il veut
  int status;                      // indique si le pair est utilisé
};

/******************************************************/
/* Change le status d'un peer ou d'une seed
 * EMPTY devient FILLED
 * FILLED devient EMPTY
 */
void change_status(int tab, int index);

/* Fonction initilisation des tableaux
 * Permet d'assurer que les champs sont bien vides initialement
 */
void init_pools();
// Fonction d'ajout de peer dans le tableau global
int add_peer();
// Fonction de modification de port du peer à d'indice index
void add_port(int port, int index);
// Fonction de modification d'IP du peer d'indice index
void add_client_ip(char *ip, int index);
// Fonction d'ajout de fichier au peer d'indice index
void add_files(int id, int index);
// Fonction d'ajout de leech du peer d'indice index
void add_leechs(int id, int index);
/* Fonction de recherche de pair par adresse IP
 * Retourne son indice s'il existe
 * PEER_NOT_FOUND le cas échéant
 */
int search_peer_by_ip(char ip[]);
// Fonction permettant de récupérer l'adresse IP du peer d'indice index
const char *get_client_ip(int index);
// Fonction permettant de récupérer le port du peer d'indice index
int get_port(int index);
// Fonction permettant de récupérer la liste d'indices de seed possédées
// du peer d'indice index
void get_peer_file_list(int *seed_list, int index);
// Fonction permettant de récupérer le nombre de fichier possédés du peer
// d'indice index
int get_peer_file_count(int index);

/*******************************************************/
// Fonction d'ajout de seed dans le tableau global
int add_seed(char key[], int peer_id);
// Fonction d'ajout de nom de fichier pour la seed d'indice index
void add_filename(char name[], int index);
// Fonction d'ajout de longueur de fichier pour la seed d'indice index
void add_len(int len, int index);
// Fonction d'ajout de taille du découpage de fichier pour la seed d'indice
// index
void add_piece_size(int size, int index);
// Fonction d'ajout de key pour la seed d'indice index
void add_key(char key[], int index);
// Fonction d'ajout de possesseur (peer_id) pour la seed d'indice index
void add_seed_owner(int index, int peer_id);
/* Fonction de recherche de seed par key
 * Retourne son indice si elle existe
 * SEED_NOT_FOUND le cas échéant
 */
int search_seed_by_key(char key[]);
/* Fonction de recherche de seed par nom de fichier
 * Stocke dans index_list les indices des seeds trouvées
 * Retourne le nombre de seed trouvée
 * SEED_NOT_FOUND si ce nombre vaut 0
 */
int search_seed_by_filename(char filename[], int *index_list);
// Fonction de récupération de liste d'indice de pairs possédant la seed
// d'indice index
const int *get_seed_owner_list(int index);
// Fonction de récupération du nombre de pairs possèdant la seed d'indice index
int get_seed_owner_count(int index);
// Fonction de récupération de la longueur de fichier de la seed d'indice index
int get_seed_length(int index);
// Fonction de récupération de de la taille du découpage de la seed d'indice
// index
int get_seed_piecesize(int index);
/* Fonction de récupération du pointeur du tableau seed
 * Elle remplit aussi l'argument seed_count avec le nombre de seed actuellement
 * dans le tableau
 * Sert seulement pour le filtrage dans la fonction parser_update()
 * A utiliser avec précaution
 */
void get_global_seed_list(int *seed_list, int *seed_count);
// Fonction de récupération de la key de la seed d'indice index
const char *get_seed_key(int index);
// Fonction de récupération du nom de fichier de la seed d'indice index
const char *get_seed_filename(int index);
/*******************************************************/
/* Fonction permettant d'enlever les anciens fichiers du pair d'indice index
 * avant mise à jour via la commande update */
void reset_update_peer(int index, int old_filecount);
/* Fonction à appeler si la pair se déconnecte en utilisant son indice */
void reset_peer(int index);
/* Fonction à appeler pour déconnecter un pair via son adresse IP */
void disconnect_peer(char ip[]);
#endif
