/*問題を生成するプログラム*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N 100

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

double prim(double x1, double x2, int n){
  return x1+x2*((double)n/N);
}

double quad(double x1, double x2, double x3, int n){
  return x1+x2*((double)n/N)+x3*((double)n/N*n/N);
}

int main(void)
{
  FILE *f1;
  FILE *f2;

  double sigma=1.0; //分散
  double mu=0;  //平均
  double x_1,x_2;
  double x_1_2,x_2_2,x_3_2;
  double y1[N],y2[N];
  double b1[N],b2[N];
  double gauss[N];
  int n;

  //１次関数のパラメータ
  x_1=2;
  x_2=3;

  //２次関数のパラメータ
  x_1_2=2;
  x_2_2=1;
  x_3_2=3;

  f1=fopen("prim.txt","w");
  f2=fopen("quad.txt","w");

  for(n=0;n<N;n++){
    noise(sigma,mu,&gauss[n]);
    y1[n]=prim(x_1,x_2,n);
    b1[n]=y1[n]+gauss[n];
    y2[n]=quad(x_1_2,x_2_2,x_3_2,n);
    b2[n]=y2[n]+gauss[n];
    fprintf(f1,"%f\n",b1[n]);
    fprintf(f2,"%f\n",b2[n]);
  }

  fclose(f1);
  fclose(f2);


  return 0;
}
