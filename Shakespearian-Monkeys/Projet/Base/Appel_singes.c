#include "Singe_lecteur.h"
#include "Singe_imprimeur.h"
#include "Singe_statisticien.h"


void modif_etat(struct etat_singes* singes, struct file* file, int cpt){
  if(cpt==-1){
    singes->lecteur = 1;
  }
  if(file->debut==NULL){
    singes->statisticien = 0;
    singes->imprimeur = 0;
  }else{
    if(((file->fin)->vu==0)&&(file->debut!=NULL)){
      singes->statisticien = 1;
      singes->imprimeur = 0;
    }
    if(((file->fin)->vu==1)&&(file->debut!=NULL)){
      singes->statisticien = 0;
      singes->imprimeur = 1;
    }
  }
}

     


int appel_singes(struct etat_singes* singes,FILE* text,struct file* file,char* word,struct pool_mot* Pool_mot,struct file_cell* file_cell,struct pool* pool, int* nb_mot_impr){
  int nb;
  int choix_singe = 1;
  int cpt=0;
  while(choix_singe){
    nb = rand()%3+1;
    if((nb==1)&&(singes->lecteur)){
      cpt=singe_lecteur(text,file,word,Pool_mot);
      choix_singe = 0;    
    }
    if((nb==2)&&(singes->statisticien)){
      singe_statisticien(file_cell,file,pool);
      choix_singe = 0;    
    }
    if((nb==3)&&(singes->imprimeur)){
      singe_imprimeur(file,nb_mot_impr);
      choix_singe = 0;   
    } 
  }
  return cpt;
}
