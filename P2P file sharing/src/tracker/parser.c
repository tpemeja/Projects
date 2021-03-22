#include "parser.h"
#include "data.h"

/* fonction d'erreur */

int request_error(int peer_id, char ip[]) {
  silent_print("ANNOUNCE ERROR \n");
  if (peer_id != NO_FREE_SPACE) {
    disconnect_peer(ip);
  }
  return REQUEST_ERROR;
}
/*
 * entrée : la string reçu sur le socket
 * sortie : le type de la requête
 */
int parser(char *buffer, char output[]) {
  buffer[strlen(buffer) - 1] = '\0';
  char *pch = strtok(buffer, " ");
  int ret = EMPTY;
  if (strcmp(pch, "announce") == 0) {
    // $piecesize1 $key1 ...] leech [$key2]
    // NB: output correspond à l'@ ip
    silent_print("ANNOUNCE\n");
    ret = parser_announce(buffer, output);
    if (ret != REQUEST_SUCCESS) {
      return REQUEST_ERROR;
    }
    return ANNOUNCE_REQUEST;
  } else if (strcmp(pch, "look") == 0) {
    // demander la liste des fichiers vérifiant les critères
    // look [$criterion1 ...]
    silent_print("LOOK\n");
    ret = parser_look(buffer, output);
    if (ret != REQUEST_SUCCESS) {
      return REQUEST_ERROR;
    }
    return LOOK_REQUEST;
  } else if (strcmp(pch, "getfile") == 0) {
    // demander les IP et ports des paires qui possèdent les fichiers keys
    // getfile $key
    silent_print("GETFILE\n");
    ret = parser_getfile(buffer, output);
    if (ret != REQUEST_SUCCESS) {
      return REQUEST_ERROR;
    }
    return GETFILE_REQUEST;
  } else if (strcmp(pch, "update") == 0) {
    // demander les IP et ports des paires qui possèdent les fichiers keys
    // getfile $key
    silent_print("UPDATE\n");
    ret = parser_update(buffer, output);
    if (ret != REQUEST_SUCCESS) {
      return REQUEST_ERROR;
    }
    return UPDATE_REQUEST;
  } else if (strcmp(pch, "quit") == 0) {
    silent_print("QUIT\n");
    ret = parser_quit(buffer, output);
    if (ret != REQUEST_SUCCESS) {
      return REQUEST_ERROR;
    }
    return QUIT_REQUEST;
  } else {
    // erreur
    silent_print("command not found\n");
    return REQUEST_ERROR;
  }
}
// announce listen $port seed [$filename1 $size1 $block_size1 $key1 ...] leech
// [$key2 ..]// envoie du message au parser :
// ...
int parser_announce(char *buffer, char ip[]) {
  char *pch;
  int mode = NO_MODE_SELECTED;
  int arg_cpt = 0;

  int seed_args = EMPTY;
  char seed_key[MAX];
  bzero(seed_key, MAX);
  char seed_filename[MAX];
  bzero(seed_filename, MAX);
  int seed_piecesize;
  int seed_length;
  int seed_id = NO_FREE_SPACE;

  int first_hook = 0;
  int last_hook = 0;

  char leech_key[MAX];
  bzero(leech_key, MAX);
  int leech_id = SEED_NOT_FOUND;

  int peer_id = NO_FREE_SPACE;
  int port = EMPTY;
  while ((pch = strtok(NULL, " ")) != NULL) {
    if (strcmp(pch, "listen") == 0) {
      if (arg_cpt != 0 || mode != NO_MODE_SELECTED) {
        // listen autre qu'en premier
        return request_error(peer_id, ip);
      }
      silent_print("LISTEN\n");
      arg_cpt++;
      mode = LISTEN;
    } else if (strcmp(pch, "seed") == 0) {
      if (arg_cpt != 1 || mode != NO_MODE_SELECTED) {
        // seed autre qu'en second
        return request_error(peer_id, ip);
      }
      silent_print("SEED\n");
      arg_cpt++;
      mode = SEED;
    } else if (strcmp(pch, "leech") == 0) {
      if (seed_args != EMPTY) {
        silent_print("bad request");
        return request_error(peer_id, ip);
      }
      if (arg_cpt != 2 || mode != NO_MODE_SELECTED) {
        // leech autre qu'en troisième
        return request_error(peer_id, ip);
      }
      silent_print("LEECH\n");
      arg_cpt++;
      mode = LEECH;
    } else {
      switch (mode) {
      case LISTEN:
        /* ajouter pch comme port puis repasser en erreur */
        peer_id = add_peer(ip);
        if (peer_id == NO_FREE_SPACE) {
          // TODO gestion d'erreur
          silent_print("DATABASE IS FULL \n");
          return request_error(peer_id, ip);
        } else {
          port = atoi(pch);
          add_port(port, peer_id);
          add_client_ip(ip, peer_id);
        }
        mode = NO_MODE_SELECTED;
        break;
      case SEED:
        // test d'intégrité
        if (strlen(pch) < 2 && (pch[0] == '[' || pch[0] == ']')) {
          return REQUEST_ERROR;
        }
        if (strcmp(pch, "[]") == 0) {
          mode = NO_MODE_SELECTED;
          break;
        }
        /* ajouter tout, on triera plus tard */
        peer_id = search_peer_by_ip(ip);
        if (peer_id == PEER_NOT_FOUND) {
          return request_error(peer_id, ip);
        }
        switch (seed_args++) {
        case FILENAME:
          if (pch[0] == '[') {
            first_hook++;
            strcpy(seed_filename, pch + 1);
            if (strlen(pch) < 2) {
              return request_error(peer_id, ip);
            }
          } else {
            strcpy(seed_filename, pch);
          }
          break;
        case LENGTH:
          seed_length = atoi(pch);
          break;
        case PIECESIZE:
          seed_piecesize = atoi(pch);
          break;
        case KEY:
          if (pch[strlen(pch) - 1] == ']') {
            last_hook++;
            strncpy(seed_key, pch, strlen(pch) - 1);
            seed_key[strlen(pch) - 1] = '\0';
            mode = NO_MODE_SELECTED;
          } else {
            strcpy(seed_key, pch);
          }
          if (first_hook > 1 || last_hook > 1) {
            silent_print("\t Too much [ or ] in seed command \n");
            return REQUEST_ERROR;
          }
          if (mode == NO_MODE_SELECTED && first_hook != 1 && last_hook != 1) {
            silent_print("\t Missing or too much [ or ] in seed command \n");
            return REQUEST_ERROR;
          }
          if (mode == NO_MODE_SELECTED) {
            first_hook = 0;
            last_hook = 0;
          }
          seed_id = add_seed(seed_key, peer_id);
          if (seed_id == NO_FREE_SPACE) {
            silent_print("DATABASE IS FULL \n");
            return request_error(peer_id, ip);
          }
          add_filename(seed_filename, seed_id);
          add_key(seed_key, seed_id);
          add_len(seed_length, seed_id);
          add_piece_size(seed_piecesize, seed_id);
          if (peer_id == NO_FREE_SPACE) {
            silent_print("bad request");
            return request_error(peer_id, ip);
          }
          add_files(seed_id, peer_id);
          seed_args = EMPTY;
          break;
        default:
          silent_print("bad request\n");
          return request_error(peer_id, ip);
        }
        break;
      case LEECH:
        // test d'intégrité
        if (strlen(pch) < 2 && (pch[0] == '[' || pch[0] == ']')) {
          return request_error(peer_id, ip);
        }
        if (strcmp(pch, "[]") == 0) {
          mode = NO_MODE_SELECTED;
          silent_print("\t Nothing to do\n");
          break;
        }
        /* ajouter pch comme clé pour leech */
        if (pch[0] == '[') {
          first_hook++;
          if (pch[strlen(pch) - 1] == ']') {
            last_hook++;
            strncpy(leech_key, pch + 1, strlen(pch) - 2);
            mode = NO_MODE_SELECTED;
          } else {
            strcpy(leech_key, pch + 1);
          }
        } else if (pch[strlen(pch) - 1] == ']') {
          last_hook++;
          strncpy(leech_key, pch, strlen(pch) - 1);
          mode = NO_MODE_SELECTED;
        } else {
          strcpy(leech_key, pch);
        }
        if (first_hook > 1 || last_hook > 1) {
          silent_print("\t Too much [ or ] in leech command \n");
          return REQUEST_ERROR;
        }
        if (mode == NO_MODE_SELECTED && first_hook != 1 && last_hook != 1) {
          silent_print("\t Missing or too much [ or ] in leech command \n");
          return REQUEST_ERROR;
        }
        if (mode == NO_MODE_SELECTED) {
          first_hook = 0;
          last_hook = 0;
        }
        leech_id = search_seed_by_key(leech_key);
        if (leech_id == SEED_NOT_FOUND) {
          if (check_silent_mode() == 0) {
            printf("\t Seed %s not found \n", leech_key);
          }
          // on part du principe que la seed existe dans la BDD
          // sinon, on pourrait en créer une sans owner
          return request_error(peer_id, ip);
        }
        add_leechs(leech_id, peer_id);
        break;
      default:
        // erreur !
        break;
      }
    }
  }
  if (arg_cpt == 3 && mode == NO_MODE_SELECTED) {
    return REQUEST_SUCCESS;
  }
  if (check_silent_mode() == 0) {
    printf("end %d\n", arg_cpt);
  }
  return request_error(peer_id, ip);
}

