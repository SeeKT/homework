/*離散フーリエ変換を用いて巡回畳み込みを計算するプログラム*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 256   //任意の長さ

int main(void)
{
  FILE *f1,*f2,*f3,*f4,*fp_1,*fp_2;
  char *fname1="fourier_99_re.txt";
  char *fname2="fourier_99_im.txt";
  char *fname3="fourier_in16_re.txt";
  char *fname4="fourier_in16_im.txt";
  char readline[N]={'\0'};
  double fxr[N],fxi[N],fpr[N],fpi[N],yr[N],yi[N];
  int k,n;

  f1 = fopen(fname1,"r");
  if(f1==NULL){
    printf("%sファイルが開けません\n",fname1);
    return -1;
  }
  int cnt=0;
  while(fgets(readline,256,f1)!=NULL){
    sscanf(readline,"%lf",&fxr[cnt]);
    cnt++;
  }
  fclose(f1);

  f2 = fopen(fname2,"r");
  if(f2==NULL){
    printf("%sファイルが開けません\n",fname2);
    return -1;
  }
  cnt=0;
  while(fgets(readline,256,f2)!=NULL){
    sscanf(readline,"%lf",&fxi[cnt]);
    cnt++;
  }
  fclose(f2);

  f3 = fopen(fname3,"r");
  if(f3==NULL){
    printf("%sファイルが開けません\n",fname3);
    return -1;
  }
  cnt=0;
  while(fgets(readline,256,f3)!=NULL){
    sscanf(readline,"%lf",&fpr[cnt]);
    cnt++;
  }
  fclose(f3);

  f4 = fopen(fname4,"r");
  if(f4==NULL){
    printf("%sファイルが開けません\n",fname2);
    return -1;
  }
  cnt=0;
  while(fgets(readline,256,f4)!=NULL){
    sscanf(readline,"%lf",&fpi[cnt]);
    cnt++;
  }
  fclose(f4);

  fp_1=fopen("F16_r.txt","w");
  fp_2=fopen("F16_i.txt","w");

  for(k=0;k<N;k++){
    yr[k]=fxr[k]*fpr[k]-fxi[k]*fpi[k];
    yi[k]=fxr[k]*fpi[k]+fxi[k]*fpr[k];
    fprintf(fp_1,"%f\n",yr[k]);
    fprintf(fp_2,"%f\n",yi[k]);
  }
  fclose(fp_1);
  fclose(fp_2);

  return 0;
}
