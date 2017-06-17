#include <stdio.h>
#include "data.h"

#define N 4

int main(void)
{
  int i, j, k;
  uint64_t products[N];
  uint8_t temp;
  uint64_t max = 0;

  // horiz
  for (i = 0; i < 20; ++i) {
    for (j = 0; j < N; ++j) {
      temp = data[i][j];
      for (k = 0; k < N; ++k) {
        if (j == k) {
          products[k] = temp;
        } else {
          products[k] *= temp;
        }
      }
    }
    for (j = N; j < 20; ++j) {
      temp = data[i][j];
      for (k = 0; k < N; ++k) {
        if (j%N == k) {
          max = (products[k]>max)?products[k]:max;
          products[k] = temp;
        } else {
          products[k] *= temp;
        }
      }
    }
    max = (products[20%N]>max)?products[20%N]:max;
  }

  // vert
  for (i = 0; i < 20; ++i) {
    for (j = 0; j < N; ++j) {
      temp = data[j][i];
      for (k = 0; k < N; ++k) {
        if (j == k) {
          products[k] = temp;
        } else {
          products[k] *= temp;
        }
      }
    }
    for (j = N; j < 20; ++j) {
      temp = data[j][i];
      for (k = 0; k < N; ++k) {
        if (j%N == k) {
          max = (products[k]>max)?products[k]:max;
          products[k] = temp;
        } else {
          products[k] *= temp;
        }
      }
    }
    max = (products[20%N]>max)?products[20%N]:max;
  }

  // diag left down
  for (i = 0; i < (20-N)+1; ++i) {
    for (j = 0; j < N; ++j) {
      temp = data[j+i][j];
      for (k = 0; k < N; ++k) {
        if (j == k) {
          products[k] = temp;
        } else {
          products[k] *= temp;
        }
      }
    }
    for (j = N; j < 20-i; ++j) {
      temp = data[j+i][j];
      for (k = 0; k < N; ++k) {
        if (j%N == k) {
          max = (products[k]>max)?products[k]:max;
          products[k] = temp;
        } else {
          products[k] *= temp;
        }
      }
    }
    max = (products[(20-i)%N]>max)?products[(20-i)%N]:max;
  }
  // diag left right
  for (i = 1; i < (20-N)+1; ++i) {
    for (j = 0; j < N; ++j) {
      temp = data[j][j+i];
      for (k = 0; k < N; ++k) {
        if (j == k) {
          products[k] = temp;
        } else {
          products[k] *= temp;
        }
      }
    }
    for (j = N; j < 20-i; ++j) {
      temp = data[j][j+i];
      for (k = 0; k < N; ++k) {
        if (j%N == k) {
          max = (products[k]>max)?products[k]:max;
          products[k] = temp;
        } else {
          products[k] *= temp;
        }
      }
    }
    max = (products[(20-i)%N]>max)?products[(20-i)%N]:max;
  }

  // diag right down
  for (i = 0; i < (20-N)+1; ++i) {
    for (j = 0; j < N; ++j) {
      temp = data[j+i][19-j];
      for (k = 0; k < N; ++k) {
        if (j == k) {
          products[k] = temp;
        } else {
          products[k] *= temp;
        }
      }
    }
    for (j = N; j < 20-i; ++j) {
      temp = data[j+i][19-j];
      for (k = 0; k < N; ++k) {
        if (j%N == k) {
          max = (products[k]>max)?products[k]:max;
          products[k] = temp;
        } else {
          products[k] *= temp;
        }
      }
    }
    max = (products[(20-i)%N]>max)?products[(20-i)%N]:max;
  }
  // diag right left
  for (i = 1; i < (20-N)+1; ++i) {
    for (j = 0; j < N; ++j) {
      temp = data[j][19-(j+i)];
      printf("(%2d %2d) ", j, 19-(j+i));
      printf("%u\n", temp);
      for (k = 0; k < N; ++k) {
        if (j == k) {
          products[k] = temp;
        } else {
          products[k] *= temp;
        }
      }
    }
    //printf("%lu\n", products[0]);
    for (j = N; j < 20-i; ++j) {
      temp = data[j][19-(j+i)];
      printf("(%2d %2d) ", j, 19-(j+i));
      for (k = 0; k < N; ++k) {
        if (j%N == k) {
          max = (products[k]>max)?products[k]:max;
          products[k] = temp;
        } else {
          products[k] *= temp;
        }
      }
    }
    printf("--\n");
    max = (products[(20-i)%N]>max)?products[(20-i)%N]:max;
  }

  printf("%lu\n", max);

  
  return 0;
}
