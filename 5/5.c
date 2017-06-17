#include <stdio.h>

int main(void)
{

  int n = 19, i, status=1;

  while(status == 1) {
    n++;
    status = 0;
    for (i = 2; i <= 20; ++i) {
      if (n%i != 0) {
        status = 1;
        break;
      }
    }
  }
  printf("%d\n", n);
  return 0;
}