// < look [filename=”file_a.dat” filesize>”1048576”]
// > list [file_a.dat 2097152 1024 8905e92afeb80fc7722ec89eb0bf0966]

int parser_look(char *buffer, char output[]) {
  bzero(output, MAX);
  char *pch;
  char criterion[MAX];
  bzero(criterion, MAX);

  char filename[MAX];
  bzero(filename, MAX);
  int filename_id_list[MAX];
  bzero(filename_id_list, MAX);
  int filename_id_count = 0;

  int first_hook = 0;
  int last_hook = 0;

  char ip[MAX];
  bzero(ip, MAX);
  char tmp_filesize[MAX];
  bzero(tmp_filesize, MAX);
  int filesize_sup = -1;
  int filesize_eq = -1;
  int filesize_inf = -1;

  int filename_flag = 0;
  int ip_flag = 0;
  int filesize_sup_flag = 0;
  int filesize_eq_flag = 0;
  int filesize_inf_flag = 0;

  while ((pch = strtok(NULL, " ")) != NULL) {
    // Filtrage des [ ]
    silent_print("\t Parsing command... \n");
    if (pch[0] == '[') {
      first_hook++;
      if (pch[strlen(pch) - 1] == ']') {
        last_hook++;
        strncpy(criterion, pch + 1, strlen(pch) - 2);
      } else {
        strcpy(criterion, pch + 1);
      }
    } else if (pch[strlen(pch) - 1] == ']') {
      last_hook++;
      strncpy(criterion, pch, strlen(pch) - 1);
    } else {
      strcpy(criterion, pch);
    }
    if (first_hook > 1 || last_hook > 1) {
      silent_print("\t Too much [ or ] in command \n");
      return REQUEST_ERROR;
    }
    /* Gestion des différents critères */
    if (strncmp(criterion, "filename=", 9) == 0 && filename_flag == 0) {
      filename_flag++;
      int len = strlen(criterion);
      if (criterion[9] == '"' && criterion[len - 1] == '"') {
        strncpy(filename, criterion + 10, len - 11);
        silent_print("\t Filename criterion activated !\n");
      } else {
        silent_print("\t Missing quotation marks in filename criterion\n");
        return REQUEST_ERROR;
      }
    } else if (strncmp(criterion, "filesize>", 9) == 0 &&
               filesize_sup_flag == 0) {
      filesize_sup_flag++;
      bzero(tmp_filesize, MAX);
      int len = strlen(criterion);

      if (criterion[9] == '"' && criterion[len - 1] == '"') {
        strncpy(tmp_filesize, criterion + 10, len - 11);
        filesize_sup = atoi(tmp_filesize);
        silent_print("\t filesize> criterion activated !\n");
      } else {
        silent_print("\t Missing quotation marks in filesize> criterion\n");
        return REQUEST_ERROR;
      }
    } else if (strncmp(criterion, "filesize=", 9) == 0 &&
               filesize_eq_flag == 0) {
      filesize_eq_flag++;
      bzero(tmp_filesize, MAX);
      int len = strlen(criterion);

      if (criterion[9] == '"' && criterion[len - 1] == '"') {
        strncpy(tmp_filesize, criterion + 10, len - 11);
        filesize_eq = atoi(tmp_filesize);
        silent_print("\t Filesize= criterion activated !\n");
      } else {
        silent_print("\t Missing quotation marks in filesize= criterion\n");
        return REQUEST_ERROR;
      }
    } else if (strncmp(criterion, "filesize<", 9) == 0 &&
               filesize_inf_flag == 0) {
      filesize_inf_flag++;
      bzero(tmp_filesize, MAX);
      int len = strlen(criterion);

      if (criterion[9] == '"' && criterion[len - 1] == '"') {
        strncpy(tmp_filesize, criterion + 10, len - 11);
        filesize_inf = atoi(tmp_filesize);
        silent_print("\t Filesize< criterion activated !\n");
      } else {
        silent_print("\t Missing quotation marks in filesize< criterion\n");
        return REQUEST_ERROR;
      }
    } else if (strncmp(criterion, "peerip=", 7) == 0 && ip_flag == 0) {
      ip_flag++;
      int len = strlen(criterion);
      if (criterion[7] == '"' && criterion[len - 1] == '"') {
        strncpy(ip, criterion + 8, len - 9);
        silent_print("\t Peerip criterion activated !\n");
      } else {
        silent_print("\t Missing quotation marks in peerip criterion\n");
        return REQUEST_ERROR;
      }
    } else {
      silent_print("\t Criterion not found\n");
      return REQUEST_ERROR;
    }
  }
  if (first_hook != 1 || last_hook != 1) {
    silent_print("\t Missing or too much [ or ] in command \n");
    return REQUEST_ERROR;
  }
  /* préparation de l'output */
  silent_print("\t Filtering output... ");
  int peer_id = PEER_NOT_FOUND;
  int seed_list[MAX];
  int seed_count = 0;
  if (ip_flag) {
    peer_id = search_peer_by_ip(ip);
    if (peer_id == PEER_NOT_FOUND) {
      silent_print("ERROR\n");
      if (check_silent_mode() == 0) {
        printf("\t Peer with ip %s not found !\n", ip);
      }
      return REQUEST_ERROR;
    }
    get_peer_file_list(seed_list, peer_id);
    seed_count = get_peer_file_count(peer_id);

  } else {
    get_global_seed_list(seed_list, &seed_count);
  }
  for (int i = 0; i < seed_count; i++) {
    int seed_tmp = seed_list[i];
    int flag_tmp = 1;
    if (filename_flag && strcmp(filename, get_seed_filename(seed_tmp)) != 0) {
      flag_tmp = 0;
    }
    int file_length = get_seed_length(seed_tmp);
    if (filesize_sup_flag && (file_length <= filesize_sup)) {
      flag_tmp = 0;
    }
    if (filesize_eq_flag && (file_length != filesize_eq)) {
      flag_tmp = 0;
    }
    if (filesize_inf_flag && (file_length >= filesize_inf)) {
      flag_tmp = 0;
    }
    if (flag_tmp) {
      filename_id_list[filename_id_count++] = seed_list[i];
    }
  }
  silent_print(" OK\n\t Testing if output has at least one file... ");
  if (filename_id_count == 0) {
    strcat(output, "list []");
    return REQUEST_SUCCESS;
  }
  /* Construction de l'output */
  silent_print("OK\n\t Preparing output... ");
  strcat(output, "list [");
  char tmp_buf[MAX];
  bzero(tmp_buf, MAX);
  for (int i = 0; i < filename_id_count; i++) {
    int index = filename_id_list[i];
    strcat(output, get_seed_filename(index));
    strcat(output, " ");
    sprintf(tmp_buf, "%d %d ", get_seed_length(index),
            get_seed_piecesize(index));
    strcat(output, tmp_buf);
    bzero(tmp_buf, MAX);
    strcat(output, get_seed_key(index));
    if (i < filename_id_count - 1) {
      strcat(output, " ");
    } else {
      strcat(output, "]\n");
    }
  }
  silent_print("OK\n");

  return REQUEST_SUCCESS;
}

