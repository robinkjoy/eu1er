#include <stdio.h>
#include <stdint.h>
#include "data.h"

int main(void)
{
  int i, j;
  uint32_t temp = 0;

  for (i = 0; i < 50; ++i) {
    for (j = 0; j < 100; ++j) {
      temp += ((uint8_t)data[j][49-i]-48); 
    }
    //printf("%u %u\n", temp%10, temp/10);
    printf("%u", temp%10);
    temp /= 10;
  }
  printf("\n%d\n", temp);

  return 0;
}
