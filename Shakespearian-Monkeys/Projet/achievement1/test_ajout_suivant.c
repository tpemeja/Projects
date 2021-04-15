/*un fichier source prenant en paramètre une graine aléatoire à l'ade de
  l'option -s */

#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "File.h"
#include "r_file.h"
#include "Singes_base.h"
#include "source.h"
////////////////////////////////////////////////////////////////
int main(int argc,  char* argv[]) {
  int nb_tour = 100;
  struct file_cell file_cell = {NULL};
  struct file file = {NULL,NULL}; //empty file
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
  struct suivant suivant = {"from","fairest"};
  //printf("%s\n",mot->mot);
  //printf("%d\n",mot->occ);
  //printf("%s\n",suivant.mot);
  //printf("%s\n",suivant.next);
  ajout_suivant(&pool_file_succ,&pool_succ,&pool,&suivant);
  struct cell* cell = pool.m;
  printf("***************\n");
  printf("%d\n",cell->noccs);
  printf("%s\n",cell->word);
  //printf("3\n");
  printf("%s\n",((cell->file_successeur)->successeur_deb)->mot);
  //printf("3\n");
  printf("***************\n");
  struct suivant suivant2 = {"fairest","creatures"};
  //printf("1\n");
  cell=(cell->next);
  //printf("%s\n",cell->word);
  ajout_suivant(&pool_file_succ,&pool_succ,&pool,&suivant2);
  //printf("1\n");
  // printf("1\n");
  printf("%d\n",cell->noccs);
  printf("%s\n",cell->word);
  printf("%s\n",((cell->file_successeur)->successeur_deb)->mot);
  printf("***************\n");
  struct suivant suivant3 = {"creatures","from"};
  cell=(cell->next);
  //printf("%s\n",cell->word);
  ajout_suivant(&pool_file_succ,&pool_succ,&pool,&suivant3);
  //printf("1\n");
  // printf("1\n");
  printf("%d\n",cell->noccs);
  printf("%s\n",cell->word);
  printf("%s\n",((cell->file_successeur)->successeur_deb)->mot);
  printf("%d\n",(((pool.m)->file_successeur)->successeur_deb)->occ);
  printf("***************\n");
  struct suivant suivant4 = {"from","fairest"};
  cell=pool.m;
  //printf("%s\n",cell->word);
  ajout_suivant(&pool_file_succ,&pool_succ,&pool,&suivant4);
  //printf("1\n");
  // printf("1\n");
  //printf("14\n");
  //printf("%d\n",(((pool.m)->file_successeur)->successeur_deb)->occ);
  printf("%d\n",(pool.m)->noccs);
  printf("%s\n",cell->word);
  printf("%s\n",(((pool.m)->file_successeur)->successeur_deb)->mot);
  printf("%d\n",(((pool.m)->file_successeur)->successeur_deb)->occ);
  // printf("%s\n",((((pool.m)->file_successeur)->successeur_deb)->prochain)->mot);
  printf("***************\n");
  return 0;
}
