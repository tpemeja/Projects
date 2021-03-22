#include "tracker.h"

sem_t lock;

void error(char *msg) {
  perror(msg);
  exit(1);
}

void *thread_main(void *self) {
  struct thread_args *current = &thread_pool[(int)(size_t)self];

  char output[MAX * 10];
  int tmp;
  char buffer[MAX];
  bzero(buffer, MAX);

  while ((current->status == FREE_STATUS ||
          current->filled_status == EMPTY_THREAD) &&
         current->exit_status == KEEP_THREAD) {
    // attente d'une connexion
  }
  int socketfd = current->socket_value;
  // ajout adresse ip du client
  // lecture du message reçu
  int flag = 1; // flag à changer (pour des tests actuellement)
  while (flag && current->exit_status == KEEP_THREAD) {
    strcpy(output, current->client_addr);
    int n = read(socketfd, buffer, MAX - 1);
    if (n <= 4) {
      if (check_silent_mode() == 0) {
        printf("ERROR, reading from socket %s\n", current->client_addr);
      }
      write(socketfd, "nok\n", 4);
      flag = 0;
      break;
    } else {
      if (check_silent_mode() == 0) {
        printf("From %s: %s", current->client_addr, buffer);
      }
      sem_wait(&lock);
      tmp = parser(buffer, output);
      sem_post(&lock);
      switch (tmp) {
      case ANNOUNCE_REQUEST:
        n = write(socketfd, "ok\n", 3);
        break;
      case LOOK_REQUEST:
        n = write(socketfd, output, strlen(output));
        break;
      case GETFILE_REQUEST:
        n = write(socketfd, output, strlen(output));
        break;
      case UPDATE_REQUEST:
        n = write(socketfd, "ok\n", 3);
        break;
      case REQUEST_ERROR:
        n = write(socketfd, "nok\n", 4);
        break;
      case QUIT_REQUEST:
        flag = 0;
        n = write(socketfd, "Good bye!\n", 10);
        break;
      default:
        // cas impossible normalement, par défaut une erreur
        n = write(socketfd, "nok\n", 4);
        break;
      }
      bzero(buffer, MAX);
      bzero(output, MAX);
    }
  }

  // fermer la socket
  if (close(socketfd) < 0) {
    error("ERROR, closing socket new\n");
  }
  if (check_silent_mode() == 0) {
    printf("Disconnected %s...\n", current->client_addr);
  }
  current->socket_value = NO_SOCKET;
  current->filled_status = EMPTY_THREAD;
  current->status = FREE_STATUS;

  if (current->exit_status == EXIT_THREAD) {
    pthread_exit(NULL);
  } else {
    thread_main(self);
  }
  return 0;
}

int free_thread_id() {
  for (int i = 0; i < THREAD_NUMBER; i++) {
    if (thread_pool[i].status == FREE_STATUS) {
      return i;
    }
  }
  return NO_THREAD_AVAILABLE;
}

void exit_threads() {
  for (int i = 0; i < THREAD_NUMBER; i++) {
    thread_pool[i].exit_status = EXIT_THREAD;
  }
}

void init_thread() {
  int fail_cpt = 0;
  sem_init(&lock, 0, 1);
  for (int i = 0; i < THREAD_NUMBER; i++) {
    thread_pool[i].status = FREE_STATUS;
    thread_pool[i].filled_status = EMPTY_THREAD;
    thread_pool[i].exit_status = KEEP_THREAD;
    thread_pool[i].socket_value = NO_SOCKET;
    if (pthread_create(&thread_pool[i].thread, NULL, thread_main,
                       (void *)(size_t)i) == -1) {
      fail_cpt++;
      error("ERROR, on thread creation");
    }
  }
  if (check_silent_mode() == 0) {
    printf("Successfully initialized %d/%d threads !\n",
           THREAD_NUMBER - fail_cpt, THREAD_NUMBER);
  }
}

void args_parser(int argc, char *argv[], int *portno) {
  int opt, v = 0;
  while ((opt = getopt(argc, argv, "vp:")) != -1) {
    switch (opt) {
    case 'v':
      printf("Silent mode is not activated !\n");
      v++;
      break;
    case 'p':
      printf("Selecting port number : %d\n", atoi(optarg));
      *portno = atoi(optarg);
      break;
    case '?':
      if (optopt == 'p') {
        printf("Usage [-p port_number]\n");
      } else {
        printf("Unknown option: -%c\n", optopt);
      }
      break;
    default:
      printf("Unknown option: -%c\n", optopt);
      break;
    }
  }
  if (v == 0) {
    set_silent_mode();
  }
}

int main(int argc, char *argv[]) {
  int sockfd, newsockfd, portno = 0;
  unsigned int clilen;
  char client_ip[INET_ADDRSTRLEN];
  struct sockaddr_in serv_addr, cli_addr;

  /* Parsing de la commande entrée */
  if (argc > 1) {
    args_parser(argc, argv, &portno);
  } else {
    set_silent_mode();
  }

  // créer une nouvelle socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    error("ERROR, opening socket\n");
  }
  // initialiser serv_addr
  bzero((char *)&serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  if (portno == 0) {
    portno = 25000;
    printf("No port number provided, tracker will run on default port %d\n",
           portno);
  }
  serv_addr.sin_port = htons(portno);

  // lier la socket à l'adresse
  while (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    // si le port par défaut utilisé on incrémente
    if (check_silent_mode() == 0) {
      printf("ERROR, port number %d already in use\n", portno);
    }
    portno++;
    serv_addr.sin_port = htons(portno);
    if (check_silent_mode() == 0) {
      printf("Trying with port number %d\n", portno);
    }
  }
  printf("Tracker successfully launched on port %d\n", portno);

  // marque la socket comme passive
  // i.e. la socket servira à accepter les demandes de connexions entrantes
  listen(sockfd, 2);
  clilen = sizeof(cli_addr);

  // initialisation des threads
  init_thread();
  // initialisation de la base de données
  init_pools();
  // boucle infinie
  // TODO : faire un cas de break, sinon on le coupe via ctrl+c et le code
  // avec les close ne sert à rien :)
  while (1) {
    // créer une nouvelle socket lors de la connexion
    // fonction bloquante
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    inet_ntop(AF_INET, &cli_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
    silent_print("CONNECTION\n");
    if (check_silent_mode() == 0) {
      printf("\t Accepted connection from %s...\n", client_ip);
    }
    if (newsockfd < 0) {
      error("ERROR, on accept\n");
    }
    int thread_id = free_thread_id();
    while (thread_id == NO_THREAD_AVAILABLE) {
      silent_print("\t No thread available, waiting ...\n");
      sleep(2); // définir un temps d'attente
      thread_id = free_thread_id();
    }
    if (check_silent_mode() == 0) {
      printf("\t %s is now connected on thread number %d...\n", client_ip,
             thread_id);
    }
    thread_pool[thread_id].status = BUSY_STATUS;
    thread_pool[thread_id].socket_value = newsockfd;
    inet_ntop(AF_INET, &cli_addr.sin_addr, thread_pool[thread_id].client_addr,
              INET_ADDRSTRLEN);
    ;
    thread_pool[thread_id].filled_status = FILLED_THREAD;
  }
  // free_thread();
  if (close(sockfd) < 0) {
    exit_threads();
    error("ERROR, closing socket server\n");
  }
  return 0;
}
