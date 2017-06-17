#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

struct result {
  uint64_t sum;
  int zcnt;
  int ysum;
  int x;
};

#define Z 16
#define Y 300
#define X 100

#define table_size(n) ((17-(n))*9)

struct lut {
  uint64_t count;
  uint64_t sum;
};

struct result sum_of_digits(uint64_t n)
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
  res.sum = sum;
  res.zcnt = (zcnt+1>Z)?Z:zcnt+1;
  res.ysum = ysum;
  res.x = n%100;
  return res;
}

int main(void)
{
  uint64_t i, j, k, temp;
  int max_zcnt;
  uint64_t sum, total_sum, count, total_count, target_count;
  struct result res;
  FILE *fp;
  char filename[100];
  struct lut ***luts;

  luts = (struct lut ***) malloc(sizeof(struct lut **)*(Z-1));
  for (i = 0; i < Z-1; ++i) {
    luts[i] = (struct lut **) malloc(sizeof(struct lut *)*(table_size(i+2)-1));
    for (j = 0; j < table_size(i+2)-1; ++j) {
      luts[i][j] = (struct lut *) malloc(sizeof(struct lut)*X);
    }
  }

  sprintf(filename, "lut%d.dat", Z);
  fp = fopen(filename, "r");
  for (i = 0; i < Z-1; ++i) {
    for (j = 0; j < table_size(i+2)-1; ++j) {
      for (k = 0; k < X; ++k) {
        fscanf(fp, "%lu %lu (%*d, %*d, %*d)", &(luts[i][j][k].count), &(luts[i][j][k].sum));
      }
    }
  }
  fclose(fp);

  total_count = 81; total_sum = 1003;
  count = 0; sum = 0;
  max_zcnt = Z;
  target_count = 1000000000000000;
  while (1) {
    res = sum_of_digits(total_sum);
    res.zcnt = (res.zcnt > max_zcnt)?max_zcnt:res.zcnt;
    if (res.zcnt >= 2 && res.ysum < table_size(res.zcnt)) {
      count = luts[res.zcnt-2][res.ysum-1][res.x].count;
      sum = luts[res.zcnt-2][res.ysum-1][res.x].sum;
      //printf("z = %d y = %d x = %d\n", res.zcnt, res.ysum, res.x);
      //printf("c+ = %lu s+ = %lu\n", count, sum);
    } else {
      count = 1;
      sum = res.sum;
      //printf("c+ = %lu s+ = %lu\n", count, sum);
    }
    if (total_count+count > target_count) {
      max_zcnt = res.zcnt-1;
    } else {
      total_count += count;
      total_sum += sum;
      //printf("c = %lu s = %lu\n", total_count, total_sum);
    }
    if (total_count == target_count) {
      break;
    }
  }


  printf("%lu %lu\n", total_count, total_sum);

  return 0;
}
