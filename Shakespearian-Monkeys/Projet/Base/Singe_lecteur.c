
#ifndef __STRUCT_FILE_H
#define __STRUCT_FILE_H 
#include "File.h"
#endif

//~~~~~~~~~~~~~~~~~~~~~singe lecteur~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*
this function uses a file (THE FILE NEEDS TO BE OPENED BEFORE), uses r_file to read a word from the txt file, then places this word on the "file". when the end of the file is reached,returns -1 and stops adding new words in the "file".Returns cpt in every case. there's also a counter for each word added in the "file".needs stdio.h,string.h,r_file.h,File.h
*/

// this programs reads the next word of an opened file. needs stdio.h and string.h
void r_file(FILE* file,char word[]){
  int i=0;
  int test=0; //to avoid this function to add a lot of 0 when there are many spaces
  char ch = fgetc(file); //gets the next character
  if (ch==EOF){ //if end of file reached
    //printf("end of the txt file\n");
    word=0;
  }
  while((ch<'A')&&(ch>'z')&&(ch!=39)&&(ch!=45)){ //in case there is a comma, then a space
    ch = fgetc(file);
    if (ch==EOF){ //if end of file reached
      //printf("end of the txt file\n");
      word=0;
    }
    test=0;
  }
  while(((ch>='A')&&(ch<='z'))||(ch==39)||(ch==45)){
    word[i]= ch; //put the character in the string "word"
    i++;
    ch = fgetc(file);
    test=1;
  }
  if (test==1){
    word[i]=0;
  }
}


int singe_lecteur(FILE* text,struct file *File,char* word,struct pool_mot* Pool_mot){
  int cpt=0;
  r_file(text,word); //r_file modifies AND replaces word. it returns 0 or 1, if this is the end of the file or not
  if (word != 0){
    struct mot* new_mot = create_new_mot(Pool_mot,word,(File->debut));
    ajout_file(new_mot,File);
    cpt++;
    return cpt;
  }
  cpt=-1;
  return cpt;
}

