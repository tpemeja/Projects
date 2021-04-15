#define MAX_CELLS 5000
#define MAX_WORD_LENGTH 20
#define MAX_MOTS 38000 
#define MAX_SUCC 38000

struct suivant { //Créer un doublé contenant un mot et son successeur
  char mot[MAX_WORD_LENGTH+1];
  char next[MAX_WORD_LENGTH+1];
};

struct suivant suivant= { "","" }; // Initialisation

struct mot { //Mot = chaine de caractère + lien vers le suivant + déjà vu par le statisticien ou non
  char word[MAX_WORD_LENGTH+1];
  struct mot* precedent;
  struct mot* suivant;
  int vu;
};
//////////////////////////////////////////////////////////////////
struct file { // Créer une file qui contient la dernière cellule ajouté
  struct mot* debut;
  struct mot* fin;
};

struct file_cell {
  struct cell* debut;
};

struct mot_successeur{
  char mot[MAX_WORD_LENGTH+1];
  int occ;
  struct mot_successeur* prochain;
};

struct file_successeur {
  struct mot_successeur* successeur_deb;
};

struct cell {
  char word[MAX_WORD_LENGTH+1];  // a char array for words of length MAX_WORD_LENGTH
  int  noccs;                    // an integer for counting occurrences
  struct cell* next;             // a (possibly NULL) pointer to the following cell
  struct file_successeur* file_successeur;
};

//////////////////////////////////////////////////////////////////
struct pool {
  struct cell m[MAX_CELLS];      // an array of memory cells
  struct cell* next_free;        // a pointer to the first free cell
};
struct pool pool = { {}, pool.m }; // Trick to initialize the pool statically
//////////////////////////////////////////////////////////////////
// Créer un pool d'espace afin de créer des mots
struct pool_mot {
  struct mot mots[MAX_MOTS];
  struct mot* mot_libre;
};
//Initialise le pool
struct pool_mot Pool_mot = { {}, Pool_mot.mots };
////////////////////////////////////////////////////////////////
struct pool_file_succ {
  struct file_successeur file_succ[MAX_MOTS];
  struct file_successeur* next_free;
};
//Initialise le pool
struct pool_file_succ pool_file_succ = { {}, pool_file_succ.file_succ };
//Initialise le pool
struct pool_mot Pool_writer = { {}, Pool_writer.mots };
////////////////////////////////////////////////////////////////
//Créer un nouveau struct mot en utilisant l'espace mémoire de la pool
struct mot* create_new_mot(struct pool_mot *Pool_mot,
                             char word[],
                             struct mot* next) {
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

struct cell* create_new_cell(struct pool *pool,
                             char word[], int noccs,
                             struct cell* next,struct file_successeur* file_successeur) {
  if(pool->next_free - pool->m >= MAX_CELLS)
    return NULL;
  struct cell* res = pool->next_free;
  strncpy(res->word, word, MAX_WORD_LENGTH+1); // Always take the null-terminator into account
  res->noccs = noccs;
  res->next = next;
  pool->next_free++;
  res->file_successeur = file_successeur;
  return res;
}
struct pool_succ{
  struct mot_successeur successeur[MAX_SUCC];
  struct mot_successeur* next_free;
};
//Initialise le pool
struct pool_succ pool_succ = { {}, pool_succ.successeur }; 
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
  if (file_cell->debut == NULL){
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

struct mot_successeur* create_new_succ(struct pool_succ* pool_succ,char word[],int occ){
  if(pool_succ->next_free - pool_succ->successeur >= MAX_SUCC)
    return NULL;
  struct mot_successeur* res = pool_succ->next_free;
  strncpy(res->mot, word, MAX_WORD_LENGTH+1); // Always take the null-terminator into account
  res->occ = occ;
  res->prochain = NULL;
  pool_succ->next_free++;
  return res;
}   

void ajout_suivant(struct pool_file_succ* pool_file_succ,struct pool_succ * pool_succ,struct pool* pool, struct suivant* suivant){
  struct cell* cell = pool->m;
  struct file_successeur* file_succ = pool_file_succ->next_free;
  (pool_file_succ->next_free)+=1;
  
  while(strcmp((cell->word),(suivant->mot))){//recherche du mot dans la liste des cellules
    cell++;
  }
  int mot_present = 0;
  int mot_null = 0;
  if((cell->file_successeur)==NULL){
    struct mot_successeur* new_succ = create_new_succ(pool_succ,(suivant->next),1);
    (file_succ->successeur_deb) = new_succ;
    (cell->file_successeur)= file_succ ;
  }else{
    struct mot_successeur* mot = (cell->file_successeur)->successeur_deb;
    struct mot_successeur* mot_before = (cell->file_successeur)->successeur_deb;;
    if(mot==NULL){
      mot_null=1;
    }
    while(mot!=NULL){
      if(!strcmp((mot->mot),(suivant->next))){
	(mot->occ)+=1;
	mot_present=1;
      }
      mot_before=mot;
      mot=(mot->prochain);
    }
    if(!mot_present){
      struct mot_successeur* new_succ = create_new_succ(pool_succ,(suivant->next),1);
      if(mot_null){
	mot=new_succ;
      }else{
	(mot_before->prochain)=new_succ;
      }
    }
  }
}

void affich(struct pool* pool){
  struct cell* cell = pool->m;
  struct mot_successeur* mot_succ = (cell->file_successeur)->successeur_deb;
  int i = 0;
  int pas_fin=1;
  printf("---------------\n");
  while(pas_fin){
    i=cell->noccs;
    printf("%s\n",cell->word);
    if((cell->file_successeur)!=NULL){
      mot_succ = (cell->file_successeur)->successeur_deb;
      while(i!=0){
	printf("%s   ||  %d\n",mot_succ->mot,mot_succ->occ);
	i-=mot_succ->occ;
	mot_succ=mot_succ->prochain;
      }
      printf("---------------\n");
    }else{
      pas_fin=0;
      printf("---------------\n");
    }
    cell=cell->next;
  }
}
