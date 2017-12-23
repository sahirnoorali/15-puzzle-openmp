# Solving 15 Puzzle via OpenMP

This project utilizes Breadth First Search algorithm and exploits the multithreaded functionality of OpenMP to solve
15-Puzzle problem. (https://en.wikipedia.org/wiki/15_puzzle)

Input for 15-Puzzle is a 4x4 grid where each cell is either a number between 1-15 or a blank which is denoted as 0 in the code.
Blank (0) can only come once in the grid and it can be moved/swapped with any of the four (max) neighbors around 0 as the allowed operators are:

- Up
- Down
- Left
- Right
  
And the goal state/grid to achieve is:

1 2 3 4

5 6 7 8

9 10 11 12

13 14 15 0
  
After successful execution, the code writes the time taken, nodes explored and the nodes generated count on the console. A reference
excel file, to illustrate the speed up, is also uploaded ('Speedup.xlsx'). The difference in curve line of the graph is subtle
since the steps required (to solve) is small. However, it is clearly visible that 8 threads out-performs serial, 2 and 6 
threaded executions. 

The input file is 'input.txt' and num_threads can be changed to any desired value (in the pragma directive inside the code).
