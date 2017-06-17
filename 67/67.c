#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define N 100

int main(void)
{
  int i, j;
  uint64_t **tri;
  uint64_t temp;

  tri = (uint64_t **)malloc(N*sizeof(uint64_t *));
  for (i = 0; i < N; ++i) {
    tri[i] = (uint64_t *)malloc((i+1)*sizeof(uint64_t));
  }

  for (i = 0; i < N; ++i) {
    for (j = 0; j < i+1; ++j) {
      scanf("%lu", &tri[i][j]);
    }
  }

  for (i = N-2; i >= 0; --i) {
    for (j = 0; j < i+1; ++j) {
      temp = (tri[i+1][j] > tri[i+1][j+1]) ? tri[i+1][j] : tri[i+1][j+1];
      tri[i][j] += temp;
    }
  }
  printf("%lu\n", tri[0][0]);

  return 0;
}
