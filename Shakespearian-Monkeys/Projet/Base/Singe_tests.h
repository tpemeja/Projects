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
// Supprime le dernier mot de la file et augmente le nombre de mot imprimé

void singe_imprimeur(struct file* file){	
  supp_file(file);
}

//~~~~~~~~~~~~~~~~~~~~~singe lecteur~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*
this function uses a file (THE FILE NEEDS TO BE OPENED BEFORE), uses r_file to read a word from the txt file, then places this word on the "file". when the end of the file is reached, "eof" is equal to 0 and stops adding new words in the "file". there's also a counter for each word added in the "file".needs stdio.h,string.h,r_file.h,File.h
*/


void singe_lecteur(FILE* text,struct file *File,int *cpt,char* word,struct pool_mot* Pool_mot,int *eof){
  *eof=r_file(text,word); //r_file modifies AND replaces word. it returns 0 or 1, if this is the end of the file or not
  if (*eof == 1){
    struct mot* new_mot = create_new_mot(Pool_mot,word,(File->debut));
    ajout_file(new_mot,File);
    (*cpt)++;
  }
}
