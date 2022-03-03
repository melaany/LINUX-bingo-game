# LINUX-bingo-game
Overall Idea:
This is a single/multiplayer bingo game called LINUX. A card of a 5x5 matrix of integers is generated for the user and the user will execute the program with a seed that cakks unique random numbers one at a time. If the number appears on the user card, it will be marked with an "m". If a row, column, or all four corners are marked, the user wins the game.

Files:

A2.c
User executes main function with a seed and CardFile (a readable file containing a Card) and calls unique random numbers one at a time using C's pseudo-random number generator (srand and rand). This program checks for winning conditions, and checks for exit status conditions which checks if the CardFile is readable and if the seed is incorrect.

list.c
This file contains the List ADT which implements a list of integer items and has functions ADD an item to list, CHECK if the items already in the list, PRINT list of call numbers, INITIALIZE the list, and FREE which deallocates the linked list items.  

list.h
This file contains the header of the List ADT.


A2MakeFile
Compiles the program using the "make -f A2Makefile". Consists of A2, A2.o, list.o, clean.



