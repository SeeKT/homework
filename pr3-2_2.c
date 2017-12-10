/*正規方程式(3×3)を導出するプログラム*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N 100

int main(void)
{
  FILE *f2,*fq;
  char *fname_2 = "quad.txt";
  char line[N][256];
  double b2[N];
  double Aq[N][3];
  double Aqt[3][N];
  double qAtA[3][3];
  double qAtb[3]={0,0,0};
  int n,i,j;

  f2 = fopen(fname_2,"r");
  if(f2==NULL){
    printf("%sファイルが開けません\n",fname_2);
    return -1;
  }

  int cnt1=0;
  while(fgets(line[cnt1],256,f2)!=NULL){
    sscanf(line[cnt1],"%lf",&b2[cnt1]);
    cnt1++;
  }
  fclose(f2);

  for(n=0;n<N;n++){
    Aq[n][0]=1;
    Aq[n][1]=((double)n/N);
    Aq[n][2]=((double)n/N*n/N);
    Aqt[0][n]=1;
    Aqt[1][n]=((double)n/N);
    Aqt[2][n]=((double)n/N*n/N);
  }

#if 0
  for(i=0;i<N;i++){
    for(j=0;j<3;j++){
      printf("%lf ",Aq[i][j]);
    }
    printf("\n");
  }
  #endif

  //正規方程式の行列Aに転置を掛ける(3×3)
    for(i=0;i<3;i++){
      for(j=0;j<3;j++){
        qAtA[i][j]=0;
      }
    }
    for(i=0;i<3;i++){
      for(j=0;j<3;j++){
        for(n=0;n<N;n++){
          qAtA[i][j]+=Aqt[i][n]*Aq[n][j];
        }
      }
    }

  //Atbを求める
  for(n=0;n<N;n++){
    qAtb[0]+=Aqt[0][n]*b2[n];
    qAtb[1]+=Aqt[1][n]*b2[n];
    qAtb[2]+=Aqt[2][n]*b2[n];
  }

  fq=fopen("eqAq.txt","w");
  for(i=0;i<3;i++){
    for(j=0;j<3;j++){
      fprintf(fq,"%f ",qAtA[i][j]);
    }
    fprintf(fq,"%f\n",qAtb[i]);
  }
  fclose(fq);



  return 0;
}
