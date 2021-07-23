
@echo off

set DIR=src\
set CC=gcc
set FLAGS=-g -Wall -std=c99
set FILES=puzzle.c
set EXE=puzzle.exe

( %CC% %FLAGS% %DIR%%FILES% -o %EXE% && echo Build complete ) || echo Build failed
