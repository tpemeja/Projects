#ifndef __TRACKER__H
#define __TRACKER__H
#include "data.h"
#include "parser.h"
#include "silent.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

/* structure essentielle aux threads du tracker */
struct thread_args {
  int socket_value;
  pthread_t thread;
  int status;
  int filled_status;
  int exit_status;
  char client_addr[INET_ADDRSTRLEN];
};
/* Différentes valeurs globales pour meilleure compréhension du code */
#define THREAD_NUMBER 5
#define FREE_STATUS 0
#define BUSY_STATUS 1
#define NO_THREAD_AVAILABLE -1
#define NO_SOCKET -1
#define EMPTY_THREAD 0
#define FILLED_THREAD 1
#define KEEP_THREAD 0
#define EXIT_THREAD 1

/* Pool de thread */
struct thread_args thread_pool[THREAD_NUMBER];

/* Fonction d'erreur */
void error(char *msg);
/* Fonction initiale de chaque thread */
void *thread_main(void *self);
/* Fonction permettant de récupérer l'id d'un thread libre dans le pool de
 * threads
 */
int free_thread_id();
/* Fonction d'instanciation du pool de thread */
void init_thread();

#endif
