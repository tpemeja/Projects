
#ifndef __STRUCT_FILE_H
#define __STRUCT_FILE_H 
#include "File.h"
#endif

// Compte le nombre d'occurence du premier mot de la file et augmente son nombre d'occurence si il est présent dans la pool ou le rajoute sinon. Lorsque c'est fait modifie vu pour qu'on sache qu'il a été vu par le statisticien 

void singe_statisticien(struct file_cell* file_cell, struct file* file,struct pool* pool){
  int mot_present = 0;
  struct cell* deb = pool->m;
  if (deb != pool->next_free){
    while(deb != pool->next_free){
      char* mot1=(deb->word);
      char* mot2=(file->fin)->word;;
      if(!strcmp(mot1,mot2)){
	(deb->noccs)+=1;
	mot_present=1;
      }
      deb++;
    }
  }
  if(!mot_present){
    struct cell* new_cell= create_new_cell(pool,(file->fin)->word,1,NULL);
    ajout_file_cell(pool,new_cell,file_cell);
  }
  (file->fin)->vu=1;
}
