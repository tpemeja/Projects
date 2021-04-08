# [Life Game](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) Optimization
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
We use 32x32 tiles which allow us to have the best optimization for parallelism. Indeed, when we distribute these tiles to the processors, they will have to load the data and a 32x32 tile performs a lot of calculations with few system calls to load the data.

### Thread speedup
To distribute the work to the different processors, we use ```#pragma omp for``` from **OpenMP** before the for-loops that perform the computations for the different tiles to generate threads and distribute them to the processors.

<p align="center">
  <img width="500" src=img/seq_vs_omp.PNG style="float:left;margin-left:-10px;">
</p>

As we can see on the figure above, **the speedup is not proportional to the number of threads**. Indeed, due to dependencies and the fact that not all processors run at the same speed, the global calculation can be slowed down compared to the theoretical value of processing these calculations in parallel.

### Parallelism scheduling 
The figure below shows the impact of the choice of scheduling on the speedup.
<p align="center">
  <img width="700" src=img/omp_vs_seq_vs_stat_dyna.PNG>
</p>

As we can see from the figure, **dynamic scheduling is less efficient than static scheduling**. 
Since the computation time is assumed to be the same for each element, dynamic scheduling will not have a better speed than static scheduling and will even need more time due to the higher number of cache miss.

## Computation vectorization
Using 256-bit vectors, we can vectorize 32 chars where each char corresponds to one element.
For each element, the necessary computation is divided into two parts:
* Identify the state of the element and its neighbors.
* Set the new state

### State identification of the neighbors
To compute all the states of the neighbors of a vector ```i```, we just load the three vectors ```i-1```, ```i``` and ```i+1```.
If we add them, we get a vector composed of the states of the 3 rows for each column. 
Adding this new vector with its left and right shift, we get the value of the states for the 30 elements in the middle of the vector.
By completing with the values for the ends, we obtain the neighbor state vector for the 32 elements.
The procedure is described in the following figure :
<p align="center">
  <img width="700" src=img/vectorization.png>
</p>

### New state calculation
The operation calculating the new state for an element also works for a vector. 
Therefore, the following operation using a vector calculates the new states for 32 elements at once:
```c
new_vector = (neighbor_state_vector == 3 + old_vector) | (neighbor_state_vector == 3)
```

## Lazy evaluation
A lazy version has been implemented. In this version, **the computation of an element will not be performed if it remains the same for the following iteration**.
To detect this, we put a boolean for each element to detect if the state has been changed. 
If all the states needed to evaluate the new state of an element (this includes the element itself and all its neighbors) have not changed in the previous iteration, then the element will not change and there is no point in performing the calculation.
The implementation of **this improvement really shows its performance with larger configurations with more work** as can be seen below.

<p align="center">
  <img width="700" src=img/comp.png>
</p>

*Note that the drop in performance observed after 24 threads is due to the switch from physical cores to virtual cores, given that the machine used for testing had 24 physical cores.*

## Conclusion
<p align="center">
  <img width="500" src=img/all_vs.PNG>
</p>

Based on all the improvements made, we were able to **speed up the calculations up to more than 150 times**. 
Notice that the decrease in performance for the lazy vectorized and parallelized version is due to the lack of calculations to be performed.
