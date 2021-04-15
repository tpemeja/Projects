#include "Singe_lecteur.c"

//~~~~~~~~~~~~~~~~~~~~~singe lecteur~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*
this function uses a file (THE FILE NEEDS TO BE OPENED BEFORE), uses r_file to read a word from the txt file, then places this word on the "file". when the end of the file is reached, "eof" is equal to 0 and stops adding new words in the "file". there's also a counter for each word added in the "file".needs stdio.h,string.h,r_file.h,File.h
*/


int singe_lecteur(FILE* text,struct file *File,char* word,struct pool_mot* Pool_mot);

// this programs reads the next word of an opened file. needs stdio.h and string.h
void r_file(FILE* file,char word[]);
