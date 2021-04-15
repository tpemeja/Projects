// Compte le nombre d'occurence du premier mot de la file et augmente son nombre d'occurence si il est présent dans la pool ou le rajoute sinon. Lorsque c'est fait modifie vu pour qu'on sache qu'il a été vu par le statisticien 


void singe_statisticien(struct pool_file_succ* pool_file_succ,struct pool_succ* pool_succ,struct file_cell* file_cell, struct file* file,struct pool* pool,struct suivant* suivant){
  int mot_present = 0;
  struct cell* deb = pool->m;
  if (deb != pool->next_free){
    while(deb != pool->next_free){
      char* mot1=(deb->word);
      char* mot2=(file->fin)->word;
      if(!strcmp(mot1,mot2)){
	(deb->noccs)+=1;
	mot_present=1;
      }
      deb++;
    }
  }
  if(!mot_present){
    struct cell* new_cell= create_new_cell(pool,(file->fin)->word,1,NULL,NULL);
    ajout_file_cell(pool,new_cell,file_cell);
  }
  if(suivant->mot==NULL){
    strcpy(suivant->mot,(file->fin)->word);
  }else{
    if(suivant->next==NULL){
      strcpy(suivant->next,(file->fin)->word);
    }else{
      ajout_suivant(pool_file_succ,pool_succ,pool,suivant);
      strcpy(suivant->mot,suivant->next);
      strcpy(suivant->next,(file->fin)->word);
    }
  }
  (file->fin)->vu=1;
  supp_file(file);
}
// Supprime le dernier mot de la file et augmente le nombre de mot imprimé

