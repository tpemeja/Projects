#include "fakeclient.h"

void error(char *msg) {
  perror(msg);
  exit(1);
}

int main(int argc, char *argv[]) {
  int sockfd, portno, n;
  struct sockaddr_in serv_addr;
  struct hostent *server;

  char buffer[256];
  if (argc < 3) {
    printf("usage %s hostname port\n", argv[0]);
    return 1;
  }
  portno = atoi(argv[2]);
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    error("ERROR, opening socket\n");
  }
  server = gethostbyname(argv[1]);
  if (server == NULL) {
    error("ERROR, no such host\n");
  }
  bzero((char *)&serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,
        server->h_length);
  serv_addr.sin_port = htons(portno);

  if (connect(sockfd, (const struct sockaddr *)&serv_addr, sizeof(serv_addr)) <
      0) {
    error("ERROR, connecting\n");
  }
  int flag = 1;
  while (flag) {
    printf("enter the message: ");
    bzero(buffer, 255);
    fgets(buffer, 255, stdin);
    if (strcmp(buffer, "quit\n") == 0) {
      flag = 0;
      printf("Closing communication...\n");
    }
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0) {
      error("ERROR, writing in socket\n");
    }
    bzero(buffer, 255);
    n = read(sockfd, buffer, 255);
    if (n < 0) {
      error("ERROR, reading from socket\n");
    }
    printf("received: %s\n", buffer);
  }
  close(sockfd);
  return 0;
}
