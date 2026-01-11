#include <stdio.h>

#define SIZE 9

int isSafe(int grid[SIZE][SIZE], int row, int col, int num) {
    // Check row
    for (int x = 0; x < SIZE; x++)
        if (grid[row][x] == num)
            return 0;

    // Check column
    for (int x = 0; x < SIZE; x++)
        if (grid[x][col] == num)
            return 0;

    // Check 3x3 box
    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return 0;

    return 1;
}

int solveSudoku(int grid[SIZE][SIZE]) {
    int row, col;
    int emptyFound = 0;

    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            if (grid[row][col] == 0) {
                emptyFound = 1;
                goto EXIT;
            }
        }
    }
EXIT:
    if (!emptyFound)
        return 1;

    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            if (solveSudoku(grid))
                return 1;

            grid[row][col] = 0; // backtrack
        }
    }
    return 0;
}

void printGrid(int grid[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++)
            printf("%d ", grid[row][col]);
        printf("\n");
    }
}

int main() {
    int grid[SIZE][SIZE] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (solveSudoku(grid)) {
        printf("✅ Sudoku Solved Successfully:\n\n");
        printGrid(grid);
    } else {
        printf("❌ No solution exists.\n");
    }

    return 0;
}
