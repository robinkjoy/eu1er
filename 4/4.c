#include <stdio.h>

int is_pldm(int a)
{
  if (a < 100000) {
    printf("less than 6 digits\n");
    return 2;
  }
  if (a%10 != a/100000) {
    return 1;
  }
  if ((a%100)/10 != (a%100000)/10000) {
    return 1;
  }
  if ((a%1000)/100 != (a%10000)/1000) {
    return 1;
  }
  return 0;
}

int main(void)
{

  int i, j;
  int max = 0;
  int status;

  for (i = 999; i  > 500; --i) {
    for (j = 999; j >= i; --j) {
      status = is_pldm(i*j);
      if (status == 2) {
        return 0;
      }
      if (status == 0) {
        if (i*j > max) {
          max = i*j;
          printf("%d\n", max);
        }
      }
    }
  }
  
  return 0;
}
