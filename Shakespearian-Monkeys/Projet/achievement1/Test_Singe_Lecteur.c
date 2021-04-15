#include <stdio.h>
#include <string.h>
#include <time.h>
#include "File.h"
#include "r_file.h"
#include "Singe_tests.h"

int main(int argc, char *argv[]){
  char word[MAX_WORD_LENGTH];
  int eof=1;//test eof. if eof=1 : not the end of the file, else, end of file (=0)
  FILE* text; //defines text as an external file (txt file here)
  text=fopen(argv[1],"r"); //opens the file as "read only"
  int cpt=0;
  struct file file = {}; //empty file
  while(eof){
    singe_lecteur(text,&file,&cpt,word,&Pool_mot,&eof);
  }
  printf("%d\n",cpt);
  printf("%s\n",(file.debut)->word);
  //printf("%s\n",((file.fin)->precedent)->word);
  int fclose(FILE* fd);
  return 0;
}
