#define MAX_CELLS 5000
#define MAX_WORD_LENGTH 20
#define MAX_MOTS 38000 

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "Singe_lecteur.h"

int main(int argc, char *argv[]){
  char word[MAX_WORD_LENGTH];
  int eof=1;//test eof. if eof=1 : not the end of the file, else, end of file (=0)
  FILE* text; //defines text as an external file (txt file here)
  text=fopen(argv[1],"r"); //opens the file as "read only"
  int cpt=0;
  struct file file = {}; //empty file
  while(eof){
    singe_lecteur(text,&file,&cpt,word,&Pool_mot,&eof);
    printf("word: %s\n",word);
  }
  printf("cpt : %d\n",cpt);
  printf("word sur file : %s\n",(file.debut)->word);
  printf("word sur file précédent : %s\n",((file.fin)->precedent)->word);
  int fclose(FILE* fd);
  return 0;
}
