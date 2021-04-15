#include "File.c"

//Créer un nouveau struct mot en utilisant l'espace mémoire de la pool
struct mot* create_new_mot(struct pool_mot *Pool_mot,char word[], struct mot* next);

struct cell* create_new_cell(struct pool *pool,char word[], int noccs,struct cell* next);

int file_vide(struct file* file); // Test si la file pointe sur une case vide

void ajout_file(struct mot* mot, struct file* file); //Ajoute un nouveau mot à la file et lie la cellule d'avant à celle-ci

void ajout_file_cell(struct pool* pool,struct cell* cell, struct file_cell* file_cell); //Ajoute une nouvelle cellule à la file et lie la cellule d'avant à celle-ci

//file ne dois pas être vide et déjà vu par le stat
void supp_file(struct file* file); //Supprime le dernier élément de la file et enlève le pointeur du dernier

void affich_file(struct file* file);
