#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "File.h"
#include "r_file.h"
#include "Singes_base.h"
#include "source.h"
#include "base.h"
int main(int argc,  char* argv[]) {
  struct file_cell file_cell = {NULL};
  base(argc,argv,&file_cell);
  //struct mot_successeur* mot = create_new_succ(&pool_succ,"bonjour",1);
  struct suivant suivant = {"je","suis"};
  //printf("%s\n",mot->mot);
  //printf("%d\n",mot->occ);
  printf("%s\n",suivant.mot);
  printf("%s\n",suivant.next);
  printf("%s\n",(file_cell.debut)->word);
  ajout_suivant(&pool_succ,&pool,&suivant);
  return 1;
}