void singe_imprimeur(struct file* file_writer, int* nb_mot_impr){
  printf("%s ",(file_writer->fin)->word);
  supp_file(file_writer);
  (*nb_mot_impr)++;
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

//~~~~~~~~~~~~~~~~~~singe écrivain~~~~~~~~~~~~~~~~~~~
//nb_phrase représente le nombre de mots dans la phrase que l'écrivain a constitué
//motchoisi : mot choisi au hasard dans la liste des mots lus; si = NULL, c'est que la phrase était finie

void singe_ecrivain(struct file* File,struct pool *pool,struct pool_mot* Pool_writer,struct file* File_writer,int *cpt,int *nb_phrase,char* motchoisi){
    
  struct cell *cell = pool->m; // cellule qui contient les infos pour les mots

  if (*motchoisi == 0){
    int nb=rand()%(*cpt)+1; //nombre pour choisir un premier mot au hasard
    int compt=0;
    while ((compt+(cell->noccs))<nb){
      compt+=cell->noccs;
      cell++;
    }
    motchoisi=strcpy(motchoisi,cell->word);
    //printf("mot choisi : %s\n",motchoisi);
    struct mot* new_mot = create_new_mot(Pool_writer,motchoisi,(File_writer->debut));
    //printf("%s ",motchoisi);
    ajout_file(new_mot,File_writer);
    (*nb_phrase)++;
    struct cell* Cell = pool->m;
    while(strcmp(motchoisi,(Cell->word))){
      Cell++;
    }
  }
  else{
    /* struct cell* Cell = pool->m;
    while(strcmp(motchoisi,(Cell->word))){
      Cell++;
    }
  */
    struct cell* Cell = pool->m;
    int nb2=rand()%(Cell->noccs)+1; //nombre pour trouver le mot suivant au hasard
    int nb_ponct=rand()%5+1; // nombre pour un point de ponctuation au hasard.
    int nb_end=rand()%10+1; //nombre pour terminer une phrase au hasard.
    char* ponct="."; //chaine de caractère contenant la ponctuation (compatibilité avec create_new_mot)
    if (((cell->noccs) == 0)||(nb_end == 10)){
      if(*nb_phrase == 1){
	ponct="!";
	struct mot* new_mot = create_new_mot(Pool_writer,ponct,(File_writer->debut));
	ajout_file(new_mot,File_writer);
	//printf("ponct : %s\n",ponct);
        motchoisi=strcpy(motchoisi,"");
	*nb_phrase=0;
      }
      else{
	switch(nb_ponct){
	case 1:
	  ponct=".";
	  struct mot* new_mot = create_new_mot(Pool_writer,ponct,(File_writer->debut));
	  ajout_file(new_mot,File_writer);
	  motchoisi=strcpy(motchoisi,"");
	  *nb_phrase=0;
	  break;
	case 2:
	  ponct=",";
	  new_mot = create_new_mot(Pool_writer,ponct,(File_writer->debut));
	  ajout_file(new_mot,File_writer);
	  motchoisi=strcpy(motchoisi,"");
	  *nb_phrase=0;
	  break;
	case 3:
	  ponct=";";
	  new_mot = create_new_mot(Pool_writer,ponct,(File_writer->debut));
	  ajout_file(new_mot,File_writer);
	  motchoisi=strcpy(motchoisi,"");
	  *nb_phrase=0;
	  break;
	case 4:
	  ponct="?";
	  new_mot = create_new_mot(Pool_writer,ponct,(File_writer->debut));
	  ajout_file(new_mot,File_writer);
	  motchoisi=strcpy(motchoisi,"");
	  *nb_phrase=0;
	  break;
	case 5:
	  ponct=":";
	  new_mot = create_new_mot(Pool_writer,ponct,(File_writer->debut));
	  ajout_file(new_mot,File_writer);
	  motchoisi=strcpy(motchoisi,"");
	  *nb_phrase=0;
	  break;
	}
	//printf("%s ",ponct);
      }
    }
    else {
      int compt=0;
      struct cell* Cell = pool->m;
      while(strcmp(motchoisi,(Cell->word))){
	Cell++;
	}
      if ((Cell->file_successeur)!= NULL){
	struct mot_successeur* Successeur = (Cell->file_successeur)->successeur_deb;     
	while((compt+(Successeur->occ))<nb2){
	  compt+=(Successeur->occ);
	  Successeur=Successeur->prochain;
	}
	motchoisi=strcpy(motchoisi,Successeur->mot);
      }
      struct mot* new_mot = create_new_mot(Pool_writer,motchoisi,(File_writer->debut));
      ajout_file(new_mot,File_writer);
      (*nb_phrase)++;
      //printf("%s ",motchoisi);
    }
  }
}



struct etat_singes{
  int lecteur;
  int statisticien;
  int imprimeur;
  int ecrivain;
};

void modif_etat(struct etat_singes* singes,struct file* file_writer, struct file* file, int* eof,int *tour){
  if(*eof==0){
    singes->lecteur = 0;
  }
  if(file_vide(file_writer)){
    singes->imprimeur = 0;
  }else{
    singes->imprimeur = 1;
  }
  if(file_vide(file)){
    singes->statisticien = 0;
  }else{
    singes->statisticien = 1;
  }
  if (*tour == 101){
    singes->ecrivain = 1;
  }
}

     

void appel_singes(char *motchoisi,int *nb_phrase,struct file* file_writer,struct pool_mot* Pool_writer,struct pool_file_succ* pool_file_succ,struct pool_succ* pool_succ,struct etat_singes* singes,FILE* text,struct file* file,int* cpt,char* word,struct pool_mot* Pool_mot,int* eof,struct file_cell* file_cell,struct pool* pool, int* nb_mot_impr){
  int nb;
  int choix_singe = 1;
  while(choix_singe){
    nb = rand()%4+1;
    if((nb==1)&&(singes->lecteur)){
      singe_lecteur(text,file,cpt,word,Pool_mot,eof);
      choix_singe = 0;    
    }
    if((nb==2)&&(singes->statisticien)){
      singe_statisticien(pool_file_succ,pool_succ,file_cell,file,pool,&suivant);
      choix_singe = 0;    
    }
    if((nb==3)&&(singes->imprimeur)){
      singe_imprimeur(file_writer,nb_mot_impr);
      choix_singe = 0;   
    } 
    if((nb==4)&&(singes->ecrivain)){
      singe_ecrivain(file,pool,Pool_writer,file_writer,cpt,nb_phrase,motchoisi);
      choix_singe = 0;   
    }
  }
}
