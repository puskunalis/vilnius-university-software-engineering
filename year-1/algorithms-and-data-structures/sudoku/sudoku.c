#include "sudoku.h"

void solveSudoku(uint8_t sudoku[][9])
{
    if (!isCorrect(sudoku))
    {
        printf("Given sudoku is incorrect!\n");
        return;
    }

    for (uint8_t i = 0; i < 9; ++i)
    {
        for (uint8_t j = 0; j < 9; ++j)
        {
            if (sudoku[i][j] == 0)
            {
                for (uint8_t k = 1; k < 10; ++k)
                {
                    sudoku[i][j] = k;

                    if (isCorrect(sudoku))
                    {
                        solveSudoku(sudoku);
                    }
                    else
                    {
                        sudoku[i][j] = 0;
                    }
                }

                return;
            }
        }
    }

    printSudoku(sudoku);
}

bool isCorrect(uint8_t sudoku[][9])
{
    // Row
    for (uint8_t i = 0; i < 9; ++i)
    {
        uint8_t numbers[10] = {0};

        for (uint8_t j = 0; j < 9; ++j)
        {
            ++numbers[sudoku[i][j]];
        }

        for (uint8_t j = 1; j < 10; ++j)
        {
            if (numbers[j] > 1)
            {
                return false;
            }
        }
    }

    // Column
    for (uint8_t i = 0; i < 9; ++i)
    {
        uint8_t numbers[10] = {0};

        for (uint8_t j = 0; j < 9; ++j)
        {
            ++numbers[sudoku[j][i]];
        }

        for (uint8_t j = 1; j < 10; ++j)
        {
            if (numbers[j] > 1)
            {
                return false;
            }
        }
    }

    // 3x3 Grid
    for (uint8_t i = 0; i < 9; ++i)
    {
        uint8_t numbers[10] = {0};

        for (uint8_t j = 0; j < 9; ++j)
        {
            ++numbers[sudoku[(j % 9 + 9 * i) / 3 % 3 + (i / 3 * 3)][(j % 3 + 3 * i) % 9]];
        }

        for (uint8_t j = 1; j < 10; ++j)
        {
            if (numbers[j] > 1)
            {
                return false;
            }
        }
    }

    return true;
}

void printSudoku(uint8_t sudoku[][9])
{
    for (uint8_t i = 0; i < 9; ++i)
    {
        for (uint8_t j = 0; j < 9; ++j)
        {
            printf("%d ", sudoku[i][j]);
        }

        printf("\n");
    }

    printf("\n");
}
