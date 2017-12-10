/*自己相関関数の計算*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 256   //任意の長さ
#define NUM 256   //任意の長さ

int main(void)
{
  FILE *fp_1;    //FILE型の構造体
  FILE *fp_2;
  char *fname_1 = "sinwave2.txt";
  char *fname_2 = "noise2.txt";
  char line1[N][256];   //sinwave.txtから読み込んだ文字列を格納する配列
  char line2[NUM][256];   //noise.txtから読み込んだ文字列を格納する配列
  int f_1_1[N];    //sinwave.txtに書き込まれた数字を格納する配列
  double f_1_2[N];    //sinwave.txtに書き込まれた数字を格納する配列
  double f_2[NUM];    //noise.txtに書き込まれた数字を格納する配列
  double r_1[N];
  double r_2[NUM];
  int i,j;

  fp_1 = fopen(fname_1,"r");
  if(fp_1==NULL){
    printf("%sファイルが開けません\n",fname_1);
    return -1;
  }

  int cnt1=0;
  while(fgets(line1[cnt1],256,fp_1)!=NULL){
    sscanf(line1[cnt1],"%d %lf",&f_1_1[cnt1],&f_1_2[cnt1]);
    cnt1++;
  }
  fclose(fp_1);


  fp_2 = fopen(fname_2,"r");
  if(fp_2==NULL){
    printf("%sファイルが開けません\n",fname_2);
    return -1;
  }

  int cnt2=0;
  while(fgets(line2[cnt2],256,fp_2)!=NULL){
    sscanf(line2[cnt2],"%lf",&f_2[cnt2]);
    cnt2++;
  }
  fclose(fp_2);

  for(i=0;i<N;i++){
    r_1[i]=0;
  }

  /*自己相関関数を求める*/
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      r_1[i]+=f_1_2[j]*f_1_2[j+i];
    }
  }

  for(i=0;i<NUM;i++){
    for(j=0;j<NUM;j++){
      r_2[i]+=f_2[j]*f_2[j+i];
    }
  }

  FILE *f1;
  FILE *f2;
  int n;

  f1=fopen("cor_sin.txt","w");

  for(n=0;n<N;n++){
    fprintf(f1,"%f\n",r_1[n]);
  }

  f2=fopen("cor_noise.txt","w");

  for(n=0;n<NUM;n++){
    fprintf(f2,"%f\n",r_2[n]);
  }

  return 0;
}
