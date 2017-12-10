/*正規方程式(NUM×NUM)を導出するプログラム*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N 100
#define NUM 5

//base^nを求める
double power(double base, int n)
{
  int i;
  double p;
  p = 1.0;
  for (i = 1; i <= n; ++i)
    p = p * base;
  return p;
}

int main(void)
{
  FILE *fp,*fq;
  char *fname = "fifth.txt";
  char line[N][256];
  double b2[N];
  double A[N][NUM];
  double At[NUM][N];
  double AtA[NUM][NUM];
  double Atb[NUM];
  int n,i,j;

  fp = fopen(fname,"r");
  if(fp==NULL){
    printf("%sファイルが開けません\n",fname);
    return -1;
  }

  int cnt1=0;
  while(fgets(line[cnt1],256,fp)!=NULL){
    sscanf(line[cnt1],"%lf",&b2[cnt1]);
    cnt1++;
  }
  fclose(fp);

  for(n=0;n<NUM;n++){
    Atb[n]=0;
  }

//行列Aを求める
for(i=0;i<N;i++){
  for(j=0;j<NUM;j++){
    A[i][j]=power(((double)i/N),j);
  }
}

//行列Atを求める
for(j=0;j<NUM;j++){
  for(i=0;i<N;i++){
    At[j][i]=power(((double)i/N),j);
  }
}

//正規方程式の行列Aに転置を掛ける(NUM×NUM)
for(i=0;i<NUM;i++){
  for(j=0;j<NUM;j++){
    AtA[i][j]=0;
  }
}
for(i=0;i<NUM;i++){
  for(j=0;j<NUM;j++){
    for(n=0;n<N;n++){
      AtA[i][j]+=At[i][n]*A[n][j];
    }
  }
}

//Atbを求める
for(i=0;i<NUM;i++){
  for(j=0;j<N;j++){
    Atb[i]+=At[i][j]*b2[j];
  }
}

fq=fopen("eA.txt","w");
for(i=0;i<NUM;i++){
  for(j=0;j<NUM;j++){
    fprintf(fq,"%f ",AtA[i][j]);
  }
  fprintf(fq,"%f\n",Atb[i]);
}
fclose(fq);



return 0;
}
