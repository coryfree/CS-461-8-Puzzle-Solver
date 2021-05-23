# CS-461-8-Puzzle-Solver

## Project Description

This program takes in a 3x3 grid of numbers 0-9, with 0 representing a blank square. Given this input, the program will determine whether or not the 8 Puzzle is able to be solved. If yes, the program will solve the puzzle and display the moves made to solve it.

## Project Explanation

An 8-puzzle is a 3x3 grid of tiles, numbered 1-8, with the last square in the grid being empty.  A tile can be slid into the blank spot, thus changing the configuration of the puzzle.  For example,
<pre>
2 4 7
1 3 
5 6 8
</pre>

Can become any of these:
<pre>
2 4 7              2 4                  2 4 7
1   3              1 3 7                1 3 8
5 6 8              5 6 8                5 6  
</pre>

The goal is to arrange the tiles in this order:
<pre>
1 2 3
4 5 6
7 8
</pre>
Given an arbitrary arrangement of tiles, can this goal state be reached? Not necessarily; half of all permutations are such that reaching the goal state is impossible.  (All states have either odd or even parity; no state with odd parity is reachable from any state with even parity, and vice-versa. The proof relies on a bit of number theory, not relevant here, and not essential for this program.)  Your task is to write a program that determines if the goal state can be reached, and if so, the series of moves (path) needed to reach it. 

## Technologies & Languages Used
Visual Studio 2017, C++
