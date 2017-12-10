/*正規方程式(2×2)を導出するプログラム*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N 100

int main(void)
{
  FILE *f1,*fp;
  char *fname_1 = "prim.txt";
  char line[N][256];
  double b1[N];
  double Ap[N][2];
  double Apt[2][N];
  double pAtA[2][2];
  double pAtb[2]={0,0};
  int n,i,j;

  f1 = fopen(fname_1,"r");
  if(f1==NULL){
    printf("%sファイルが開けません\n",fname_1);
    return -1;
  }

  int cnt1=0;
  while(fgets(line[cnt1],256,f1)!=NULL){
    sscanf(line[cnt1],"%lf",&b1[cnt1]);
    cnt1++;
  }
  fclose(f1);

  for(n=0;n<N;n++){
    Ap[n][0]=1;
    Ap[n][1]=((double)n/N);
    Apt[0][n]=1;
    Apt[1][n]=((double)n/N);
  }

  //正規方程式の行列Aに転置を掛ける(2×2)
  for(i=0;i<2;i++){
    for(j=0;j<2;j++){
      pAtA[i][j]=0;
    }
  }
  for(i=0;i<2;i++){
    for(j=0;j<2;j++){
      for(n=0;n<N;n++){
        pAtA[i][j]+=Apt[i][n]*Ap[n][j];
      }
    }
  }

  //Atbを求める
  for(n=0;n<N;n++){
    pAtb[0]+=Apt[0][n]*b1[n];
    pAtb[1]+=Apt[1][n]*b1[n];
  }

  fp=fopen("eqAp.txt","w");
  for(i=0;i<2;i++){
    for(j=0;j<2;j++){
      fprintf(fp,"%f ",pAtA[i][j]);
    }
    fprintf(fp,"%f\n",pAtb[i]);
  }
  fclose(fp);



  return 0;
}
