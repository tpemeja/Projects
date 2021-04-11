# Custom thread library
Project realized in 2020 with Sonia OUEDRAOGO, Julien MIRANDE.

[Projet_OS.pdf.pdf](Projet_OS.pdf.pdf) is a French report of this project, describing more precisely the work done and explained below.

## Project description
In this project, we designed our own thread library called **thread** in [thread.c](https://github.com/tpemeja/Projects/blob/main/Thread%20support%20library/src/thread/thread.c) which reproduces the behavior of [pthread](https://pubs.opengroup.org/onlinepubs/7908799/xsh/pthread.h.html).

The project was divided into two parts:
- Implementation and optimization of the basic functions of the pthread library
  - ```thread_self```, ```thread_create```, ```thread_yield```, ```thread_join```, ```thread_exit```
- Support for more complex concepts such as **Preemption**, **Mutex**, **Priority**

## Pre-requesties :
- C compiler
- make
- pthread
- valgrind

## Mode
The library supports different behaviors for threads. The behavior in the Makefile command can be selected by specifying the mode.
The different modes available are as follows:
- **default behavior** : our thread library
- **-pthread** : pthread library
- **-premp** : thread library with preemption
- **-head** : thread library with thread insertion from the head of the queue

##  Test
- ```make check``` :  compile and run all tests with the thread library and pthread

- ```make pthreads``` :  compile and run all tests with the pthread library only

- ```make [Test name] [MODE1=] [MODE2=-pthread]``` :  compile and run the test with the chosen modes

By default, the modes are defined on the thread and pthread libraries. If ``MODE1`` = ``MODE2``, the test will be run only on the selected mode.

##  Valgrind test
- ```make check``` : compile and run all tests using valgrind with the thread library and pthread

For each test, the result is stored in ```./install/bin/Test_name-valgrind.txt``` and only **SUCCESS** or **FAILURE** are displayed indicating if all memory has been freed and if there is no memory error.

- ```make [Test name]-valgrind [MODE1=]``` : compile and run the test using valgrind with the selected mode

By default, the mode is defined on the thread library. And the result is stored and displayed in the same way using **SUCCES** or **FAILURE**.

##  Graph
- ```make graphs``` : compile and create graphs for all tests using the thread and pthread libraries

- ```make [Test name]-graph [MODE1=-pthread] [MODE2=] [MODE3=] [MODE4=]``` : compile and create a test graph for a range of modes from 1 to 4
- 
By default, the modes are defined on the thread and pthread libraries. If two modes are identical then the mode will only appear once in the graph.
