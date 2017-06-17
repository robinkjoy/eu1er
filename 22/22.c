#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

int swap(char *a, char *b)
{
  int count = 0;
  while (a[count] != '\0' && b[count] != '\0') {
    if (a[count] > b[count]) {
      return 1;
    } else if (a[count] < b[count]) {
      return 0;
    }
    count++;
  }
  if (a[count] == '\0') {
    return 0;
  } else {
    return 1;
  }
}

uint64_t score(char * a)
{
  int sum = 0, count = 0;
  while(a[count] != '\0') {
    sum += ((int)a[count] - 64);
    count++;
  }
  return sum;
}

int main(void)
{
  uint64_t i, j;
  char **names, temp[100];
  uint64_t sum = 0;

  names = (char **)malloc(5163*sizeof(char *));
  for (i = 0; i < 5163; ++i) {
    names[i] = (char *)malloc(100*sizeof(char));
  }

  for (i = 0; i < 5163; ++i) {
    scanf("%s", names[i]);
  }

  //sort
  for (i = 0; i < 5163; ++i) {
    for (j = i+1; j < 5163; ++j) {
      if (swap(names[i], names[j]) == 1) {
        strcpy(temp, names[j]);
        strcpy(names[j], names[i]);
        strcpy(names[i], temp);
      }
    }
  }

  for (i = 0; i < 5163; ++i) {
    sum += ((i+1)*score(names[i]));
  }
  printf("%lu\n", sum);

  return 0;
}
