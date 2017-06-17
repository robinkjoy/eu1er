#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <string.h>

#define Z 3
#define Y 300
#define X 100

struct lut {
  uint32_t count;
  uint32_t sum;
};

uint32_t sum_of_digits(uint32_t offset, uint32_t n)
{
  uint32_t t;
  uint32_t sum = 0;

  t = n;

  while(t > 0) {
    sum += t%10;
    t /= 10;
  }
  return sum+offset;
}

int main(void)
{

  uint32_t i, j, total_sum = 0, sum = 0, limit, count;
  FILE *fp;
  char filename[100];

  sprintf(filename, "lut%d.dat", Z);
  fp = fopen(filename, "w");

  limit = (uint32_t)pow(10.0, (double)Z+1);
#ifndef DEBUG
  for (i = 1; i < Y; ++i) {
    for (j = 0; j < X; ++j) {
#else
  for (i = 1; i < 2; ++i) {
    for (j = 0; j < 1; ++j) {
#endif
      count = 0;
      sum = j;
      total_sum = 0;
      while (limit > total_sum+sum) {
        total_sum += sum;
        count++;
        sum = sum_of_digits(i, total_sum);
#ifdef DEBUG
        printf("%u %u\n", count, total_sum);
#endif
      }
      fprintf(fp, "%u %u (%d, %d, %d)\n", count-1, total_sum-j, Z, i, j);
    }
    //printf("i = %d\n", i);
  }

  fclose(fp);
  
  return 0;
}
