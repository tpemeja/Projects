#include "silent.h"
static int silent_mode = 0;

void set_silent_mode() {
  printf("Silent mode is now activated !\n");
  silent_mode = 1;
}

int check_silent_mode() { return silent_mode; }

void silent_print(char *to_print) {
  if (silent_mode == 0) {
    printf("%s", to_print);
  }
}
