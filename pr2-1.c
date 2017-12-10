/*乱数により問題を生成するプログラム*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 5

/*0~2の範囲の乱数を発生させる*/
double ran0() {
    return 2*(double)rand()/((double)RAND_MAX+1);
}

int main(void)
{
  FILE *f1;
  double array[N][N];
  double bector[N];
  srand(time(NULL));

  int i,j;
  f1=fopen("equation_5.txt","w");

  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      /*0~2の一様乱数から1を引くことで-1から1の範囲の一様乱数を発生されることができる*/
      array[i][j]=ran0()-1;
      fprintf(f1,"%f ",array[i][j]);
    }
    bector[i]=ran0()-1;
    fprintf(f1,"%f\n",bector[i]);
  }

  fclose(f1);

  return 0;

}
