/*正弦波の発生*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 256   //任意の長さ
#define A 1   //振幅


int main(void)
{
  FILE *f1;   //ファイルの宣言
  FILE *f2;

  double omega;   //各周波数
  double theta;   //位相
  double x[N];    //正弦波を離散化することで得られる数列

  f1=fopen("sinwave.txt","w");

  omega=M_PI/16;    //omegaにM_PI/16を代入
  theta=0;    //thetaに0を代入

  int n;

  for(n=0;n<N;n++){
    x[n]=A*sin(omega*n+theta);
    fprintf(f1,"%d %f\n",n,x[n]);

  }

  fclose(f1);

  f2=fopen("sinwave2.txt","w");

  omega=M_PI/32;
  theta=M_PI/3;

  for(n=0;n<N;n++){
    x[n]=A*sin(omega*n+theta);
    fprintf(f2,"%d %f\n",n,x[n]);
  }

  fclose(f2);

  return 0;
}
