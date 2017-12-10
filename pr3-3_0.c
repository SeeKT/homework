/*問題を生成するプログラム*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N 100
#define NUM 5

/*0~1の範囲の乱数を発生させる*/
double ran0() {
    return (double)rand()/((double)RAND_MAX+1);
}

/*ガウス乱数を発生させる*/
void noise(double s, double m, double *y1){
  double x1,x2;
  x1=ran0();
  x2=ran0();

  // 正規乱数計算
  *y1 = s * sqrt(-2 * log(x1)) * cos(2 * M_PI * x2) + m;
}

//m次関数のy_nを求める
double multi(double x[], int n, int m){
  int i;
  double p,q,r;
  r=0;
  p=1.0;
  q=(double)n/N;
  for(i=0;i<m;i++){
    r+=x[i]*p;
    p*=q;
  }
  return r;
}

int main(void)
{
  FILE *f1;

  double sigma=0.5; //分散
  double mu=0;  //平均
  double x[NUM];
  double y[N];
  double b[N];
  double gauss[N];
  int n;

  for(n=0;n<NUM;n++){
    x[n]=rand()%NUM+1;
  }

  f1=fopen("fifth.txt","w");

  for(n=0;n<N;n++){
    noise(sigma,mu,&gauss[n]);
    y[n]=multi(x,n,NUM);
    b[n]=y[n]+gauss[n];
    fprintf(f1,"%f\n",b[n]);
  }

  fclose(f1);

  return 0;
}
