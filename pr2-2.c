/*ガウスの消去法*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define N1 5

int main(void)
{
  FILE *f1;
  char *fname_1 = "eA.txt";
  char line1[N1][256];
  char *line1_1[N1+1][256];
  double Array1[N1][N1];
  double Array1_1[N1][N1];
  double Array1_2[N1][N1];
  double Bector1[N1];
  double Bector1_1[N1];
  double r1;
  double max1;
  double tmp;
  int i,j,k,p;
  char *tp;
  double tmp1[N1];
  double X1[N1];

  f1 = fopen(fname_1,"r");
  if(f1==NULL){
    printf("%sファイルが開けません\n",fname_1);
    return -1;
  }

  int cnt1=0;
  while(fgets(line1[cnt1],256,f1)!=NULL){
    cnt1++;
  }
  fclose(f1);

  for(i=0;i<N1;i++){
     /* 最初に見つかった区切り文字（" "）に "\0" を挿入する */
    tp=strtok(line1[i]," ");
    line1_1[i][0]=tp;
    j=1;
    /* 第一引数に NULL を指定すると前回の line1_1 値の続きから始める */
    /* strtok() の戻り値は次のトークンの位置 */
    /* 区切り文字が見つからなかったら NULL が返ってくる */
    while(tp=strtok(NULL, " ")){
      line1_1[i][j]=tp;
      j++;
    }
  }

/*Array1に係数行列、Bector1に係数ベクトルを格納する*/
  for(i=0;i<N1;i++){
    for(j=0;j<N1;j++){
      Array1[i][j]=atof(line1_1[i][j]);
    }
    Bector1[i]=atof(line1_1[i][N1]);
  }


  for(i=0;i<N1;i++){
    for(j=0;j<N1;j++){
      Array1_2[i][j]=Array1[i][j];
      //printf("%f ",Array1_2[i][j]);
    }
    Bector1_1[i]=Bector1[i];
    //printf("%f",Bector1_1[i]);
    //printf("\n");
  }
  printf("\n");



/*行列の要素の絶対値を求める*/
  for(i=0;i<N1;i++){
    for(j=0;j<N1;j++){
      Array1_1[i][j]=fabs(Array1[i][j]);
    }
  }

/*解の存在判定*/
  for(k=0;k<N1;k++){
    if(Array1[k][k]==0){
      printf("解が一意に定まらない\n");
      return -1;
    }
    /*列ベクトルの要素の絶対値が最大となる行とk行を交換する*/
    max1=fabs(Array1[k][k]);
    for(i=k;i<N1;i++){
      Array1_1[i][k]=fabs(Array1[i][k]);
      if(max1<=Array1_1[i][k]){
        max1=Array1_1[i][k];
        p=i;
      }
    }

    for(j=0;j<N1;j++){
      tmp1[j]=Array1[k][j];
      Array1[k][j]=Array1[p][j];
      Array1[p][j]=tmp1[j];
    }

    tmp=Bector1[k];
    Bector1[k]=Bector1[p];
    Bector1[p]=tmp;

    /*k列を消去する*/
    for(i=k+1;i<N1;i++){
      r1=Array1[i][k]/Array1[k][k];
      for(j=k;j<N1;j++){
        Array1[i][j]-=r1*Array1[k][j];
      }
      Bector1[i]-=r1*Bector1[k];
    }

#if 0
    for(i=0;i<N1;i++){
      for(j=0;j<N1;j++){
        printf("%f ",Array1[i][j]);
      }
      printf("%f",Bector1[i]);
      printf("\n");
    }
    printf("\n");
#endif
  }


//解xを求める
  double sum[N1];
  for(i=0;i<N1;i++){
    sum[i]=0;
  }

  for(i=N1-1;i>=0;i--){
    for(j=i+1;j<N1;j++){
      sum[i]+=Array1[i][j]*X1[j];
    }
    X1[i]=Bector1[i]-sum[i];
    X1[i]/=Array1[i][i];
  }

  for(i=0;i<N1;i++){
    printf("%f\n",X1[i]);
  }

//テキストファイルに書き込む
  FILE *fp_1;
  fp_1=fopen("eA_ans.txt","w");
  for(i=0;i<N1;i++){
    fprintf(fp_1,"%f\n",X1[i]);
  }
  fclose(fp_1);

//誤差を求める
  double E[N1];
  for(i=0;i<N1;i++){
    E[i]=0;
  }

  for(i=0;i<N1;i++){
    for(j=0;j<N1;j++){
      E[i]+=Array1_2[i][j]*X1[j];
    }
    E[i]-=Bector1_1[i];
  }

//相対誤差を求める
  double Norm_E,Norm_b;
  Norm_E=0;
  Norm_b=0;
  for(i=0;i<N1;i++){
    Norm_E+=E[i]*E[i];
    Norm_b+=Bector1_1[i]*Bector1_1[i];
  }

  Norm_E=sqrt(Norm_E);
  Norm_b=sqrt(Norm_b);

  double RE=Norm_E/Norm_b;

  printf("%e\n",RE);

  return 0;
}
