#include "Appel_singes.c"

void modif_etat(struct etat_singes* singes, struct file* file,int cpt);

int appel_singes(struct etat_singes* singes,FILE* text,struct file* file,char* word,struct pool_mot* Pool_mot,struct file_cell* file_cell,struct pool* pool, int* nb_mot_impr);