#ifndef __STRUCT_FILE_H
#define __STRUCT_FILE_H 
#include "File.h"
#endif

// Supprime le dernier mot de la file et augmente le nombre de mot imprimé
void singe_imprimeur(struct file* file, int* nb_mot_impr){	
  supp_file(file);
  (*nb_mot_impr)++;
}
