#include "data.h"

/* tableau contenant toutes les données sur toutes les pairs que l'on connait */
static struct peer peers[MAX];
/* tableau contenant toutes les données sur tous les fichiers que l'on connait
 */
static struct seed seeds[MAX];
/* tableau de sémaphores pour les pb de concurrence */
sem_t semaphores[SEM_NUMBER];

/******************************************************/

void init_pools() {
  silent_print("Data base initialization..");
  for (int i = 0; i < MAX; i++) {
    peers[i].status = EMPTY;
    peers[i].files_count = EMPTY;
    peers[i].leechs_count = EMPTY;
    seeds[i].status = EMPTY;
    seeds[i].owners_count = EMPTY;
  }
  for (int i = 0; i < SEM_NUMBER; i++) {
    if (sem_init(&semaphores[i], PTHREAD_PROCESS_SHARED, 1) == 1) {
      silent_print("SEMAPHORE FAILED TO INITIALIZE\n");
    }
  }
  silent_print("  OK\n");
}

int next_free_peer() {
  int index = 0;
  while (peers[index].status == FILLED) {
    index++;
  }
  if (index < MAX) {
    return index;
  } else {
    silent_print(" NO MORE SPACE ");
    return NO_FREE_SPACE;
  }
}

int next_free_seed() {
  int index = 0;
  while (seeds[index].status == FILLED) {
    index++;
  }
  if (index < MAX) {
    return index;
  } else {
    silent_print(" NO MORE SPACE ");
    return NO_FREE_SPACE;
  }
}

int search_seed_by_filename(char filename[], int *index_list) {
  int cpt = 0;
  for (int i = 0; i < MAX; i++) {
    if ((strcmp(seeds[i].filename, filename) == 0) &&
        seeds[i].status == FILLED && seeds[i].owners_count > 0) {
      index_list[cpt] = i;
      cpt++;
    }
  }
  if (cpt == 0) {
    return FILENAME_NOT_FOUND;
  }
  return cpt;
}

int search_seed_by_key(char key[]) {
  for (int i = 0; i < MAX; i++) {
    if ((strcmp(seeds[i].key, key) == 0) && seeds[i].status == FILLED &&
        seeds[i].owners_count > 0) {
      return i;
    }
  }
  return SEED_NOT_FOUND;
}

int search_peer_by_ip(char ip[]) {
  for (int i = 0; i < MAX; i++) {
    if ((strcmp(peers[i].client_ip, ip) == 0) && peers[i].status == FILLED) {
      return i;
    }
  }
  return PEER_NOT_FOUND;
}

void change_status(int tab, int index) {
  switch (tab) {
  case PEER_TAB:
    peers[index].status = !peers[index].status;
    break;
  case SEED_TAB:
    seeds[index].status = !seeds[index].status;
    break;
  }
}

/******************* Peer functions ***********************************/
int add_peer(char ip[]) {
  silent_print("\t Checking if ip exist and is active..\n");
  int index = search_peer_by_ip(ip);
  if (index != PEER_NOT_FOUND) {
    if (check_silent_mode() == 0) {
      printf("\t Found peer active %i for %s\n", index, ip);
    }
    reset_peer(index);
    return index;
  }
  silent_print("\t Ip not found ! Adding a new peer..");
  sem_wait(&semaphores[ADD_PEER]);
  index = next_free_peer();
  change_status(PEER_TAB, index);
  sem_post(&semaphores[ADD_PEER]);
  if (check_silent_mode() == 0) {
    printf("  %i OK\n", index);
  }
  return index;
}

void add_port(int port, int index) {
  if (check_silent_mode() == 0) {
    printf("\t Adding port %i for peer %i..", port, index);
  }
  peers[index].port = port;
  silent_print("  OK\n");
}
void add_client_ip(char *ip, int index) { strcpy(peers[index].client_ip, ip); }
void add_files(int id, int index) {
  if (check_silent_mode() == 0) {
    printf("\t Adding file %i for peer %i..", id, index);
  }
  peers[index].files[peers[index].files_count++] = id;
  silent_print("  OK\n");
}
void add_leechs(int id, int index) {
  if (check_silent_mode() == 0) {
    printf("\t Adding leech %i for peer %i..", id, index);
  }
  peers[index].leechs[peers[index].leechs_count++] = id;
  silent_print("  OK\n");
}

int get_port(int index) { return peers[index].port; }
const char *get_client_ip(int index) { return peers[index].client_ip; }
void get_peer_file_list(int *seed_list, int index) {
  for (int i = 0; i < peers[index].files_count; i++) {
    seed_list[i] = i;
  }
}
int get_peer_file_count(int index) { return peers[index].files_count; }
/*********************************************************************/

