<h3 align="center">CSE 101 Fall 2023 PA4</h3>

## README.md
> This markdown file gives a general summary of all of the files made by Lia Cui.

## Makefile
> This make file is a script used to compile the c codes and check the executable file.

## Sparse.c
> This c file contains code to take in an input and output file for the program to take in Matrix information (ie. size, nnz, and entries) and print out various math equations involving the inputted matrices. The input and output file system base is from Patrick Tantalo's FileIO code.

## List.c
> This c file contains code that builds the List ADT in the form of a doubly linked list with a cursor element. The file contains constructor and destructor functions as well as various access and data manipulation functions.

## List.h
> This is the header file containing the functions from List.c.

## Matrix.c
> This c file contains code that builds the Matrix structure in the form of an adjacency list with defining features acknowledging the vertices, edges and arcs. The file contains constructor and destructor functions as well as various access and data manipulation functions. Vertex neighbors are discovered using a Breadth First Search method implemented as a function in this file.

## Matrix.h
> This is the header file containing the functions from Matrix.c.

## MatrixTest.c
> This c file contains code used to test the functionality of every function in the Matrix.c file. The test code and format base is from Patrick Tantalo's MatrixClient code.

## ListTest.c
> This c file contains code used to test the functionality of every function in the modified List.c file. The test code and format base is from Patrick Tantalo's ListClient code.
