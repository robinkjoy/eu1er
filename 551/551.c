#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint64_t sum_of_digits(uint64_t n)
{
  uint64_t t;
  uint64_t sum = 0;

  t = n;

  while(t > 0) {
    sum += t%10;
    t /= 10;
  }
  return sum;
}

int main(int argc, char *argv[])
{
  uint64_t i, temp;
  uint64_t a = 1;

  if (argc != 2) {
    printf("missing arg\n");
    return 0;
  }

  for (i = 1; i < strtol(argv[1], NULL, 10); ++i) {
    temp = sum_of_digits(a);
    a += temp;
    //printf("%lu\n", a);
  }

  printf("%lu\n", a);

  return 0;
}
