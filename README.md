Author          : Sunil Shankar Jaishankar
Created         : September 28, 2018
Last Modified   : September 28, 2018

Affiliation          : Georgia Institute of Technology


Description
-------------

These programs are solutions to the problem statements in Assignment 2 for CSE 6010. The first program (Graphgen/Assg2P1) takes in arguments such as number of grids in a 2D matrix, probability of a cell being colored and output file name. This program then generates a square grid of colored-uncolored cells which is then transformed into an adjacency list representation of a graph and printed as such in the output file. The second program reads the results from this output file, runs DFS on it to compute statistics regarding the number of components in the graph.


Installation: Program 1
------------------------

To install, run

    gcc Assignment2_Part1.c functions_part1.c -std=c99 -o Assg2P1

Note: The -std=c99 flag is required on some C compilers to allow variable declarations at arbitrary locations in a function.

Execution: Program 1
---------------------

Run executable using

    ./Assg2P1 10 0.4 topology

    Where 10 is number of columns/rows in the grid, 0.4 is the probability of a cell being colored and 'topology' is the name of the file that stores the output. One may change the values of 10, and 0.4 if needed.

    Installation: Program 2
------------------------

To install, run

    gcc Assignment2_Part2.c functions_part2.c -std=c99 -o Assg2P2

Note: The -std=c99 flag is required on some C compilers to allow variable declarations at arbitrary locations in a function.

Execution: Program 1
---------------------

Run executable using

    ./Assg2P2 topology outfile

    where topology is the name of the file output of the first program, and outfile is the name of the file that will hold the output of the current program 


