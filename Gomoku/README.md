# [Gomoku](https://fr.wikipedia.org/wiki/Gomoku)
Project realized in 2019 with Emeric Duchemin, Laurent Genty, Julien Miens

## Project description
This project is divided into three main parts:
- Build a [bitboard](https://en.wikipedia.org/wiki/Bitboard) and all the operations needed to play Gomoku
- Implement a server making two players play the game
- Create players with different implementations and strategies

## Tree
- /src : source folder
  -  /src/players : contains all player code and their heuristic
  - /src/server : contains server and bitboard
  - /src/test : contains test files
- /Makefile
- /README.md
- /build_Debug : folder for development, created by command make
- /install : main installation folder, created by command make install
- /doc/doxygen/ : all doxygen generated documentation
- [Projet_s6_Gomoku.pdf](Projet_s6_Gomoku.pdf) : Project report (only in French)

## Pre-requesties :
- C compiler
- doxygen
- make
- [lib thread (on Windows)](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/rubenvb/gcc-4.7-experimental-stdthread/)

## Compilation :

- ```make``` : compile in *build_Debug* folder
- ```make install``` :  transfer all executable files to the *install* folder (call ```make``` if files are not created)

Each player may be compiled separately :
- ```make build_Debug/playerN.so``` : compile playerN

## Execution :

Go in *install* folder
```./server -n 10 -o playerA.so playerB.so```
where -n is used to give the size of the board
and -o pass the game in swap mode (with opening proposal)
Player B will play first

## Test :

- ```make test``` : compute global tests
- ```make test full=ON``` : compute results for all test

## Documentation :

- ```make doc``` : generate all doxygen documentation and run `doc/doxygen/index.html` on your browser to see it

Or run directly `doc/doxygen/html/index.html` after cloning the repository to see the documentation

## Cleaning :

- ```make clean``` : clean the repository
