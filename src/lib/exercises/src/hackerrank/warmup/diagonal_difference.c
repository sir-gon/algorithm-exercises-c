#include <exercises/hackerrank/warmup/diagonal_difference.h>

/**
 * @link Problem definition [[docs/hackerrank/warmup/diagonal_difference.md]]
 */

#include <stdlib.h>

int HACKERRANK_WARMUP_diagonalDifference(int arr_rows, int arr_columns,
                                         int **arr) {
  int diag1 = 0;
  int diag2 = 0;
  int last = arr_rows - 1L;

  for (int i = 0; i < arr_rows; i++) {
    for (int j = 0; j < arr_columns; j++) {
      if (i == j) {
        diag1 += arr[i][j];
        diag2 += arr[last - i][j];
      }
    }
  }
  return abs(diag1 - diag2);
}
