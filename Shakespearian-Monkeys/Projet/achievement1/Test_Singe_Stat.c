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
  struct file_cell file_cell = {NULL};
  while(eof){
    singe_lecteur(text,&file,&cpt,word,&Pool_mot,&eof);
  }
  //struct mot* mot = (file.debut);
  while(file.fin!=NULL){
    //printf("%s\n",(file.fin)->word);
    //printf("%d\n",(file.fin)->vu);
    singe_statisticien(&file_cell,&file,&pool);
    // printf("%d\n",(file.fin)->vu);
    //printf("****\n");
    singe_imprimeur(&file);
  }
  struct cell* cell=pool.m;
  int n = 0;
  while((cell != pool.next_free)&&n<10){
    printf("%s %d\n",cell->word,cell->noccs);
    cell++;
    n++;
  }
  

    /*singe_statisticien(&file_cell,&file,&pool);
  singe_imprimeur(&file,&nb_impr);
  singe_statisticien(&file_cell,&file,&pool);
  singe_imprimeur(&file,&nb_impr);
  singe_statisticien(&file_cell,&file,&pool);
  //printf("%d\n",(file.debut)->vu);
  printf("%s\n",(file_cell.debut)->word);
  printf("%d\n",(file_cell.debut)->noccs);
  printf("%s\n",((file_cell.debut)->next)->word);
  printf("%d\n",((file_cell.debut)->next)->noccs);*/
  int fclose(FILE* fd);
  return 0;
}
