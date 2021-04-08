# Optimization of the [Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life)
Project realized in 2020 with Maxime ROSAY

## Project description
The goal of this project is to optimize the game of life already implemented in [EasyPAP](https://gforgeron.gitlab.io/easypap/#documentation) and which can be seen in [life_vec.c](life_vec.c).
To achieve this optimization, we focus on two main parts:
- Use parralism to distribute computations with OpenMP
- Accelerate calculations with vectorization

## Parallelism of work
### Data tiling
The game is represented by a matrix where each element corresponds to a state. 
To know the new state of each element, we need its current value and the value of all its neighbors. So instead of distributing the computation of each element to the different processors, we tile the matrix with tiles that group the elements geographically. 
We use 32x32 tiles which allow us to have the best optimization for parallelism. Indeed, when we distribute these tiles to the processors, they will have to load the data and a 32x32 tile allows us to perform a lot of calculations with few system calls to load the data.

### Thread speedup
To distribute the work to the different processors, we use ``#pragma omp for`` from **OpenMP** before the for-loops that perform the computations for the different tiles, to generate threads and distribute them to the processors.

<p align="center">
  <img width="500" src=img/seq_vs_omp.PNG style="float:left;margin-left:-10px;">
</p>

As we can see on the figure above, the speedup is not proportional to the number of threads. Indeed, due to dependencies and the fact that not all processors run at the same speed, the global calculation can be slowed down compared to the theoretical value of processing these calculations in parallel.

### Parallelism scheduling 
The figure below shows the impact of the choice of scheduling on the speedup.
<p align="center">
  <img width="700" src=img/omp_vs_seq_vs_stat_dyna.PNG>
</p>
As we can see from the figure, dynamic scheduling is less efficient than static scheduling. 
Since the computation time is assumed to be the same for each element, dynamic scheduling will not have a better speed than static scheduling and will even need more time due to the higher number of cache miss.
