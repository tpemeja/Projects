#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "board_generator.h"
#include "move.h"

#define MAX_WORD_LENGTH 3
// this programs reads the next word of an opened file
void r_file(FILE* file,char word[]){
  int i=0;
  char ch = fgetc(file); //gets the next character
  while(ch==' '||ch=='\n'){ //in case there is a comma, then a space
    ch = fgetc(file);
  }
  while(ch!=' '&&ch!='\n'&&ch!=EOF){
    word[i]= ch; //put the character in the string "word"
    i++;
    ch = fgetc(file);
  }
  for(int j=i;j<MAX_WORD_LENGTH;j++){
    word[j]=' ';
  }
}

int generate_move(FILE* text,struct move_t* moves){ //Moves est doit être de la taille max de coups possibles
  char word[MAX_WORD_LENGTH];
  r_file(text,word);
  printf("Value : %s\n",word);
  r_file(text,word);
  int length = atoi(word);
  struct move_t m;
  for(int i=0;i<length;i++){
    r_file(text,word);
    m.row=atoi(word);
    r_file(text,word);
    m.col=atoi(word);
    moves[i]=m;
  }
  return length;
}

void generate_moves(FILE* text,struct move_t* moves,int nb){
  int length;
  for(int i = 0; i<nb;i++){
    length = generate_move(text,moves);
    printf("--- %d ---\n",length);
    for(int i = 0; i < length ;i++){
      printf("%zd %zd\n",moves[i].row,moves[i].col);
    }
  }
}

void create_path(char* path,int taille,int i){
  char staille[10]="";
  char svalue[4]="";
  char sp[1]="_";
  char end_path[]=".txt";
  strcpy(path,"board_generated/board_generated_");
  sprintf(staille,"%d",taille);
  sprintf(svalue,"%d",i);
  strcat(path,staille);
  strcat(path,sp);
  strcat(path,end_path);
}

int main(){
  int taille = 10;
  int nb = 2;
  int min_value = -10;
  int max_value = 24;
  FILE* text;
  char path[100]="";
  struct move_t moves[NB_MAX];
  for(int i = min_value; i<max_value+1; i++){ //FORCEMENT DANS LE MAIN
    create_path(path,taille,i);
    printf("*** %s ****\n",path);
    text=fopen(path,"r"); // FORCEMENT DANS LE MAIN
    generate_moves(text,moves,nb);
  }
  return 0;
}
  
