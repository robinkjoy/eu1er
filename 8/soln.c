#include <stdio.h>
#include "data.h"

#define dat(c) ((uint8_t)(data[c])-48)
#define N 13

int main(void)
{
  int i, j;
  uint64_t products[N];
  uint8_t temp;
  uint64_t max = 0;

  for (i = 0; i < N; ++i) {
    temp = dat(i);
    for (j = 0; j < N; ++j) {
      if (i == j) {
        products[j] = temp;
      } else {
        products[j] *= temp;
      }
    }
  }

  for (i = N; i < 1000; ++i) {
    temp = dat(i);
    for (j = 0; j < N; ++j) {
      if (i%N == j) {
        max = (products[j]>max)?products[j]:max;
        products[j] = temp;
      } else {
        products[j] *= temp;
      }
    }
  }

  printf("%lu\n", max);

  return 0;
}
