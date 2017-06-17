#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#ifndef Z
#define Z 3
#endif
#define Y 100
#define X 100

//#define table_size(n) ((17-(n))*(17-(n)))
#define table_size(n) ((17-(n))*9)

struct lut {
  uint64_t count;
  uint64_t sum;
};

struct result {
  uint64_t sum;
  int zcnt;
  int ysum;
  int x;
};

struct result sum_of_digits(uint32_t offset, uint64_t n)
{
  uint64_t t;
  uint64_t sum = 0;
  int cnt = 0, ysum = 0, temp, zcnt = 0, flag = 0, x = 0;
  struct result res;

  t = n;

  while(t > 0) {
    temp = t%10;
    t /= 10;
    if (cnt < 2) {
      cnt++;
    } else {
      if (temp == 0 && flag == 0) {
        zcnt++;
      } else {
        flag++;
      }
      ysum += temp;
    }
    sum += temp;
  }
  //printf("%lu %d %d\n", sum, zcnt, xsum);
  res.sum = sum+offset;
  res.zcnt = zcnt+1;
  res.ysum = ysum+offset;
  res.x = n%100;
  return res;
}

int main(void)
{

  uint32_t i, j, k;
  uint64_t total_sum = 0, sum = 0, limit, count, total_count, first;
  FILE *fp;
  struct result res;
  char filename[100];
  struct lut ***luts;

  setbuf(stdout, NULL);

  luts = (struct lut ***) malloc(sizeof(struct lut **)*(Z-2));
  for (i = 0; i < Z-2; ++i) {
    luts[i] = (struct lut **) malloc(sizeof(struct lut *)*(table_size(i+2)-1));
    for (j = 0; j < table_size(i+2)-1; ++j) {
      luts[i][j] = (struct lut *) malloc(sizeof(struct lut)*X);
    }
  }

  sprintf(filename, "lut%d.dat", Z-1);
  fp = fopen(filename, "r");
  for (i = 0; i < Z-2; ++i) {
    for (j = 0; j < (table_size(i+2))-1; ++j) {
      for (k = 0; k < X; ++k) {
        fscanf(fp, "%lu %lu (%*d, %*d, %*d)", &(luts[i][j][k].count), &(luts[i][j][k].sum));
      }
    }
  }
  fclose(fp);

  sprintf(filename, "lut%d.dat", Z);
  fp = fopen(filename, "w");

  for (i = 0; i < Z-2; ++i) {
    for (j = 0; j < (table_size(i+2))-1; ++j) {
      for (k = 0; k < X; ++k) {
        fprintf(fp, "%lu %lu (%d, %d, %d)\n", luts[i][j][k].count, luts[i][j][k].sum, i+2, j+1, k);
      }
    }
  }

  limit = (uint64_t)pow(10.0, (double)Z+1);
  printf("%d %lu\n", table_size(Z), limit);
#ifndef DEBUG
  for (i = 1; i < table_size(Z); ++i) {
    for (j = 0; j < X; ++j) {
#else
  for (i = 1; i < 2; ++i) {
    for (j = 0; j < 1; ++j) {
#endif
      total_count = 0;
      count = luts[Z-1-2][i-1][j].count;
      total_sum = j;
      sum = luts[Z-1-2][i-1][j].sum;
      while (limit > total_sum+sum) {
        total_sum += sum;
        total_count += count;
        res = sum_of_digits(i, total_sum);
        if (res.zcnt >= 2) {
          count = luts[res.zcnt-2][res.ysum-1][res.x].count;
          sum = luts[res.zcnt-2][res.ysum-1][res.x].sum;
        } else {
          count = 1;
          sum = res.sum;
        }
#ifdef DEBUG
        printf("zcnt = %u ysum = %u x = %u\n", res.zcnt, res.ysum, res.x);
        printf("count = %lu sum = %lu\n", count, sum);
        printf("%lu %lu\n", total_count+count, total_sum+sum-j);
#endif
      }
      fprintf(fp, "%lu %lu (%d, %d, %d)\n", total_count, total_sum-j, Z, i, j);
#ifdef DEBUG
      printf("j = %d\n", j);
#endif
    }
    printf("0");
  }

  fclose(fp);
  printf("\n");
  
  return 0;
}
