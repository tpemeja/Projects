CFLAGS = -std=c99 -Wall

all: code

code: code-base

code-base: ./Projet/Base/base.c ./Projet/Base/File.h ./Projet/Base/r_file.h ./Projet/Base/Singes.h
	 gcc $(CFLAGS) ./Projet/Base/base.c -o project

test: test_singes

test_singes : ./Projet/Base/Test_Singe_imprimeur.c ./Projet/Base/Test_Singe_Lecteur.c ./Projet/Base/Test_Singe_Stat.c
	 gcc $(CFLAGS) ./Projet/Base/Test_Singe_Lecteur.c -o Test_Lecteur ; ./Test_Lecteur words.txt; 
	 gcc $(CFLAGS) ./Projet/Base/Test_Singe_imprimeur.c -o Test_imprimeur ; ./Test_imprimeur;
	 gcc $(CFLAGS) ./Projet/Base/Test_Singe_Stat.c -o Test_Stat ; ./Test_Stat words.txt;

clean : 
	 rm Test_Stat Test_imprimeur Test_Lecteur project 
