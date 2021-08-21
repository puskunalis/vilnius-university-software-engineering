#ifndef SUDOKU_H
#define SUDOKU_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

void solveSudoku(uint8_t sudoku[][9]);

bool isCorrect(uint8_t sudoku[][9]);

void printSudoku(uint8_t sudoku[][9]);

#endif
