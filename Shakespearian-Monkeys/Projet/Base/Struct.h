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
struct file file = {NULL,NULL}; //empty file

struct file_cell {
  struct cell* debut;
};
struct file_cell file_cell = {NULL};

struct cell {
  char word[MAX_WORD_LENGTH+1];  // a char array for words of length MAX_WORD_LENGTH
  int  noccs;                    // an integer for counting occurrences
  struct cell* next;             // a (possibly NULL) pointer to the following cell
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

struct etat_singes{
  int lecteur;
  int statisticien;
  int imprimeur;
};
