#define MAX_CELLS 5000
#define MAX_WORD_LENGTH 20
#define MAX_MOTS 38000 

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "Singe_imprimeur.h"

int main(int argc, char* argv[]){   
  //Create a file of 3 words
  int a=0;
  struct mot* mot1 = create_new_mot(&Pool_mot,"Word1",NULL);
  struct mot* mot2 = create_new_mot(&Pool_mot,"Word2",NULL);
  struct mot* mot3 = create_new_mot(&Pool_mot,"Word3",NULL);
  struct file file = {NULL,NULL};
  ajout_file(mot1,&file);
  affich_file(&file);
  ajout_file(mot2,&file);
  affich_file(&file);
  ajout_file(mot3,&file);
  affich_file(&file);
  //Delete words
  //printf("\n%s\n",(file.debut)->word);
  //printf("\n%s\n",((file.debut)->suivant)->word);
  // printf("\n%s\n",(((file.debut)->suivant)->suivant)->word);
  //printf("\n%s\n",((file.fin)->word));
  //printf("\n%s\n",(((file.fin)->precedent)->word));
  singe_imprimeur(&file,&a);
  affich_file(&file); 
  singe_imprimeur(&file,&a); 
  affich_file(&file); 
  singe_imprimeur(&file,&a); 
  affich_file(&file); 
  return 0;
}
