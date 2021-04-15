# Shakespearian Monkeys
Project realized in 2018 with Corentin Le Métayer

First project realized which explains the different problems of code, organization and architecture of the project.

[rapport.pdf](rapport.pdf) is a French report of this project describing more precisely the work done and explained below.
More information about the project is also available on [Shakespearian Monkeys](https://www.labri.fr/perso/renault/working/teaching/projets/2018-19-S5-ShakeMonkeys.php) (in French)

## Project description
This random text generator based on the [Infinite monkey theorem](https://en.wikipedia.org/wiki/Infinite_monkey_theorem) is divided into two main parts:
- [Base](Projet/Base) : Build a program using randomly one of the three functions that respectively ```Read the text word by word```, ```Update the number of occurrences of the word in the text```, ```Print the word```

- [achievement1](Projet/achievement1) : Upgrade of the **basic version**, now the second function will also ```list the following words``` of the word and count their occurrences. A new function is created that ```randomly generates a sentence``` based on the occurrence of the word and its following words.

## Commands :

- ```make``` : compile the basic version

- ```./project text_file.txt <-s seed_number>``` : Run the basic version on the ```test_file.txt``` file, we can specify a seed with ```-s seed_number``` to change the random selection of functions

The basic version prints the text and its statistics, such as the ```number of words```, ```number of different words```, ```highest and lowest occurrences```.

- ```make test``` : compute tests for the basic version


