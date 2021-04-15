// this programs reads the next word of an opened file. needs stdio.h and string.h

int r_file(FILE* file,char word[]){
  int i=0;
  char ch = fgetc(file); //gets the next character
  if (ch==EOF){ //if end of file reached
    //printf("end of the txt file\n");
    return 0;
  }
  while(((ch<'A')&&(ch>'z'))&&(ch!=39)&&(ch!=45)){ //in case there is a comma, then a space
    ch = fgetc(file);
  }
  while(((ch>='A')&&(ch<='z'))||(ch==39)||(ch==45)){
    
    word[i]= ch; //put the character in the string "word"
    i++;
    ch = fgetc(file);
  }
  word[i]=0;
  return 1; //end of file not reached
}
