# Solving 15 Puzzle via OpenMP

This project utilizes Breadth First Search algorithm and exploits the multithreaded functionality of OpenMP to solve
15-Puzzle problem. 

## OpenMP
OpenMP is an Application Programming Interface (API) that provides parallel programming support for multi-platform shared memory models.
Languages supported include: C,C++ and Fortran (https://en.wikipedia.org/wiki/OpenMP). It is very flexible, scalable and most importantly,
easier to use (compared to other alternatives like POSIX). 

## 15-Puzzle - Problem
https://en.wikipedia.org/wiki/15_puzzle

### Input
Input for 15-Puzzle is a 4x4 grid where each cell is either:

1. A number between 1-15 or 
2. A blank denoted as 0 

where blank (0) can only come once in the grid. An example input configuration is given below:
```
1  2  3  4
5  6  7  8
9  0  10 12
13 14 11 15
```
### Actions/Operators Allowed
Only blank can be moved/swapped with any of the four (max) neighbors around 0 as the allowed operators are:

- **Up**
- **Down**
- **Left**
- **Right**
  
### Goal Grid  
The goal state/grid to achieve is:
```
1  2  3  4
5  6  7  8
9  10 11 12
13 14 15 0
```  

### Output
After successful execution, the code writes the time taken, nodes explored and the nodes generated count on the console. A reference
excel file, to illustrate the speed up, is also uploaded ('Speedup.xlsx'). The difference in curve line of the graph is subtle
since the steps required (to solve) is small. However, it is clearly visible that 8 threads out-performs serial, 2 and 6 
threaded executions. 

### Note
The input file is 'input.txt' and num_threads can be changed to any desired value (in the pragma directive inside the code).
