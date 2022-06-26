all: minesweeper

minesweeper: main.o minesweeper.o
	gcc -o minesweeper main.o minesweeper.o -lm

main.o: main.c
	gcc -c main.c

minesweeper.o: minesweeper.c minesweeper.h
	gcc -c minesweeper.c