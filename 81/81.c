#include <stdio.h>
#include <stdint.h>

#define N 80

int main(void)
{
  int i, j;
  uint32_t mat[N][N], row, col;

  for (i = 0; i < N; ++i) {
    for (j = 0; j < N; ++j) {
      scanf("%d", &mat[i][j]);
    }
  }

  for (i = 0; i < N; ++i) {
    for (j = 0; j < N; ++j) {
      if (i==0 && j==0) {
        continue;
      }
      col = (i != 0)?mat[i-1][j]:UINT32_MAX;
      row = (j != 0)?mat[i][j-1]:UINT32_MAX;
      mat[i][j] += ((row<col)?row:col);
    }
  }
  printf("%u\n", mat[N-1][N-1]);

  return 0;
}