/******************* Seed functions ***********************************/
int add_seed(char key[], int peer_id) {
  int index = search_seed_by_key(key);
  switch (index) {
  case SEED_NOT_FOUND:
    silent_print("\t Adding new seed..\n");
    sem_wait(&semaphores[ADD_SEED]);
    index = next_free_seed();
    if (index != NO_FREE_SPACE) {
      change_status(SEED_TAB, index);
      add_seed_owner(index, peer_id);
    }
    sem_post(&semaphores[ADD_SEED]);
    if (check_silent_mode() == 0) {
      printf("\t Seed %i successfly added !\n", index);
    }
    return index;
  default:
    if (seeds[index].owners_count < MAX) {
      seeds[index].owners[seeds[index].owners_count++] = peer_id;
      if (check_silent_mode() == 0) {
        printf("\t Seed %i existing, adding owner %i\n", index, peer_id);
      }
      return index;
    }
    silent_print("ERROR NO FREE SPACE IN SEED\n");
    return NO_FREE_SPACE;
  }
}
void add_filename(char name[], int index) {
  if (strcmp(name, seeds[index].filename) == 0) {
    return;
  }
  if (check_silent_mode() == 0) {
    printf("\t Adding filename %s to seed id %i..", name, index);
  }
  strcpy(seeds[index].filename, name);
  silent_print("  OK\n");
}
void add_seed_owner(int index, int peer_id) {
  if (check_silent_mode() == 0) {
    printf("\t Adding new owner id %i to seed id %i..", peer_id, index);
  }
  seeds[index].owners[seeds[index].owners_count++] = peer_id;
  silent_print("  OK\n");
}
void add_len(int len, int index) {
  if (len == seeds[index].len) {
    return;
  }
  if (check_silent_mode() == 0) {
    printf("\t Adding len %i to seed id %i..", len, index);
  }
  seeds[index].len = len;
  silent_print("  OK\n");
}
void add_piece_size(int size, int index) {
  if (size == seeds[index].piece_size) {
    return;
  }
  if (check_silent_mode() == 0) {
    printf("\t Adding piece_size %i to seed id %i..", size, index);
  }
  seeds[index].piece_size = size;
  silent_print("  OK\n");
}
void add_key(char key[], int index) {
  if (strcmp(key, seeds[index].key) == 0) {
    return;
  }
  if (check_silent_mode() == 0) {
    printf("\t Adding key %s to seed id %i..", key, index);
  }
  strcpy(seeds[index].key, key);
  silent_print("  OK\n");
}
int get_seed_length(int index) { return seeds[index].len; }
int get_seed_piecesize(int index) { return seeds[index].piece_size; }
const char *get_seed_key(int index) { return seeds[index].key; }
const char *get_seed_filename(int index) { return seeds[index].filename; }
const int *get_seed_owner_list(int index) { return seeds[index].owners; }
int get_seed_owner_count(int index) { return seeds[index].owners_count; }

void get_global_seed_list(int *seed_list, int *seed_count) {
  int cpt = 0;
  for (int index = 0; index < MAX; index++) {
    if (seeds[index].status == FILLED && seeds[index].owners_count > 0) {
      seed_list[cpt++] = index;
    }
  }
  *seed_count = cpt;
}

/*********************************************************************/

void left_shift_seed_owners(int index, int begin) {
  int end = seeds[index].owners_count;
  for (int i = begin; i < end; i++) {
    seeds[index].owners[i] = seeds[index].owners[i + 1];
  }
}

int get_owner_id_by_peer_id(int index, int peer_id) {
  for (int i = 0; i < seeds[index].owners_count; i++) {
    if (seeds[index].owners[i] == peer_id) {
      return i;
    }
  }
  return OWNER_NOT_FOUND;
}

void reset_peer(int index) {
  if (check_silent_mode() == 0) {
    printf("\t Resetting peer id %d", index);
  }
  while (peers[index].files_count > EMPTY) {
    peers[index].files_count = peers[index].files_count - 1;
    int seed_index = peers[index].files[peers[index].files_count];
    if (seeds[seed_index].owners_count > 1) {
      int begin = get_owner_id_by_peer_id(seed_index, index);
      if (begin == OWNER_NOT_FOUND) {
        // TODO
      } else {
        left_shift_seed_owners(seed_index, begin);
        seeds[seed_index].owners_count--;
      }
    } else {
      change_status(SEED_TAB, seed_index);
      seeds[seed_index].owners_count = 0;
    }
  }
  peers[index].leechs_count = 0;
  silent_print("  OK\n");
}

void reset_update_peer(int index, int old_filecount) {
  peers[index].files_count -= old_filecount;
  if (check_silent_mode() == 0) {
    printf("\t Resetting peer id %d", index);
  }
  while (old_filecount > EMPTY) {
    old_filecount = old_filecount - 1;
    int seed_index = peers[index].files[old_filecount];
    if (seeds[seed_index].owners_count > 1) {
      int begin = get_owner_id_by_peer_id(seed_index, index);
      if (begin == OWNER_NOT_FOUND) {
        // TODO
      } else {
        left_shift_seed_owners(seed_index, begin);
        seeds[seed_index].owners_count--;
      }
    } else {
      change_status(SEED_TAB, seed_index);
      seeds[seed_index].owners_count = 0;
    }
  }
  peers[index].leechs_count = 0;
  silent_print("  OK\n");
}

void disconnect_peer(char ip[]) {
  int peer_id = search_peer_by_ip(ip);
  if (peer_id == PEER_NOT_FOUND) {
    if (check_silent_mode() == 0) {
      printf("\t Could not disconnect %s, ip not found in database\n", ip);
    }
    return;
  }
  if (check_silent_mode() == 0) {
    printf("\t Disconnecting peer id %i..\n", peer_id);
  }
  change_status(PEER_TAB, peer_id);
  reset_peer(peer_id);
}
