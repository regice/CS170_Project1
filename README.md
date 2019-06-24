# The Eight-Puzzle

This is Project 1 for CS170, Introduction to Artificial Intelligence, taught at UCR by [Eamonn Keogh](https://www.cs.ucr.edu/~eamonn/) in Fall 2018. For the assignment, I was to write a program that solves the eight-puzzle via three algorithms, one of which is selected at runtime:
* Uniform Cost Search (also noted to be A\* but with h(n) hardcoded to equal zero),
* A\* with the Misplaced Tile heuristic, and
* A\* with the Manhattan Distance heuristic.

C++ was the programming language of choice for this project because I felt the most comfortable with it. MATLAB was also a strong contender, but I was more accustomed to using C++'s standard libraries for sequence containers (specifically, for double-ended queues). The source code can be found in `main.cpp`.
___________

# Compiling
To compile, run the command `g++ main.cpp`, which will create an executable called `a`. To run `a`, use the command `./a`.
