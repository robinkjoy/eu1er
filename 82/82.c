#include <stdio.h>
#include <stdint.h>

#define N 80

int main(void)
{
  int i, j, flag;
  uint32_t in[N][N], out[N][N], min;

  for (i = 0; i < N; ++i) {
    for (j = 0; j < N; ++j) {
      scanf("%u", &in[i][j]);
    }
  }

  for (i = 0; i < N; ++i) {
    out[i][0] = in[i][0];
  }

  for (j = 1; j < N; ++j) {
    for (i = 0; i < N; ++i) {
      out[i][j] = out[i][j-1]+in[i][j];
    }
    do {
      flag = 0;
      for (i = 0; i < N; ++i) {
        if (i != 0 && out[i-1][j]+in[i][j] < out[i][j]) {
          out[i][j] = out[i-1][j]+in[i][j];
          flag++;
        }
        if (i != N-1 && out[i+1][j]+in[i][j] < out[i][j]) {
          out[i][j] = out[i+1][j]+in[i][j];
          flag++;
        }
      }
    } while (flag != 0);
  }

  min = UINT32_MAX;
  for (i = 0; i < N; ++i) {
    min = (out[i][N-1]<min)?out[i][N-1]:min;
  }

  printf("%u\n", min);

  return 0;
}
