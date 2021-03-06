#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "File.h"
#include "r_file.h"
#include "Singes.h"
#include "source.h"

int main(int argc,  char* argv[]) {
  if(argc>=2){
    char word[MAX_WORD_LENGTH];
    FILE* text; //defines text as an external file (txt file here)
    if(strcmp(argv[1],"-s")){
      text=fopen(argv[1],"r");
      parse_opts(argc, argv);
    }else{
      text=fopen(argv[3],"r"); //opens the file as "read only"
      parse_opts(argc, argv);
    }
    int cpt=0;
    int eof=1;//test eof. if eof=1 : not the end of the file, else, end of file (=0)
    struct file file = {NULL,NULL}; //empty file
    struct file_cell file_cell = {NULL};
    int nb_mot_impr = 0;
    srand((unsigned)seed);
    //printf("Seed : %d\n", seed);
    struct etat_singes singes = {1,0,0};
    while(singes.lecteur || singes.statisticien || singes.imprimeur){
      appel_singes(&pool_file_succ,&pool_succ,&singes,text,&file,&cpt,word,&Pool_mot,&eof,&file_cell,&pool,&nb_mot_impr);
      modif_etat(&singes,&file,&eof);
    }
    struct cell* cell=pool.m;
    int nb_mot_diff = 0;
    int max = 0;
    int min = 0;
    if(cell!=pool.next_free){
      min = cell->noccs;
      max = cell->noccs;
      while(cell!=pool.next_free){
	if((cell->noccs)>max){
	  max=(cell->noccs);
	}
	if((cell->noccs)<min){
	  min=(cell->noccs);
	}
	cell++;
	nb_mot_diff++;
      }
    }    
    char motchoisi[MAX_WORD_LENGTH]="";
    printf("motchoisi: %s\n",motchoisi);
    int nb_phrase=0;
    struct file file_writer = {NULL,NULL}; //empty file
    singe_ecrivain(&file,&pool,&Pool_writer,&file_writer,&cpt,&nb_phrase,motchoisi);
    printf("nb_phrase: %d\n",nb_phrase);
    singe_ecrivain(&file,&pool,&Pool_writer,&file_writer,&cpt,&nb_phrase,motchoisi);
    printf("nb_phrase: %d\n",nb_phrase);
    singe_ecrivain(&file,&pool,&Pool_writer,&file_writer,&cpt,&nb_phrase,motchoisi);
    printf("nb_phrase: %d\n",nb_phrase);
    singe_ecrivain(&file,&pool,&Pool_writer,&file_writer,&cpt,&nb_phrase,motchoisi);
    printf("nb_phrase: %d\n",nb_phrase);
    singe_ecrivain(&file,&pool,&Pool_writer,&file_writer,&cpt,&nb_phrase,motchoisi);
    printf("nb_phrase: %d\n",nb_phrase);
    singe_ecrivain(&file,&pool,&Pool_writer,&file_writer,&cpt,&nb_phrase,motchoisi);
    printf("nb_phrase: %d\n",nb_phrase);
    singe_ecrivain(&file,&pool,&Pool_writer,&file_writer,&cpt,&nb_phrase,motchoisi);
    printf("nb_phrase: %d\n",nb_phrase);
    int fclose(FILE* fd);
  }
  return 0;
}