// getfile $key
// Attention a la taille du buffer d'output fixé à MAX !
int parser_getfile(char *buffer, char output[]) {
  char *pch = strtok(NULL, " ");
  if (pch == NULL) {
    silent_print("GETFILE ERROR \n");
    return REQUEST_ERROR;
  }
  pch[strlen(pch)] = '\0';
  if (check_silent_mode() == 0) {
    printf("\t Searching seed with key %s..\n", pch);
  }
  int seed_id = search_seed_by_key(pch);
  if (seed_id == SEED_NOT_FOUND) {
    silent_print("\t Seed not found \t ERROR\n");
    return REQUEST_ERROR;
  }
  if (check_silent_mode() == 0) {
    printf("\t Seed %d found ! Now searching peers..\n", seed_id);
  }

  strcpy(output, "peers \0");
  strcat(output, pch);
  strcat(output, " [");
  const int *owner_list = get_seed_owner_list(seed_id);
  int owner_count = get_seed_owner_count(seed_id);

  char port[MAX];
  if (check_silent_mode() == 0) {
    printf("\t Found %i peers\n", owner_count);
  }
  for (int i = 0; i < owner_count; i++) {
    if (strlen(output) >= (MAX - 5)) {
      printf("\t Too many owners \n");
      break;
    }
    strcat(output, get_client_ip(owner_list[i]));
    sprintf(port, ":%i", get_port(owner_list[i]));
    strcat(output, port);
    if (i != (owner_count - 1)) {
      strcat(output, " ");
    }
  }

  strcat(output, "]\n");
  return REQUEST_SUCCESS;
  /* transmettre le resultat */
}

