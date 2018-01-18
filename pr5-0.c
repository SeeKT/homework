/*ファイルを生成する*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 256   //信号長
#define M 16   //定数

int main(void)
{
  FILE *f1,*f2;
  double h[N],i[N];
  int n,l,key;

  for(n=0;n<N;n++){
    i[n]=0;
    if (n < M) {
      h[n] = 1.0 / M;
    } else {
      h[n] = 0;
    }
  }

  f1=fopen("inpulse_16.txt","w");
  f2=fopen("99_im.txt","w");
    for(n=0;n<N;n++){
      fprintf(f1,"%f\n",h[n]);
      fprintf(f2,"%f\n",i[n]);
    }
  fclose(f1);
  fclose(f2);

  return 0;
}
