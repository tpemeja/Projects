/*un fichier source prenant en paramètre une graine aléatoire à l'ade de
  l'option -s */

#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "File.h"
#include "r_file.h"
#include "Singes.h"
#include "source.h"
////////////////////////////////////////////////////////////////
int main(int argc,  char* argv[]) {
  int nb_tour = 17000;
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
    int tour = 0;
    while((singes.lecteur || singes.statisticien || singes.imprimeur)&&tour<nb_tour){
      appel_singes(&singes,text,&file,&cpt,word,&Pool_mot,&eof,&file_cell,&pool,&nb_mot_impr);
      modif_etat(&singes,&file,&eof);
      tour++;
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
    printf("Nombre de mots lus :%d\n",cpt);
    printf("Nombre de mots imprimés :%d\n",nb_mot_impr);
    printf("Nombre de mots différents :%d\n",nb_mot_diff);
    printf("Plus grande multiplicité :%d\n",max);
    printf("Plus petite multiplicité :%d\n",min);
    int fclose(FILE* fd);
  }
  return 0;
}
