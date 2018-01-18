/*巡回畳み込み演算を計算するプログラム*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 256   //任意の長さ
#define M 8

int main(void)
{
  FILE *f1,*f2,*f3,*f4,*fp_1,*fp_2;
  char *fname1="99.txt";
  char *fname2="99_im.txt";
  char *fname3="rF_re.txt";
  char *fname4="rF_im.txt";
  char readline[N]={'\0'};
  double x_re[N],x_im[N],h_re[N],h_im[N],y_re[N],y_im[N];
  int n,l,key;

  f1 = fopen(fname1,"r");
  if(f1==NULL){
    printf("%sファイルが開けません\n",fname1);
    return -1;
  }
  int cnt1=0;
  while(fgets(readline,256,f1)!=NULL){
    sscanf(readline,"%lf",&x_re[cnt1]);
    cnt1++;
  }
  fclose(f1);

  f2 = fopen(fname2,"r");
  if(f2==NULL){
    printf("%sファイルが開けません\n",fname2);
    return -1;
  }
  int cnt2=0;
  while(fgets(readline,256,f2)!=NULL){
    sscanf(readline,"%lf",&x_im[cnt2]);
    cnt2++;
  }
  fclose(f2);

  f3 = fopen(fname3,"r");
  if(f3==NULL){
    printf("%sファイルが開けません\n",fname3);
    return -1;
  }
  int cnt3=0;
  while(fgets(readline,256,f3)!=NULL){
    sscanf(readline,"%lf",&h_re[cnt3]);
    cnt3++;
  }
  fclose(f3);

  f4 = fopen(fname4,"r");
  if(f4==NULL){
    printf("%sファイルが開けません\n",fname4);
    return -1;
  }
  int cnt4=0;
  while(fgets(readline,256,f4)!=NULL){
    sscanf(readline,"%lf",&h_im[cnt4]);
    cnt4++;
  }
  fclose(f4);

  for(n=0;n<N;n++){
    y_re[n]=0;
    y_im[n]=0;
    for(l=0;l<N;l++){
      key=n-l;
      if(key<0){
        key+=N;
      }
      y_re[n]+=h_re[l]*x_re[key]-h_im[l]*x_im[key];
      y_im[n]+=h_im[l]*x_re[key]+h_re[l]*x_im[key];
    }
  }

  fp_1=fopen("con_16_re.txt","w");
  fp_2=fopen("con_16_im.txt","w");
    for(n=0;n<N;n++){
      fprintf(fp_1,"%f\n",y_re[n]);
      fprintf(fp_2,"%f\n",y_im[n]);
    }
  fclose(fp_1);
  fclose(fp_2);

  return 0;
}
