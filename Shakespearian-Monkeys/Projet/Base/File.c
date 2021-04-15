//Créer un nouveau struct mot en utilisant l'espace mémoire de la pool
struct mot* create_new_mot(struct pool_mot *Pool_mot,char word[],struct mot* next) {
  if(Pool_mot->mot_libre - Pool_mot->mots >= MAX_MOTS)
    return NULL;
  struct mot* res = Pool_mot->mot_libre;
  strncpy(res->word, word, MAX_WORD_LENGTH+1); // Always take the null-terminator into account
  if (next!=NULL){ //Modifie le précédent du mot de la tête de la file si celle-ci n'est pas vide
    next->precedent = res; 
  }
  res->suivant = next; //Ajoute la tête de la liste en suivant du nouveau mot
  res->vu = 0; // 0 si le fichier n'a pas été vu par pour les stats
  res->precedent = NULL;
  Pool_mot->mot_libre++;
  return res;
}

struct cell* create_new_cell(struct pool *pool,char word[], int noccs,struct cell* next) {
  if(pool->next_free - pool->m >= MAX_CELLS)
    return NULL;
  struct cell* res = pool->next_free;
  strncpy(res->word, word, MAX_WORD_LENGTH+1); // Always take the null-terminator into account
  res->noccs = noccs;
  res->next = next;
  pool->next_free++;
  return res;
}
//////////////////////////////////////////////////////////////////
int file_vide(struct file* file){ // Test si la file pointe sur une case vide
  if (file->debut == NULL){
    return 1;
  }
  return 0;
}

void ajout_file(struct mot* mot, struct file* file){ //Ajoute un nouveau mot à la file et lie la cellule d'avant à celle-ci
    if (file_vide(file)){ //Le pointeur de fin de la file faut le mot si la file est vide
    file->debut = mot;
    file->fin = mot;
  }else{
    mot->suivant=file->debut;
    (file->debut)->precedent=mot;
    file->debut=mot;
  }
}

void ajout_file_cell(struct pool* pool,struct cell* cell, struct file_cell* file_cell){ //Ajoute une nouvelle cellule à la file et lie la cellule d'avant à celle-ci
  
  if (pool->m == NULL){
    file_cell->debut = cell;
  }else{
    struct cell* cell_fin = pool->m;
    while((cell_fin->next) != NULL){
      cell_fin++;
    }
    (cell_fin->next) = cell;
  }
}
//file ne dois pas être vide et déjà vu par le stat
void supp_file(struct file* file){ //Supprime le dernier élément de la file et enlève le pointeur du dernier
  if((file->debut)->suivant==NULL){
    (file->debut) = NULL;
    (file->fin) = NULL;
  }else{
    struct mot* mot = file->fin;
    file->fin=mot->precedent;
    (file->fin)->suivant=NULL; 
  }
}

void affich_file(struct file* file){
  struct mot* mot= file->debut;
  while(mot!=NULL){
    printf("%s\n",mot->word);
    mot=mot->suivant;
  }
  printf("\n");
}