// update seed [...] leech [...]
// semblable à announce
int parser_update(char *buffer, char ip[]) {
  char *pch;
  int mode = NO_MODE_SELECTED;
  int arg_cpt = 0;
  int peer_id = search_peer_by_ip(ip);

  int first_hook = 0;
  int last_hook = 0;

  if (peer_id == PEER_NOT_FOUND) {
    if (check_silent_mode() == 0) {
      printf("Peer not found for %s\n", ip);
    }
    return REQUEST_ERROR;
  }
  int old_filecount = get_peer_file_count(peer_id);
  printf("old filecount %d\n", old_filecount);
  char seed_key[MAX];
  bzero(seed_key, MAX);
  int seed_id = NO_FREE_SPACE;

  char leech_key[MAX];
  bzero(leech_key, MAX);
  int leech_id = SEED_NOT_FOUND;

  while ((pch = strtok(NULL, " ")) != NULL) {
    if (strcmp(pch, "seed") == 0) {
      if (arg_cpt != 0 || mode != NO_MODE_SELECTED) {
        // seed autre qu'en premier
        return REQUEST_ERROR;
      }
      silent_print("SEED\n");
      arg_cpt++;
      mode = SEED;
    } else if (strcmp(pch, "leech") == 0) {
      if (arg_cpt != 1 || mode != NO_MODE_SELECTED) {
        // leech autre qu'en second
        return REQUEST_ERROR;
      }
      reset_update_peer(peer_id, old_filecount);
      silent_print("LEECH\n");
      arg_cpt++;
      mode = LEECH;
    } else {
      switch (mode) {
      case SEED:
        // test d'intégrité
        if (strlen(pch) < 2 && (pch[0] == '[' || pch[0] == ']')) {
          return request_error(peer_id, ip);
        }
        if (strcmp(pch, "[]") == 0) {
          mode = NO_MODE_SELECTED;
          break;
        }
        // parse la liste
        if (pch[0] == '[') {
          first_hook++;
          if (pch[strlen(pch) - 1] == ']') {
            last_hook++;
            strncpy(seed_key, pch + 1, strlen(pch) - 2);
            mode = NO_MODE_SELECTED;
          } else {
            strcpy(seed_key, pch + 1);
          }
        } else if (pch[strlen(pch) - 1] == ']') {
          last_hook++;
          strncpy(seed_key, pch, strlen(pch) - 1);
          mode = NO_MODE_SELECTED;
        } else {
          strcpy(seed_key, pch);
        }
        if (first_hook > 1 || last_hook > 1) {
          silent_print("\t Too much [ or ] in seed command \n");
          return REQUEST_ERROR;
        }
        if (mode == NO_MODE_SELECTED && first_hook != 1 && last_hook != 1) {
          silent_print("\t Missing or too much [ or ] in seed command \n");
          return REQUEST_ERROR;
        }
        if (mode == NO_MODE_SELECTED) {
          first_hook = 0;
          last_hook = 0;
        }
        seed_id = search_seed_by_key(seed_key);
        if (seed_id == SEED_NOT_FOUND) {
          if (check_silent_mode() == 0) {
            printf("\t Seed %s not found !\n", seed_key);
          }
          return REQUEST_ERROR;
        }
        add_files(seed_id, peer_id);
        add_seed_owner(seed_id, peer_id);
        break;
      case LEECH:
        // test d'intégrité
        if (strcmp(pch, "[]") == 0) {
          mode = NO_MODE_SELECTED;
          break;
        }
        /* ajouter pch comme clé pour leech */
        if (pch[0] == '[') {
          first_hook++;
          if (pch[strlen(pch) - 1] == ']') {
            last_hook++;
            strncpy(leech_key, pch + 1, strlen(pch) - 2);
            mode = NO_MODE_SELECTED;
          } else {
            strcpy(leech_key, pch + 1);
          }
        } else if (pch[strlen(pch) - 1] == ']') {
          last_hook++;
          strncpy(leech_key, pch, strlen(pch) - 1);
          mode = NO_MODE_SELECTED;
        } else {
          strcpy(leech_key, pch);
        }
        if (first_hook > 1 || last_hook > 1) {
          silent_print("\t Too much [ or ] in leech command \n");
          return REQUEST_ERROR;
        }
        if (mode == NO_MODE_SELECTED && first_hook != 1 && last_hook != 1) {
          silent_print("\t Missing or too much [ or ] in leech command \n");
          return REQUEST_ERROR;
        }
        if (mode == NO_MODE_SELECTED) {
          first_hook = 0;
          last_hook = 0;
        }
        leech_id = search_seed_by_key(leech_key);
        if (leech_id == SEED_NOT_FOUND) {
          if (check_silent_mode() == 0) {
            printf("\t Seed %s not found \n", leech_key);
          }
          // on part du principe que la seed existe dans la BDD
          // sinon, on pourrait en créer une sans owner
          return REQUEST_ERROR;
        }
        add_leechs(leech_id, peer_id);
        mode = NO_MODE_SELECTED;
        break;
      default:
        // erreur !
        break;
      }
    }
  }
  if (arg_cpt == 2 && mode == NO_MODE_SELECTED) {
    return REQUEST_SUCCESS;
  }
  return REQUEST_ERROR;
}

int parser_quit(char *buffer, char output[]) {
  disconnect_peer(output);
  return REQUEST_SUCCESS;
}
