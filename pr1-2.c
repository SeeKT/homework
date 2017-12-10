/*ガウス性雑音の発生*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N 128   //任意の長さ
#define NUM 512

/*0~1の範囲の乱数を発生させる*/
double ran0() {
    return (double)rand()/((double)RAND_MAX+1);
}

/*ガウス乱数を発生させる*/
void noise(double s, double m, double *y1, double *y2){
  double x1,x2;
  x1=ran0();
  x2=ran0();

  // 正規乱数計算
  *y1 = s * sqrt(-2 * log(x1)) * cos(2 * M_PI * x2) + m;
  *y2 = s * sqrt(-2 * log(x1)) * sin(2 * M_PI * x2) + m;
}

int main(void)
{
  FILE *f1;
  FILE *f2;   //ファイルの宣言

  double sigma = 1;
  double mu = 0;
  double y_1[2*NUM];
  double y_2[2*N];
  srand(time(NULL)); //現在時刻を元に乱数種を生成

  int n;
  f1=fopen("noise.txt","w");

  for(n=0;n<NUM;n++){
    noise(sigma,mu,&y_1[2*n],&y_1[2*n+1]);
    fprintf(f1,"%f\n",y_1[2*n]);
    fprintf(f1,"%f\n",y_1[2*n+1]);
  }

  fclose(f1);


  f2=fopen("noise2.txt","w");

  for(n=0;n<N;n++){
    noise(sigma,mu,&y_2[2*n],&y_2[2*n+1]);
    fprintf(f2,"%f\n",y_2[2*n]);
    fprintf(f2,"%f\n",y_2[2*n+1]);
  }

  fclose(f2);
  return 0;
}
