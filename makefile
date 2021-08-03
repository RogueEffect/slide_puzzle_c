
DIR = src
CC = gcc
FLAGS = -g -Wall -std=c99
FILES = puzzle.c
EXE = puzzle

all:
	cd ${DIR} && $(CC) $(FLAGS) $(FILES) -o ../$(EXE)
