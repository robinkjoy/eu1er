#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define LSIZE 100000000

int main(void)
{
  int i, j;
  uint32_t count, n, seq_count, max = 0, maxn;
  uint32_t *lut = malloc(LSIZE*sizeof(uint32_t));
  uint32_t *seq = malloc(LSIZE*sizeof(uint32_t));
  
  for (i = 0; i < LSIZE; ++i) {
    lut[i] = 0;
  }

  for (i = 2; i < 1000000; ++i) {
    count = 1;
    n = i;
    seq_count = 0;
    while (n != 1) {
      if (n < LSIZE && lut[n] != 0) {
        count += lut[n];
        break;
      }
      if (n%2 == 0) {
        n = n/2;
      } else {
        n = n*3+1;
      }
      seq[seq_count] = n;
      count++;
      seq_count++;
    }
    lut[i] = count;
    //printf("%u %u\n", i, count);
    for (j = 0; j < seq_count; ++j) {
      if (seq[j] < LSIZE) {
        lut[seq[j]] = count-j-1;
      }
      //printf("%u %u\n", seq[j], count-j-1);
    }
    if (count > max) {
      max = count;
      maxn = i;
      //printf("%u, %u\n", maxn, count);
    }
  }
  printf("%u, %u\n", maxn, max);

  return 0;
}
